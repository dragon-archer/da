/* SPDX-License-Identifier: MIT */
/**
 * @file      fold.hpp
 * @brief     Implement macro DA_FOLD
 * @version   0.1
 * @author    dragon-archer
 *
 * @copyright Copyright (c) 2023 dragon-archer
 */

#ifndef _DA_PREPROCESSOR_FOLD_HPP_
#define _DA_PREPROCESSOR_FOLD_HPP_

#include <da/preprocessor/config.hpp>
#include <da/preprocessor/expand.hpp>
#include <da/preprocessor/seq.hpp>

/**
 * @brief Wrapper of DA_FOLD_LEFT()
 */
#define DA_FOLD(op, ...) __VA_OPT__(DA_FOLD_LEFT(op, __VA_ARGS__))

/**
 * @brief Left fold with op(x, y)
 * 
 * The result would be like: 
 * op(op(...(op(_1, _2), _3), ...), _n)
 * 
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
