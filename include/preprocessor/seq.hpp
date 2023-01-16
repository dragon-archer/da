/**
 * @file      seq.hpp
 * @brief     Macros for sequence operations
 * @version   0.1
 * @author    dragon-archer
 * @note      In this header, the term "sequence" means:
 *            1. Empty, contains nothing
 *            2. A comma separated list, while the length is not limited
 * @note      Though there is no hard limits of the sequence length,
 *            it's recommended not to exceed DA_EXPAND_MAX (currently 256),
 *            or some of the macros might fail.
 *
 * @copyright Copyright (c) 2023
 */

#ifndef _LIBDA_PREPROCESSOR_SEQ_HPP_
#define _LIBDA_PREPROCESSOR_SEQ_HPP_

#include "base.hpp"

/**
 * @section DA_SEQ_HEAD
 * @brief   Simply return the first element of a sequence
 */
#define DA_SEQ_HEAD(...)              __VA_OPT__(DA_SEQ_HEAD_HELPER(__VA_ARGS__))
#define DA_SEQ_HEAD_HELPER(head, ...) head

/**
 * @section DA_SEQ_REVERSE
 * @brief   Reverse a sequence
 */
#define DA_SEQ_REVERSE(...) \
	__VA_OPT__(DA_EXPAND(DA_SEQ_REVERSE_HELPER(__VA_ARGS__)))
#define DA_SEQ_REVERSE_HELPER(head, ...)                      \
	__VA_OPT__(DA_SEQ_REVERSE_AGAIN DA_PARENS(__VA_ARGS__), ) \
	head
#define DA_SEQ_REVERSE_AGAIN() DA_SEQ_REVERSE_HELPER

/**
 * @section DA_SEQ_TAIL
 * @brief   Returns the last element of a sequence
 */
#define DA_SEQ_TAIL(...) DA_SEQ_HEAD(DA_SEQ_REVERSE(__VA_ARGS__))

#endif // _LIBDA_PREPROCESSOR_SEQ_HPP_
