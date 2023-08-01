/* SPDX-License-Identifier: MIT */
/**
 * @file      compare.hpp
 * @brief     Compare operations
 * @version   0.2
 * @author    dragon-archer
 *
 * @copyright Copyright (c) 2023 dragon-archer
 */

#ifndef _DA_PREPROCESSOR_COMPARE_HPP_
#define _DA_PREPROCESSOR_COMPARE_HPP_

#include <da/preprocessor/dec.hpp>
#include <da/preprocessor/logical.hpp>
#include <da/preprocessor/tuple.hpp>
#include <da/preprocessor/while.hpp>

/**
 * @brief Helper macro for compare
 *
 * Returns a two-element tuple, with at least one 0
 */
#define DA_CMP(x, y) DA_WHILE(DA_CMP_P, DA_CMP_O, (x, y))
#define DA_CMP_P(d)  DA_AND2(DA_TUPLE_HEAD(d), DA_TUPLE_GET(1, d))
#define DA_CMP_O(d)  (DA_DEC(DA_TUPLE_HEAD(d)), DA_DEC(DA_TUPLE_GET(1, d)))

/**
 * @return 1 if x == y, 0 otherwise
 */
#define DA_EQUAL(x, y)   DA_IDENTITY(DA_EQUAL_I DA_CMP(x, y))
#define DA_EQUAL_I(x, y) DA_NOR2(x, y)

/**
 * @return 1 if x != y, 0 otherwise
 */
#define DA_NOT_EQUAL(x, y) DA_NOT(DA_EQUAL(x, y))

/**
 * @return 1 if x < y, 0 otherwise
 */
#define DA_LESS(x, y)   DA_IDENTITY(DA_LESS_I DA_CMP(x, y))
#define DA_LESS_I(x, y) DA_AND2(DA_NOT(x), y)

/**
 * @return 1 if x > y, 0 otherwise
 */
#define DA_GREATER(x, y) DA_LESS(y, x)

/**
 * @return 1 if x <= y, 0 otherwise
 */
#define DA_LESS_EQUAL(x, y) DA_NOT(DA_LESS(y, x))

/**
 * @return 1 if x >= y, 0 otherwise
 */
#define DA_GREATER_EQUAL(x, y) DA_NOT(DA_LESS(x, y))

#endif // _DA_PREPROCESSOR_COMPARE_HPP_
