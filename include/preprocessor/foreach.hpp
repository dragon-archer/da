/**
 * @file      foreach.hpp
 * @brief     Implement DA_FOREACH macro
 * @version   0.1
 * @author    dragon-archer
 *
 * @copyright Copyright (c) 2023
 */

#ifndef _LIBDA_PREPROCESSOR_FOREACH_HPP_
#define _LIBDA_PREPROCESSOR_FOREACH_HPP_

#include "base.hpp"

/**
 * @section DA_FOREACH
 * @brief   This macro implements a basic foreach at preprocess time
 */
#define DA_FOREACH(macro, ...) \
	__VA_OPT__(DA_EXPAND(DA_FOREACH_HELPER(macro, __VA_ARGS__)))
#define DA_FOREACH_HELPER(macro, _1, ...) \
	macro(_1) __VA_OPT__(DA_FOREACH_AGAIN DA_PARENS(macro, __VA_ARGS__))
#define DA_FOREACH_AGAIN() DA_FOREACH_HELPER

#endif // _LIBDA_PREPROCESSOR_FOREACH_HPP_
