/**
 * @file      while.hpp
 * @brief     Implement DA_WHILE
 * @version   0.1
 * @author    dragon-archer
 *
 * @copyright Copyright (c) 2023
 */

#ifndef _DA_PREPROCESSOR_WHILE_HPP_
#define _DA_PREPROCESSOR_WHILE_HPP_

#include <da/preprocessor/base.hpp>
#include <da/preprocessor/expand.hpp>

/**
 * @brief Perform a while loop
 * @param pred The predictor
 * @param op The iterate operation
 * @param data The initial data
 *
 * As long as pred(data) returns 1,
 * the loop will continue with DA_WHILE(pred, op, op(data))
 * When pred(data) returns 0, the loop will return the data now
 */
#define DA_WHILE(pred, op, data) \
	DA_EXPAND(DA_WHILE_I(pred, op, data))
#define DA_WHILE_I(pred, op, data)          \
	DA_IF(pred(data), DA_WHILE_R, DA_EMPTY) \
	DA_PARENS()                             \
	DA_IF(pred(data), (pred, op, op(data)), data)
#define DA_WHILE_R() DA_WHILE_I

#endif // _DA_PREPROCESSOR_WHILE_HPP_
