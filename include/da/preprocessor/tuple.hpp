/* SPDX-License-Identifier: MIT */
/**
 * @file      tuple.hpp
 * @brief     Basic tuple operations
 * @version   0.1
 * @author    dragon-archer
 *
 * @copyright Copyright (c) 2023 dragon-archer
 */

#ifndef _DA_PREPROCESSOR_TUPLE_HPP_
#define _DA_PREPROCESSOR_TUPLE_HPP_

#include <da/preprocessor/base.hpp>
#include <da/preprocessor/conditional.hpp>
#include <da/preprocessor/empty.hpp>
#include <da/preprocessor/seq.hpp>

/**
 * @brief Detect whether it is a tuple
 */
#define DA_IS_TUPLE(...) DA_IS_EMPTY(DA_EMPTY __VA_ARGS__)

/**
 * @brief Unpack tuple
 */
#define DA_TUPLE_UNPACK(x)     DA_TUPLE_UNPACK_I x
#define DA_TUPLE_UNPACK_I(...) __VA_ARGS__

/**
 * @brief Unpack if it is a tuple, else do nothing
 */
#define DA_TUPLE_UNPACK_OPT(...) DA_IF(DA_IS_TUPLE(__VA_ARGS__), DA_TUPLE_UNPACK, DA_IDENTITY)(__VA_ARGS__)

/**
 * @brief Get the size of a tuple
 */
#define DA_TUPLE_SIZE(x) DA_CNT x

/**
 * @brief Get nth element of a tuple
 */
#define DA_TUPLE_GET(n, x) DA_SEQ_GET(n, DA_TUPLE_UNPACK(x))

/**
 * @brief Get the first element of a tuple
 */
#define DA_TUPLE_HEAD(x) DA_SEQ_HEAD x
/**
 * @brief Get the last element of a tuple
 */
#define DA_TUPLE_TAIL(x) DA_SEQ_TAIL x

/**
 * @brief Reverse a tuple
 */
#define DA_TUPLE_REVERSE(x) (DA_SEQ_REVERSE x)

/**
 * @brief Remove the first element of a tuple
 */
#define DA_TUPLE_REMOVE_HEAD(x) (DA_SEQ_REMOVE_HEAD x)

/**
 * @brief Remove the last element of a tuple
 */
#define DA_TUPLE_REMOVE_TAIL(x) (DA_SEQ_REMOVE_TAIL x)

/**
 * @brief Insert at the tail of a tuple
 */
#define DA_TUPLE_INSERT_TAIL(x, ...) (DA_TUPLE_UNPACK(x) __VA_OPT__(, ) __VA_ARGS__)

/**
 * @brief Insert at the front of a tuple
 */
#define DA_TUPLE_INSERT_HEAD(x, ...) (__VA_ARGS__ __VA_OPT__(, ) DA_TUPLE_UNPACK(x))

#endif // _DA_PREPROCESSOR_TUPLE_HPP_
