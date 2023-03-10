/* SPDX-License-Identifier: MIT */
/**
 * @file      expand.hpp
 * @brief     Implement DA_EXPAND
 * @version   0.1
 * @author    dragon-archer
 *
 * @copyright Copyright (c) 2023 dragon-archer
 */

#ifndef _DA_PREPROCESSOR_EXPAND_HPP_
#define _DA_PREPROCESSOR_EXPAND_HPP_

#include <da/preprocessor/base.hpp>
#include <da/preprocessor/conditional.hpp>

// clang-format off

/**
 * @brief Detect which depth of macro has been used
 */
#define DA_AUTO_DIM(check) DA_IF(check(2), DA_AUTO_DIM_2, DA_AUTO_DIM_3)(check)
	#define DA_AUTO_DIM_2(check) DA_IF(check(1), 1, 2)
	#define DA_AUTO_DIM_3(check) DA_IF(check(3), 3, 4)

// clang-format on

/**
 * @brief Fully expand anything
 *
 * This macro is mainly used to enable a macro to repeat itself
 * Since macros can not reentrant by default, this macro simulate the reentrance
 * This macro can reenter 4 times at most
 *
 * @see DA_FOREACH()
 */
#define DA_EXPAND                      DA_CAT2(DA_EXPAND_, DA_AUTO_DIM(DA_EXPAND_CHECK))
#define DA_EXPAND_CHECK(n)             DA_CAT2(DA_EXPAND_CHECK_, DA_EXPAND_##n(1))
#define DA_EXPAND_CHECK_1              1
#define DA_EXPAND_CHECK_DA_EXPAND_1(x) 0
#define DA_EXPAND_CHECK_DA_EXPAND_2(x) 0
#define DA_EXPAND_CHECK_DA_EXPAND_3(x) 0
#define DA_EXPAND_CHECK_DA_EXPAND_4(x) 0

#define DA_EXPAND_1(...)   DA_EXPAND_1_1(DA_EXPAND_1_1(DA_EXPAND_1_1(DA_EXPAND_1_1(__VA_ARGS__))))
#define DA_EXPAND_1_1(...) DA_EXPAND_1_2(DA_EXPAND_1_2(DA_EXPAND_1_2(DA_EXPAND_1_2(__VA_ARGS__))))
#define DA_EXPAND_1_2(...) DA_EXPAND_1_3(DA_EXPAND_1_3(DA_EXPAND_1_3(DA_EXPAND_1_3(__VA_ARGS__))))
#define DA_EXPAND_1_3(...) DA_EXPAND_1_4(DA_EXPAND_1_4(DA_EXPAND_1_4(DA_EXPAND_1_4(__VA_ARGS__))))
#define DA_EXPAND_1_4(...) __VA_ARGS__

#define DA_EXPAND_2(...)   DA_EXPAND_2_1(DA_EXPAND_2_1(DA_EXPAND_2_1(DA_EXPAND_2_1(__VA_ARGS__))))
#define DA_EXPAND_2_1(...) DA_EXPAND_2_2(DA_EXPAND_2_2(DA_EXPAND_2_2(DA_EXPAND_2_2(__VA_ARGS__))))
#define DA_EXPAND_2_2(...) DA_EXPAND_2_3(DA_EXPAND_2_3(DA_EXPAND_2_3(DA_EXPAND_2_3(__VA_ARGS__))))
#define DA_EXPAND_2_3(...) DA_EXPAND_2_4(DA_EXPAND_2_4(DA_EXPAND_2_4(DA_EXPAND_2_4(__VA_ARGS__))))
#define DA_EXPAND_2_4(...) __VA_ARGS__

#define DA_EXPAND_3(...)   DA_EXPAND_3_1(DA_EXPAND_3_1(DA_EXPAND_3_1(DA_EXPAND_3_1(__VA_ARGS__))))
#define DA_EXPAND_3_1(...) DA_EXPAND_3_2(DA_EXPAND_3_2(DA_EXPAND_3_2(DA_EXPAND_3_2(__VA_ARGS__))))
#define DA_EXPAND_3_2(...) DA_EXPAND_3_3(DA_EXPAND_3_3(DA_EXPAND_3_3(DA_EXPAND_3_3(__VA_ARGS__))))
#define DA_EXPAND_3_3(...) DA_EXPAND_3_4(DA_EXPAND_3_4(DA_EXPAND_3_4(DA_EXPAND_3_4(__VA_ARGS__))))
#define DA_EXPAND_3_4(...) __VA_ARGS__

#define DA_EXPAND_4(...)   DA_EXPAND_4_1(DA_EXPAND_4_1(DA_EXPAND_4_1(DA_EXPAND_4_1(__VA_ARGS__))))
#define DA_EXPAND_4_1(...) DA_EXPAND_4_2(DA_EXPAND_4_2(DA_EXPAND_4_2(DA_EXPAND_4_2(__VA_ARGS__))))
#define DA_EXPAND_4_2(...) DA_EXPAND_4_3(DA_EXPAND_4_3(DA_EXPAND_4_3(DA_EXPAND_4_3(__VA_ARGS__))))
#define DA_EXPAND_4_3(...) DA_EXPAND_4_4(DA_EXPAND_4_4(DA_EXPAND_4_4(DA_EXPAND_4_4(__VA_ARGS__))))
#define DA_EXPAND_4_4(...) __VA_ARGS__

#define DA_EXPAND_MAX 256

#endif // _DA_PREPROCESSOR_EXPAND_HPP_
