/**
 * @file      fold.hpp
 * @brief     Implement macro DA_FOLD
 * @version   0.1
 * @author    dragon-archer
 *
 * @copyright Copyright (c) 2023
 */

#ifndef _DA_PREPROCESSOR_FOLD_HPP_
#define _DA_PREPROCESSOR_FOLD_HPP_

#include <da/preprocessor/base.hpp>
#include <da/preprocessor/seq.hpp>

/**
 * @section DA_FOLD
 * @brief   Wrapper of @ref DA_FOLD_LEFT
 */
#define DA_FOLD(op, ...) __VA_OPT__(DA_FOLD_LEFT(op, __VA_ARGS__))

/**
 * @section DA_FOLD_LEFT
 * @brief   Left fold with @param op
 * @note    The result would be like:
 *          op(op(...(op(_1, _2), _3), ...), _n)
 */
#define DA_FOLD_LEFT(op, ...) \
	__VA_OPT__(DA_FOLD_LEFT_I(op, __VA_ARGS__))
#define DA_FOLD_LEFT_I(op, _1, ...) \
	DA_SEQ_HEAD(DA_EXPAND(__VA_OPT__(DA_FOLD_LEFT_II(op, _1, __VA_ARGS__), ) _1))
#define DA_FOLD_LEFT_II(op, _1, _2, ...)                                  \
	__VA_OPT__(DA_FOLD_LEFT_R DA_PARENS()(op, op(_1, _2), __VA_ARGS__), ) \
	op(_1, _2)
#define DA_FOLD_LEFT_R() DA_FOLD_LEFT_II

#endif // _DA_PREPROCESSOR_FOLD_HPP_
