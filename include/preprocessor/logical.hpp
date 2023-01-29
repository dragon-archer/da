/**
 * @file      logical.hpp
 * @brief     Macros for logical operations
 * @version   0.1
 * @author    dragon-archer
 *
 * @copyright Copyright (c) 2023
 */

#ifndef _LIBDA_PREPROCESSOR_LOGICAL_HPP_
#define _LIBDA_PREPROCESSOR_LOGICAL_HPP_

#include "bool.hpp"
#include "cat.hpp"


/**
 * @section DA_NOT
 * @brief   Bitnot
 */
#define DA_NOT(x) DA_CAT2(DA_NOT_, DA_BOOL(x))
#define DA_NOT_0  1
#define DA_NOT_1  0

/**
 * @section DA_AND2
 * @brief   Bitand, with 2 arguments
 */
#define DA_AND2(x, y) DA_CAT(DA_AND2_, DA_BOOL(x), DA_BOOL(y))
#define DA_AND2_00    0
#define DA_AND2_01    0
#define DA_AND2_10    0
#define DA_AND2_11    1

/**
 * @section DA_OR2
 * @brief   Bitor, with 2 arguments
 */
#define DA_OR2(x, y) DA_CAT(DA_OR2_, DA_BOOL(x), DA_BOOL(y))
#define DA_OR2_00    0
#define DA_OR2_01    1
#define DA_OR2_10    1
#define DA_OR2_11    1

#endif // _LIBDA_PREPROCESSOR_LOGICAL_HPP_
