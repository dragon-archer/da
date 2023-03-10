/* SPDX-License-Identifier: MIT */
/**
 * @file      foreach.hpp
 * @brief     Implement DA_FOREACH macro
 * @version   0.1
 * @author    dragon-archer
 *
 * @copyright Copyright (c) 2023 dragon-archer
 */

#ifndef _DA_PREPROCESSOR_FOREACH_HPP_
#define _DA_PREPROCESSOR_FOREACH_HPP_

#include <da/preprocessor/config.hpp>
#include <da/preprocessor/expand.hpp>

/**
 * @brief This macro implements a basic foreach at preprocess time
 */
#define DA_FOREACH(op, ...) \
	__VA_OPT__(DA_EXPAND(DA_FOREACH_I(op, __VA_ARGS__)))
#define DA_FOREACH_I(op, _1, ...) \
	op(_1) __VA_OPT__(DA_FOREACH_R DA_PARENS()(op, __VA_ARGS__))
#define DA_FOREACH_R() DA_FOREACH_I

#endif // _DA_PREPROCESSOR_FOREACH_HPP_
