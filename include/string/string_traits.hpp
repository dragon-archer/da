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

		constexpr pointer _M_allocate(size_type n) {
			assert(n != 0);
			return Alloc::allocate(n);
		}

		constexpr void _M_deallocate(pointer p, size_type n) {
			assert(p != nullptr && n != 0);
			Alloc::deallocate(p, n);
		}

		static constexpr pointer _S_copy(pointer dest, const_pointer src, size_type n) noexcept {
			UTILITY_IFUNLIKELY(n == 0) {
				return dest;
			}
			UTILITY_IFUNLIKELY(n == 1) {
				_S_assign(*dest, *src);
				return dest;
			}
			return Traits::copy(dest, src, n);
		}

		static constexpr void _S_assign(reference dest, const_reference src) noexcept {
			Traits::assign(dest, src);
		}

		static constexpr pointer _S_assign(pointer dest, size_type n, value_type src) noexcept {
			UTILITY_IFUNLIKELY(n == 0) {
				return dest;
			}
			UTILITY_IFUNLIKELY(n == 1) {
				_S_assign(*dest, src);
				return dest;
			}
			return Traits::assign(dest, n, src);
		}
	};
}

#endif // _UTILITY_STRING_STRING_TRAITS_HPP_
