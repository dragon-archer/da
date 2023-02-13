/**
 * @file      arithmatic.hpp
 * @brief     Arithmatic macros
 * @version   0.1
 * @author    dragon-archer
 *
 * @copyright Copyright (c) 2023
 */

#ifndef _DA_PREPROCESSOR_ARITHMATIC_HPP_
#define _DA_PREPROCESSOR_ARITHMATIC_HPP_

#include <da/preprocessor/base.hpp>
#include <da/preprocessor/dec.hpp>
#include <da/preprocessor/inc.hpp>
#include <da/preprocessor/while.hpp>

/**
 * @brief Add 2 numbers
 * @note The 2 numbers should all be positive
 *       The result must not exceed 256
 */
#define DA_ADD(x, y) DA_TUPLE_GET(0, DA_WHILE(DA_ADD_P, DA_ADD_O, (x, y)))
#define DA_ADD_P(d)  DA_TUPLE_GET(1, d)
#define DA_ADD_O(d)  (DA_INC(DA_TUPLE_GET(0, d)), DA_DEC(DA_TUPLE_GET(1, d)))

/**
 * @brief Subtract 2 numbers
 * @note The 2 numbers should all be positive,
 *       and the first number should be greater equal than the second
 */
#define DA_SUB(x, y) DA_TUPLE_GET(0, DA_WHILE(DA_SUB_P, DA_SUB_O, (x, y)))
#define DA_SUB_P(d)  DA_TUPLE_GET(1, d)
#define DA_SUB_O(d)  (DA_DEC(DA_TUPLE_GET(0, d)), DA_DEC(DA_TUPLE_GET(1, d)))

#endif // _DA_PREPROCESSOR_ARITHMATIC_HPP_
