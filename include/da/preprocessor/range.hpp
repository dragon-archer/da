/**
 * @file      range.hpp
 * @brief     Range related macros
 * @version   0.1
 * @author    dragon-archer
 *
 * @copyright Copyright (c) 2023
 */

#ifndef _DA_PREPROCESSOR_RANGE_HPP_
#define _DA_PREPROCESSOR_RANGE_HPP_

#include <da/preprocessor/base.hpp>
#include <da/preprocessor/conditional.hpp>
#include <da/preprocessor/logical.hpp>
#include <da/preprocessor/tuple.hpp>

#define DA_IS_RANGE(x) DA_AND2(DA_IS_TUPLE(x), )

#endif // _DA_PREPROCESSOR_RANGE_HPP_
