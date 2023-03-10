/* SPDX-License-Identifier: MIT */
/**
 * @file      cat.hpp
 * @brief     Implement DA_CAT
 * @version   0.1
 * @author    dragon-archer
 *
 * @copyright Copyright (c) 2023 dragon-archer
 */

#ifndef _DA_PREPROCESSOR_CAT_HPP_
#define _DA_PREPROCESSOR_CAT_HPP_

#include <da/preprocessor/config.hpp>
#include <da/preprocessor/fold.hpp>

/**
 * @brief Concat everything
 * 
 * This macro is the super version of DA_CAT2(), and can concat any number of params
 */
#define DA_CAT(...) __VA_OPT__(DA_FOLD(DA_CAT2, __VA_ARGS__))

#endif // _DA_PREPROCESSOR_CAT_HPP_
