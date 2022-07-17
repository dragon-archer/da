/**
 * @file      string_traits.hpp
 * @brief     Common operations of a string
 * @version   0.1
 * @author    dragon-archer (dragon-archer@outlook.com)
 *
 * @copyright Copyright (c) 2022
 */

#ifndef _UTILITY_STRING_STRING_TRAITS_HPP_
#define _UTILITY_STRING_STRING_TRAITS_HPP_

#include "../config.hpp"
#include "string_fwd.hpp"

namespace da {
	template<typename Char, typename Traits, typename Alloc>
	class string_traits : protected Alloc { // Empty-Base Optimization
	public:
		typedef typename Traits::char_type value_type;
		typedef typename Alloc::size_type  size_type;
		typedef value_type*				   pointer;
		typedef const pointer			   const_pointer;
		typedef value_type&				   reference;
		typedef const value_type&		   const_reference;

		operator Alloc() {
			return *static_cast<Alloc*>(this);
		}

		constexpr pointer allocate_n(size_type n) {
			return Alloc::allocate(n + 1); // One more element for '\0'
		}

		constexpr void deallocate_n(pointer p, size_type n) {
			Alloc::deallocate(p, n + 1); // One more element for '\0'
		}

		static constexpr void copy(pointer dest, const_pointer src, size_type n) noexcept {
			Traits::copy(dest, src, n + 1); // One more element for '\0'
		}

		static constexpr void assign(reference dest, const_reference src) noexcept {
			Traits::assign(dest, src);
		}
	};
}

#endif // _UTILITY_STRING_STRING_TRAITS_HPP_
