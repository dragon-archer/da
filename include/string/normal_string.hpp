/**
 * @file      normal_string.hpp
 * @brief     A normal string implemtion
 * @version   0.1
 * @author    dragon-archer (dragon-archer@outlook.com)
 *
 * @copyright Copyright (c) 2022
 */

#ifndef _UTILITY_STRING_NORMAL_STRING_HPP_
#define _UTILITY_STRING_NORMAL_STRING_HPP_

#include "../config.hpp"
#include "string_fwd.hpp"
#include "string_traits.hpp"

namespace da {
	template<typename Char, typename Traits, typename Alloc>
	class normal_string_base : protected string_traits<Char, Traits, Alloc> {
		// If char type isn't pod, then the allocation will fail
		// Since is_pod is depercated in C++20, use is_standard_layout && is_trivial instead
		static_assert(std::is_standard_layout<Char>::value && std::is_trivial<Char>::value, "Char type must be pod");

	private:
		typedef normal_string_base<Char, Traits, Alloc> Self;

	public:
		typedef Traits											   traits_type;
		typedef string_traits<Char, Traits, Alloc>				   string_traits;
		typedef typename traits_type::char_type					   value_type;
		typedef Alloc											   allocator_type;
		typedef std::allocator_traits<allocator_type>			   alloc_traits;
		typedef typename alloc_traits::size_type				   size_type;
		typedef typename alloc_traits::difference_type			   difference_type;
		typedef typename alloc_traits::pointer					   pointer;
		typedef typename alloc_traits::const_pointer			   const_pointer;
		typedef value_type&										   reference;
		typedef const value_type&								   const_reference;
		typedef normal_iterator<pointer, normal_string_base>	   iterator;
		typedef normal_iterator<const_pointer, normal_string_base> const_iterator;
		typedef std::reverse_iterator<iterator>					   reverse_iterator;
		typedef std::reverse_iterator<const_iterator>			   const_reverse_iterator;

		static constexpr size_type npos			  = std::numeric_limits<size_type>::max();
		static constexpr size_type start_capacity = 16; // Capacity should be no less than this

		UTILITY_CONSTEXPR_20 normal_string_base()
			: m_ptr(allocate_n(start_capacity + 1))
			, m_size(0)
			, m_capacity(start_capacity) {
			assign(*data(), Char());
		}

	private:
		pointer	  m_ptr;
		size_type m_size;
		size_type m_capacity;

	public: // Allocators
		constexpr allocator_type& get_alloc() const noexcept {
			// Force convert this to non-const to make it work on const string
			// Required by: max_size()
			return *static_cast<string_traits*>(const_cast<Self*>(this));
		}

		using string_traits::allocate_n;
		using string_traits::assign;
		using string_traits::copy;
		using string_traits::deallocate_n;

	public: // Basic operations
		constexpr size_type size() const noexcept {
			return m_size;
		}

		constexpr size_type capacity() const noexcept {
			return m_capacity;
		}

		constexpr pointer data() const noexcept {
			return m_ptr;
		}

		UTILITY_CONSTEXPR_20 void size(size_type n) noexcept {
			assert(n <= capacity());
			m_size = n;
			assign(data()[n], Char());
		}

		constexpr void capacity(size_type n) noexcept {
			m_capacity = n;
		}

		constexpr void data(pointer p) noexcept {
			m_ptr = p;
		}
	};
} // namespace da

#endif // _UTILITY_STRING_NORMAL_STRING_HPP_
