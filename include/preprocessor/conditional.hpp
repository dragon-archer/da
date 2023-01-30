/**
 * @file      conditional.hpp
 * @brief     Conditional operations
 * @version   0.1
 * @author    dragon-archer
 *
 * @copyright Copyright (c) 2023
 */

#ifndef _LIBDA_PREPROCESSOR_CONDITIONAL_HPP_
#define _LIBDA_PREPROCESSOR_CONDITIONAL_HPP_

#include "base.hpp"
#include "bool.hpp"
#include "cat.hpp"
#include "seq.hpp"

/**
 * @section DA_IF
 * @brief   Preprocessor if
 */
#define DA_IF(b, t, f) DA_CAT2(DA_IF_, DA_BOOL(b))(t, f)
#define DA_IF_0(t, f)  f
#define DA_IF_1(t, f)  t

/**
 * @section DA_IF_EMPTY
 * @brief   Detect whether the argument is empty
 */
#define DA_IS_EMPTY(...)   DA_IS_EMPTY_I(DA_EXPAND(__VA_ARGS__))
#define DA_IS_EMTPY_I(...) DA_SEQ_HEAD(__VA_OPT__(0, ) 1)

#endif // _LIBDA_PREPROCESSOR_CONDITIONAL_HPP_
