/**
 * @file      sso_string.hpp
 * @brief     A string implemtion to optimize short strings
 * @version   0.1
 * @author    dragon-archer (dragon-archer@outlook.com)
 *
 * @copyright Copyright (c) 2022
 */

#ifndef _UTILITY_SSO_STRING_HPP_
#define _UTILITY_SSO_STRING_HPP_

#include "../config.hpp"
#include "string_fwd.hpp"

namespace da {
	template<typename Char, typename Traits, typename Alloc>
	class sso_string_base {
		// If char type isn't pod, then the allocation will fail
		// Since is_pod is depercated in C++20, use is_standard_layout && is_trivial instead
		static_assert(std::is_standard_layout<Char>::value && std::is_trivial<Char>::value, "Char type must be pod");
		// Char size should be less than 8(max_sso_size should be at least 1), otherwise it can't be optimized
		static_assert(sizeof(Char) <= 8, "Char size should be less than 8 bytes, otherwise it can't be optimized");

	public:
		typedef Traits											traits_type;
		typedef typename traits_type::char_type					value_type;
		typedef Alloc											allocator_type;
		typedef std::allocator_traits<allocator_type>			alloc_traits;
		typedef typename alloc_traits::size_type				size_type;
		typedef typename alloc_traits::difference_type			difference_type;
		typedef typename alloc_traits::pointer					pointer;
		typedef typename alloc_traits::const_pointer			const_pointer;
		typedef value_type&										reference;
		typedef const value_type&								const_reference;
		typedef normal_iterator<pointer, sso_string_base>		iterator;
		typedef normal_iterator<const_pointer, sso_string_base> const_iterator;
		typedef std::reverse_iterator<iterator>					reverse_iterator;
		typedef std::reverse_iterator<const_iterator>			const_reverse_iterator;

		// 2 represents alignment & '\0'
		static constexpr size_type max_sso_size = ((2 * sizeof(size_type) + sizeof(pointer)) / sizeof(value_type)) - 2;
		// Since the highest bit of m_size is used to identify whether it is optimized,
		// we can only use half of the size
		static constexpr size_type npos = std::numeric_limits<size_type>::max() / 2;

		constexpr sso_string_base() noexcept
			: m_data{ .short_string = { 0x80, '\0' } } { }

	private:
		// The memory layout is like:
		// SSO:
		// ---------------------------------
		// |S&m_size| 1B                   | 8B
		// |             m_ptr             | 16B
		// |                               | 24B
		// Normal:
		// | S | 1b      m_size            | 8B
		// |             m_capacity        | 16B
		// |             m_ptr             | 24B
		// If S is 1, then the string is optimized
		// otherwise, it is in normal state;
		union data_type {
			struct {
				unsigned char m_size;
				value_type	  m_ptr[max_sso_size + 1]; // One more Char for '\0'
			} short_string;
			struct {
				size_type m_size;
				size_type m_capacity;
				pointer	  m_ptr;
			} long_string;
		} m_data;

	protected:
		// Internal functions used by da::string

		// TODO: Use EBO to reduce the construction cost
		inline allocator_type get_alloc() const noexcept {
			return allocator_type();
		}

		// Check whether the string is optimized
		inline bool is_sso() const noexcept {
			return (*reinterpret_cast<const unsigned char* const>(&m_data)) & (0x80);
		}

		void change_sso_to_normal() {
			UTILITY_IFUNLIKELY(!is_sso()) {
				return;
			}
			data_type new_data;
			new_data.long_string.m_size		= size();
			new_data.long_string.m_capacity = 32 / sizeof(value_type); // nearest power of 2 that bigger than max_sso_size
			UTILITY_TRY {
				new_data.long_string.m_ptr = alloc_traits::allocate(get_alloc(), new_data.long_string.m_capacity);
				traits_type::copy(new_data.long_string.m_ptr, data(), size());
			}
			UTILITY_CATCH(...) {
				UTILITY_THROW_AGAIN
			}
			m_data = new_data;
		}

		void change_normal_to_sso() {
			UTILITY_IFUNLIKELY(is_sso()) {
				return;
			}
			UTILITY_IFUNLIKELY(m_data.long_string.m_size > max_sso_size) {
				UTILITY_THROW(std::out_of_range("current size exceeds max_sso_size"));
			}
			data_type new_data;
			new_data.short_string.m_size = size();
			// Since new_data is allocated on stack, it should not throw errors
			traits_type::copy(new_data.short_string.m_ptr, data(), size());
			UTILITY_TRY {
				alloc_traits::deallocate(get_alloc(), data(), capacity());
			}
			UTILITY_CATCH(...) {
				UTILITY_THROW_AGAIN
			}
			m_data = new_data;
		}

		inline void set_size(size_type n) noexcept {
			if(is_sso()) {
				m_data.short_string.m_size = static_cast<size_type>(n + 0x80);
			} else {
				m_data.long_string.m_size = n;
			}
		}

		inline void set_capacity(size_type n) noexcept {
			if(!is_sso()) {
				m_data.long_string.m_capacity = n;
			}
		}

		inline void set_ptr(pointer p) noexcept {
			if(!is_sso()) {
				m_data.long_string.m_ptr = p;
			}
		}

	public:
		inline size_type size() const noexcept {
			return is_sso() ? static_cast<size_type>(m_data.short_string.m_size - 0x80) // SSO bit
							: m_data.long_string.m_size;
		}

		inline size_type capacity() const noexcept {
			return is_sso() ? max_sso_size
							: m_data.long_string.m_capacity;
		}

		inline pointer data() const noexcept {
			return is_sso() ? const_cast<pointer>(static_cast<const_pointer>(m_data.short_string.m_ptr))
							: m_data.long_string.m_ptr;
		}

		void reserve(size_type n) {
			// since it will only extend the capacity, so just return back
			UTILITY_IFUNLIKELY(n < capacity()) {
				return;
			}
			UTILITY_IFUNLIKELY(n < max_sso_size) {
				return;
			}
			data_type new_data;
			new_data.long_string.m_capacity = n;
			new_data.long_string.m_size		= size();
			UTILITY_TRY {
				new_data.long_string.m_ptr = alloc_traits::allocate(get_alloc(), n);
				traits_type::copy(new_data.long_string.m_ptr, data(), size());
				if(!is_sso()) {
					traits_type::deallocate(get_alloc(), data(), capacity());
				}
			}
			UTILITY_CATCH(...) {
				UTILITY_THROW_AGAIN
			}
			m_data = new_data;
		}

		void reserve() {
			if(is_sso()) {
				return;
			}
			size_type s = size();
			size_type c = capacity();
			if(s <= max_sso_size) {
				change_normal_to_sso();
			} else if(s < c) {
				UTILITY_TRY {
					pointer tmp = alloc_traits::allocate(get_alloc(), s + 1);
					traits_type::copy(tmp, data(), s + 1);
					traits_type::deallocate(get_alloc(), data(), c + 1);
					set_capacity(s);
					set_ptr(tmp);
				}
				UTILITY_CATCH(...) {
					UTILITY_THROW_AGAIN
				}
			}
		}
	};
} // namespace da

#endif // _UTILITY_SSO_STRING_HPP_
