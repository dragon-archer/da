/**
 * @file      preprocessor.hpp
 * @brief     A set of useful macros
 * @version   0.1
 * @author    dragon-archer (dragon-archer@outlook.com)
 * @note      Most of the macros in this file support 10 arguments at most, you may extend this limit by yourself
 *
 * @copyright Copyright (c) 2022
 */

#ifndef _UTILITY_PREPROCESSOR_HPP_
#define _UTILITY_PREPROCESSOR_HPP_

#include "config.hpp"

/**
 * @brief Test whether the compiler support `__VA_OPT__`
 * @note  The trailing comma in `UTILITY_HAS_VA_OPT_HELPER_1` is used to remove warning of zero arguments in `...`
 */
#define UTILITY_HAS_VA_OPT_HELPER_2(_1, _2, x, ...) x
#define UTILITY_HAS_VA_OPT_HELPER(...)				UTILITY_HAS_VA_OPT_HELPER_2(__VA_OPT__(, ), 1, 0, )
#define UTILITY_HAS_VA_OPT							UTILITY_HAS_VA_OPT_HELPER(dummy)

/**
 * @brief A base macro to stringfy everything
 */
#define UTILITY_STR_HELPER(x) #x
#define UTILITY_STR(x)		  UTILITY_STR_HELPER(x)

/**
 * @brief A macro to get the count of args
 * @note  To make it work with zero argument, it need the support of `__VA_OPT__` since C++20
 * @note  The max number or arguments is 64
 */
#define UTILITY_VA_COUNT_HELPER(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43, _44, _45, _46, _47, _48, _49, _50, _51, _52, _53, _54, _55, _56, _57, _58, _59, _60, _61, _62, _63, _64, x, ...) x

#if UTILITY_HAS_VA_OPT
#define UTILITY_VA_COUNT(...) UTILITY_VA_COUNT_HELPER(__VA_ARGS__ __VA_OPT__(, ) 64, 63, 62, 61, 60, 59, 58, 57, 56, 55, 54, 53, 52, 51, 50, 49, 48, 47, 46, 45, 44, 43, 42, 41, 40, 39, 38, 37, 36, 35, 34, 33, 32, 31, 30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0)
#else
#define UTILITY_VA_COUNT(...) UTILITY_VA_COUNT_HELPER(__VA_ARGS__, 64, 63, 62, 61, 60, 59, 58, 57, 56, 55, 54, 53, 52, 51, 50, 49, 48, 47, 46, 45, 44, 43, 42, 41, 40, 39, 38, 37, 36, 35, 34, 33, 32, 31, 30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1)
#endif

/**
 * @brief The following helpers are used to make the macro expand correctly
 */
#define UTILITY_CONCAT_1_HELPER(_1)										  _1 // For compatiblity
#define UTILITY_CONCAT_2_HELPER(_1, _2)									  _1##_2
#define UTILITY_CONCAT_3_HELPER(_1, _2, _3)								  _1##_2##_3
#define UTILITY_CONCAT_4_HELPER(_1, _2, _3, _4)							  _1##_2##_3##_4
#define UTILITY_CONCAT_5_HELPER(_1, _2, _3, _4, _5)						  _1##_2##_3##_4##_5
#define UTILITY_CONCAT_6_HELPER(_1, _2, _3, _4, _5, _6)					  _1##_2##_3##_4##_5##_6
#define UTILITY_CONCAT_7_HELPER(_1, _2, _3, _4, _5, _6, _7)				  _1##_2##_3##_4##_5##_6##_7
#define UTILITY_CONCAT_8_HELPER(_1, _2, _3, _4, _5, _6, _7, _8)			  _1##_2##_3##_4##_5##_6##_7##_8
#define UTILITY_CONCAT_9_HELPER(_1, _2, _3, _4, _5, _6, _7, _8, _9)		  _1##_2##_3##_4##_5##_6##_7##_8##_9
#define UTILITY_CONCAT_10_HELPER(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10) _1##_2##_3##_4##_5##_6##_7##_8##_9##_10

#define UTILITY_CONCAT_1(_1)									   UTILITY_CONCAT_1_HELPER(_1)
#define UTILITY_CONCAT_2(_1, _2)								   UTILITY_CONCAT_2_HELPER(_1, _2)
#define UTILITY_CONCAT_3(_1, _2, _3)							   UTILITY_CONCAT_3_HELPER(_1, _2, _3)
#define UTILITY_CONCAT_4(_1, _2, _3, _4)						   UTILITY_CONCAT_4_HELPER(_1, _2, _3, _4)
#define UTILITY_CONCAT_5(_1, _2, _3, _4, _5)					   UTILITY_CONCAT_5_HELPER(_1, _2, _3, _4, _5)
#define UTILITY_CONCAT_6(_1, _2, _3, _4, _5, _6)				   UTILITY_CONCAT_6_HELPER(_1, _2, _3, _4, _5, _6)
#define UTILITY_CONCAT_7(_1, _2, _3, _4, _5, _6, _7)			   UTILITY_CONCAT_7_HELPER(_1, _2, _3, _4, _5, _6, _7)
#define UTILITY_CONCAT_8(_1, _2, _3, _4, _5, _6, _7, _8)		   UTILITY_CONCAT_8_HELPER(_1, _2, _3, _4, _5, _6, _7, _8)
#define UTILITY_CONCAT_9(_1, _2, _3, _4, _5, _6, _7, _8, _9)	   UTILITY_CONCAT_9_HELPER(_1, _2, _3, _4, _5, _6, _7, _8, _9)
#define UTILITY_CONCAT_10(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10) UTILITY_CONCAT_10_HELPER(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10)

/**
 * @note This is actually the same as `UTILITY_CONCAT_2`
 *       By using a different macro, it can work with exactly 2 arguments
 */
#define UTILITY_CONCAT_HELPER(_1, _2) UTILITY_CONCAT_2_HELPER(_1, _2)

#define UTILITY_CONCAT(...) UTILITY_CONCAT_HELPER(UTILITY_CONCAT_, UTILITY_VA_COUNT(__VA_ARGS__))(__VA_ARGS__)

#endif // _UTILITY_PREPROCESSOR_HPP_
