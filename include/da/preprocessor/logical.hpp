/**
 * @file      logical.hpp
 * @brief     Macros for logical operations
 * @version   0.1
 * @author    dragon-archer
 *
 * @copyright Copyright (c) 2023
 */

#ifndef _DA_PREPROCESSOR_LOGICAL_HPP_
#define _DA_PREPROCESSOR_LOGICAL_HPP_

#include <da/preprocessor/base.hpp>
#include <da/preprocessor/bool.hpp>
#include <da/preprocessor/cat.hpp>
#include <da/preprocessor/conditional.hpp>
#include <da/preprocessor/empty.hpp>

/**
 * @brief Bitnot
 */
#define DA_NOT(x) DA_CAT2(DA_NOT_, DA_BOOL(x))
#define DA_NOT_0  1
#define DA_NOT_1  0

/**
 * @brief Simple logical and, with 2 arguments
 *
 * This is a simple version of logical and.
 * It is faster than DA_AND(), but it supports only exact 2 arguments,
 * and it is not short-circuited.
 */
#define DA_AND2(x, y) DA_CAT(DA_AND2_, DA_BOOL(x), DA_BOOL(y))
#define DA_AND2_00    0
#define DA_AND2_01    0
#define DA_AND2_10    0
#define DA_AND2_11    1

/**
 * @brief Simple logical or, with 2 arguments
 *
 * This is a simple version of logical or.
 * It is faster than DA_OR(), but it supports only exact 2 arguments,
 * and it is not short-circuited.
 */
#define DA_OR2(x, y) DA_CAT(DA_OR2_, DA_BOOL(x), DA_BOOL(y))
#define DA_OR2_00    0
#define DA_OR2_01    1
#define DA_OR2_10    1
#define DA_OR2_11    1

/**
 * @brief Wrappers of basic macros
 */
#define DA_LOGICAL_R_IF()    DA_IF
#define DA_LOGICAL_R_TRUE()  DA_TRUE
#define DA_LOGICAL_R_FALSE() DA_FALSE

/**
 * @brief Logical and, with any arguments
 *
 * This is an enhanced logical and, which allows any number of arguments.
 * It is short-circuited, just like && in normal C++ code.
 *
 * @note Call DA_AND() with no param results to 1
 */
#define DA_AND(...) DA_EXPAND(DA_AND_I(1 __VA_OPT__(, ) __VA_ARGS__))
#define DA_AND_I(x, ...)                                                                  \
	DA_IF(x, DA_LOGICAL_R_IF, DA_EMPTY)                                                   \
	DA_PARENS()                                                                           \
	DA_IF(x, (DA_IS_EMPTY(__VA_ARGS__), DA_LOGICAL_R_TRUE, DA_AND_R), DA_LOGICAL_R_FALSE) \
	DA_PARENS()                                                                           \
	(__VA_ARGS__)
#define DA_AND_R() DA_AND_I

/**
 * @brief Logical or, with any arguments
 *
 * This is an enhanced logical or, which allows any number of arguments.
 * It is short-circuited, just like || in normal C++ code.
 *
 * @note Call DA_OR() with no param results to 0
 */
#define DA_OR(...) DA_EXPAND(DA_OR_I(0 __VA_OPT__(, ) __VA_ARGS__))
#define DA_OR_I(x, ...)                                                                  \
	DA_IF(x, DA_EMPTY, DA_LOGICAL_R_IF)                                                  \
	DA_PARENS()                                                                          \
	DA_IF(x, DA_LOGICAL_R_TRUE, (DA_IS_EMPTY(__VA_ARGS__), DA_LOGICAL_R_FALSE, DA_OR_R)) \
	DA_PARENS()                                                                          \
	(__VA_ARGS__)
#define DA_OR_R() DA_OR_I

#endif // _DA_PREPROCESSOR_LOGICAL_HPP_
