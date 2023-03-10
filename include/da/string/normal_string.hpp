/* SPDX-License-Identifier: MIT */
/**
 * @file      normal_string.hpp
 * @brief     A normal string implemtion
 * @version   0.1
 * @author    dragon-archer (dragon-archer@outlook.com)
 *
 * @copyright Copyright (c) 2022-2023 dragon-archer
 */

#ifndef _DA_STRING_NORMAL_STRING_HPP_
#define _DA_STRING_NORMAL_STRING_HPP_

#include <da/config.hpp>
#include <da/string/string_fwd.hpp>
#include <da/string/string_traits.hpp>

DA_BEGIN_NAMESPACE

template<typename Char, typename Traits, typename Alloc>
class normal_string_base : protected string_traits<Char, Traits, Alloc> {
	typedef normal_string_base<Char, Traits, Alloc> Self;

	public:
	typedef Traits                                             traits_type;
	typedef string_traits<Char, Traits, Alloc>                 string_traits;
	typedef typename traits_type::char_type                    value_type;
	typedef Alloc                                              allocator_type;
	typedef std::allocator_traits<allocator_type>              alloc_traits;
	typedef typename alloc_traits::size_type                   size_type;
	typedef typename alloc_traits::difference_type             difference_type;
	typedef typename alloc_traits::pointer                     pointer;
	typedef typename alloc_traits::const_pointer               const_pointer;
	typedef value_type&                                        reference;
	typedef const value_type&                                  const_reference;
	typedef normal_iterator<pointer, normal_string_base>       iterator;
	typedef normal_iterator<const_pointer, normal_string_base> const_iterator;
	typedef std::reverse_iterator<iterator>                    reverse_iterator;
	typedef std::reverse_iterator<const_iterator>              const_reverse_iterator;

	static constexpr size_type npos = std::numeric_limits<size_type>::max();

	constexpr normal_string_base() noexcept
		: m_ptr(nullptr)
		, m_size(0)
		, m_capacity(0) {
	}

	private:
	pointer   m_ptr;
	size_type m_size;
	size_type m_capacity;

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

	constexpr void _M_size(size_type n) noexcept {
		assert(n <= capacity());
		m_size = n;
		_S_assign(data()[n], Char());
	}

	constexpr void _M_capacity(size_type n) noexcept {
		m_capacity = n;
	}

	constexpr void _M_data(pointer p) noexcept {
		m_ptr = p;
	}
};

DA_END_NAMESPACE

#endif // _DA_STRING_NORMAL_STRING_HPP_
