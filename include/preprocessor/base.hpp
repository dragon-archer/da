/**
 * @file      base.hpp
 * @brief     Basic fetures of libda/preprocessor
 * @version   0.1
 * @author    dragon-archer
 *
 * @copyright Copyright (c) 2023
 */

#ifndef _LIBDA_PREPROCESSOR_BASE_HPP_
#define _LIBDA_PREPROCESSOR_BASE_HPP_

/**
 * @section DA_PARENS
 * @brief   A simple pair of parens, used to let it expand later
 */
#define DA_PARENS ()

/**
 * @section DA_HAS_VA_OPT
 * @brief   Test whether the compiler support `__VA_OPT__`, if not then define it
 * @note    The trailing comma in `DA_HAS_VA_OPT_HELPER` is used to remove warning of zero arguments in `...`
 */
#define DA_HAS_VA_OPT                          DA_HAS_VA_OPT_HELPER(dummy)
#define DA_HAS_VA_OPT_HELPER(...)              DA_HAS_VA_OPT_HELPER_2(__VA_OPT__(, ), 1, 0, )
#define DA_HAS_VA_OPT_HELPER_2(_1, _2, x, ...) x
#if !DA_HAS_VA_OPT
	#warning "The compiler doesn't support __VA_OPT__, some macros might fail"
	#define __VA_OPT__(x) x
#endif

/**
 * @section DA_STR
 * @brief   A basic macro to stringfy everything
 */
#define DA_STR(x)        DA_STR_HELPER(x)
#define DA_STR_HELPER(x) #x

/**
 * @section DA_CNT
 * @brief   A macro to get the count of args
 */
#define DA_CNT(...) DA_CNT_HELPER(__VA_ARGS__ __VA_OPT__(, ) 64, 63, 62, 61, 60, 59, 58, 57, 56, 55, 54, 53, 52, 51, 50, 49, 48, 47, 46, 45, 44, 43, 42, 41, 40, 39, 38, 37, 36, 35, 34, 33, 32, 31, 30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0)

#define DA_CNT_HELPER(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43, _44, _45, _46, _47, _48, _49, _50, _51, _52, _53, _54, _55, _56, _57, _58, _59, _60, _61, _62, _63, _64, x, ...) x

#define DA_CNT_MAX 64

/**
 * @section DA_EXPAND
 * @brief   Fully expand anything
 * @note    This macro is mainly used to enable a macro to repeat itself
 *          You can @see DA_FOREACH and @see DA_FOLD_LEFT for detailed usage
 */
#define DA_EXPAND(...)  DA_EXPAND1(DA_EXPAND1(DA_EXPAND1(DA_EXPAND1(__VA_ARGS__))))
#define DA_EXPAND1(...) DA_EXPAND2(DA_EXPAND2(DA_EXPAND2(DA_EXPAND2(__VA_ARGS__))))
#define DA_EXPAND2(...) DA_EXPAND3(DA_EXPAND3(DA_EXPAND3(DA_EXPAND3(__VA_ARGS__))))
#define DA_EXPAND3(...) DA_EXPAND4(DA_EXPAND4(DA_EXPAND4(DA_EXPAND4(__VA_ARGS__))))
#define DA_EXPAND4(...) __VA_ARGS__

#define DA_EXPAND_MAX 256

#endif // _LIBDA_PREPROCESSOR_BASE_HPP_
