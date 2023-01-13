/**
 * @file      fold.hpp
 * @brief     Implement macro DA_FOLD
 * @version   0.1
 * @author    dragon-archer
 *
 * @copyright Copyright (c) 2023
 */

#ifndef _LIBDA_PREPROCESSOR_FOLD_HPP_
#define _LIBDA_PREPROCESSOR_FOLD_HPP_

#include "base.hpp"
#include "seq.hpp"

/**
 * @section DA_FOLD
 * @brief   Wrapper of DA_FOLD_LEFT
 */
#define DA_FOLD(macro, ...) __VA_OPT__(DA_FOLD_LEFT(macro, __VA_ARGS__))

/**
 * @section DA_FOLD_LEFT
 * @brief   Left fold with macro
 * @note    The result would be like:
 *          macro(macro(...(macro(_1, _2), _3), ...), _n)
 */
#define DA_FOLD_LEFT(macro, ...) \
	__VA_OPT__(DA_FOLD_LEFT_HELPER(macro, __VA_ARGS__))
#define DA_FOLD_LEFT_HELPER(macro, _1, ...) \
	DA_SEQ_HEAD(DA_EXPAND(__VA_OPT__(DA_FOLD_LEFT_HELPER2(macro, _1, __VA_ARGS__), ) _1))
#define DA_FOLD_LEFT_HELPER2(macro, _1, _2, ...)                                  \
	__VA_OPT__(DA_FOLD_LEFT_AGAIN DA_PARENS(macro, macro(_1, _2), __VA_ARGS__), ) \
	macro(_1, _2)
#define DA_FOLD_LEFT_AGAIN() DA_FOLD_LEFT_HELPER2

#endif // _LIBDA_PREPROCESSOR_FOLD_HPP_
