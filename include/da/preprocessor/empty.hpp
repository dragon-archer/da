/* SPDX-License-Identifier: MIT */
/**
 * @file      empty.hpp
 * @brief     Implement DA_IS_EMPTY
 * @version   0.2
 * @author    dragon-archer
 *
 * @copyright Copyright (c) 2023 dragon-archer
 */

#ifndef _DA_PREPROCESSOR_EMPTY_HPP_
#define _DA_PREPROCESSOR_EMPTY_HPP_

#include <da/preprocessor/config.hpp>
#include <da/preprocessor/seq.hpp>

/**
 * @brief Detect whether the argument is empty
 */
#define DA_IS_EMPTY(...)   DA_IS_EMPTY_I(__VA_ARGS__)
#define DA_IS_EMPTY_I(...) DA_SEQ_HEAD(__VA_OPT__(0, ) 1)

#endif // _DA_PREPROCESSOR_EMPTY_HPP_
