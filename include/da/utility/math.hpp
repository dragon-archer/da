/* SPDX-License-Identifier: MIT */
/**
 * @file      math.hpp
 * @brief     Some utility math functions
 * @version   0.1
 * @author    dragon-archer (dragon-archer@outlook.com)
 *
 * @copyright Copyright (c) 2022-2023 dragon-archer
 */

#ifndef _DA_UTILITY_MATH_HPP_
#define _DA_UTILITY_MATH_HPP_

#include <da/config.hpp>
#include <da/type_traits/config.hpp>
#include <da/concepts.hpp>
#include <cmath>

DA_BEGIN_NAMESPACE

/**
 * @brief Calculate base^exp
 * @tparam T Any arithmetic type
 * @param base The base number
 * @param exp The exponent, must be integer
 * @return base^exp
 * @note 0^0 returns 0 instead of arithmetic error
 */
template<arithmetic T>
[[nodiscard]] constexpr T pow(T base, ssize_t exp) noexcept {
	if(base == 0 || base == 1) {
		return base;
	}
	if(exp == 0) {
		return 1;
	} else if(exp < 0) {
		if constexpr(std::is_integral_v<T>) {
			DA_IFUNLIKELY(base == 2 && exp == -1) {
				return 1; // 2^(-1) round off to 1
			}
			return 0;
		} else {
			return 1 / pow(base, -exp);
		}
	} else {
		T      ret = 1, tmp = base;
		size_t e = exp;
		while(e) {
			if(e & 1) {
				ret *= tmp;
			}
			tmp *= tmp;
			e >>= 1;
		}
		return ret;
	}
}

DA_END_NAMESPACE

#endif // _DA_UTILITY_MATH_HPP_
