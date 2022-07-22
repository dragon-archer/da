/**
 * @file      sso_string.hpp
 * @brief     A string implemtion to optimize short strings
 * @version   0.1
 * @author    dragon-archer (dragon-archer@outlook.com)
 *
 * @copyright Copyright (c) 2022
 */

#ifndef _DA_STRING_SSO_STRING_HPP_
#define _DA_STRING_SSO_STRING_HPP_

#include "../config.hpp"
#include "string_fwd.hpp"
#include "string_traits.hpp"

namespace da {
	template<typename Char, typename Traits, typename Alloc>
	class sso_string_base : protected string_traits<Char, Traits, Alloc> {
		// If char type isn't pod, then the allocation will fail
		// Since is_pod is depercated in C++20, use is_standard_layout && is_trivial instead
		static_assert(std::is_standard_layout<Char>::value && std::is_trivial<Char>::value, "Char type must be pod");
		// Char size should be less than 8(max_sso_size should be at least 1), otherwise it can't be optimized
		static_assert(sizeof(Char) <= 8, "Char size should be less than 8 bytes, otherwise it can't be optimized");

		typedef sso_string_base<Char, Traits, Alloc> Self;

	public:
		typedef Traits											traits_type;
		typedef string_traits<Char, Traits, Alloc>				string_traits;
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
			: m_data { .short_string = { 0x80, { '\0' } } } { }

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
				uint8_t	   m_size;
				value_type m_ptr[max_sso_size + 1]; // One more Char for '\0'
			} short_string;
			struct {
				size_type m_size;
				size_type m_capacity;
				pointer	  m_ptr;
			} long_string;
		} m_data;

	protected: // Internal functions used by da::string
		// Check whether the string is optimized
		constexpr bool is_sso() const noexcept {
			return (*reinterpret_cast<const uint8_t* const>(&m_data)) & (0x80);
		}

		DA_CONSTEXPR_20 void change_sso_to_normal() {
			DA_IFUNLIKELY(!is_sso()) {
				return;
			}
			data_type new_data;
			size_type s						= size();
			new_data.long_string.m_capacity = 32 / sizeof(value_type); // nearest power of 2 that bigger than max_sso_size
			new_data.long_string.m_ptr		= _M_create(new_data.long_string.m_capacity, max_sso_size);
			_S_copy(new_data.long_string.m_ptr, data(), s);
			m_data = new_data;
			_M_size(s);
		}

		DA_CONSTEXPR_20 void change_normal_to_sso() {
			DA_IFUNLIKELY(is_sso()) {
				return;
			}
			DA_IFUNLIKELY(size() > max_sso_size) {
				DA_THROW(std::out_of_range(format::format("da::sso_string_base::change_normal_to_sso: Current size (which is {}) exceeds max_sso_size (which is {})", size(), max_sso_size)));
			}
			data_type new_data;
			size_type s = size();
			// Since new_data is allocated on stack, it should not throw errors
			_S_copy(new_data.short_string.m_ptr, data(), s);
			_M_dispose();
			m_data = new_data;
			_M_size(s);
		}

	public: // Allocators
		constexpr allocator_type& _M_get_alloc() const noexcept {
			// Force convert this to non-const to make it work on const string
			// Required by: max_size()
			return *static_cast<string_traits*>(const_cast<Self*>(this));
		}

		using string_traits::_M_allocate;
		using string_traits::_M_deallocate;
		using string_traits::_S_assign;
		using string_traits::_S_copy;

		DA_CONSTEXPR_20 pointer _M_create(size_type& new_capacity, size_type old_capacity) {
			DA_IFUNLIKELY(new_capacity > max_size()) {
				DA_THROW(std::length_error(format::format("da::sso_string_base::_M_create: The new capacity (which is {}) > max_size() (which is {})", new_capacity, max_size())));
			}
			if(size() == 0 && new_capacity <= max_sso_size) { // Optimize for constructers
				new_capacity = max_sso_size;
				change_normal_to_sso();
				return data();
			}
			if(new_capacity > old_capacity && new_capacity < 2 * old_capacity) {
				new_capacity = 2 * old_capacity;
				if(new_capacity > max_size()) {
					new_capacity = max_size();
				}
			}
			return _M_allocate(new_capacity + 1); // One more element for '\0'
		}

		DA_CONSTEXPR_20 void _M_dispose() {
			if(!is_sso()) {
				_M_destroy(capacity());
			}
		}

		DA_CONSTEXPR_20 void _M_destroy(size_type n) {
			if(!is_sso() && data() != nullptr) {
				_M_deallocate(data(), n + 1);
			}
		}

	public: // Basic operations
		constexpr size_type size() const noexcept {
			return is_sso() ? static_cast<size_type>(m_data.short_string.m_size - 0x80) // SSO bit
							: m_data.long_string.m_size;
		}

		constexpr size_type capacity() const noexcept {
			return is_sso() ? max_sso_size
							: m_data.long_string.m_capacity;
		}

		constexpr pointer data() const noexcept {
			return is_sso() ? const_cast<pointer>(static_cast<const_pointer>(m_data.short_string.m_ptr))
							: m_data.long_string.m_ptr;
		}

		constexpr size_type max_size() const noexcept {
			return npos - 1;
		}

		DA_CONSTEXPR_20 void _M_size(size_type n) noexcept {
			assert(n <= capacity());
			if(is_sso()) {
				m_data.short_string.m_size = static_cast<uint8_t>(n + 0x80);
			} else {
				m_data.long_string.m_size = n;
			}
			_S_assign(data()[n], Char());
		}

		constexpr void _M_capacity(size_type n) noexcept {
			if(!is_sso()) {
				m_data.long_string.m_capacity = n;
			} else {
				if(n > max_sso_size) {
					change_sso_to_normal();
					m_data.long_string.m_capacity = n;
				}
			}
		}

		constexpr void _M_data(pointer p) noexcept {
			if(!is_sso()) {
				m_data.long_string.m_ptr = p;
			} else {
				if(p != data()) {
					data_type new_data;
					new_data.long_string.m_ptr		= p;
					new_data.long_string.m_capacity = capacity();
					new_data.long_string.m_size		= size();
					m_data							= new_data;
				}
			}
		}

	public:
		DA_CONSTEXPR_20 void reserve() {
			if(is_sso()) {
				return;
			}
			size_type s = size();
			size_type c = capacity();
			if(s <= max_sso_size) {
				change_normal_to_sso();
			} else if(s < c) {
				pointer tmp = _M_create(s, 0);
				_S_copy(tmp, data(), s + 1);
				_M_dispose();
				_M_data(tmp);
				_M_capacity(s);
			}
		}

		DA_CONSTEXPR_20 void swap(const Self& s) {
			std::swap(m_data, s.m_data);
		}
	};
} // namespace da

#endif // _DA_STRING_SSO_STRING_HPP_
