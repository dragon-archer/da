/* SPDX-License-Identifier: MIT */
/**
 * @file      conditional.hpp
 * @brief     Conditional operations
 * @version   0.2
 * @author    dragon-archer
 *
 * @copyright Copyright (c) 2023 dragon-archer
 */

#ifndef _DA_PREPROCESSOR_CONDITIONAL_HPP_
#define _DA_PREPROCESSOR_CONDITIONAL_HPP_

#include <da/preprocessor/config.hpp>
#include <da/preprocessor/bool.hpp>

/**
 * @brief Conditional support
 */
#define DA_IF(b, t, f) DA_CAT2(DA_IF_, DA_BOOL(b))(t, f)
#define DA_IF_0(t, f)  f
#define DA_IF_1(t, f)  t

#endif // _DA_PREPROCESSOR_CONDITIONAL_HPP_
