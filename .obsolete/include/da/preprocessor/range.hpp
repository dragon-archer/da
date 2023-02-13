/**
 * @file      range.hpp
 * @brief     Range related macros
 * @version   0.1
 * @author    dragon-archer
 *
 * The term "range" means:
 * 1. A 3-element tuple
 * 2. Each element is a number
 * 3. Ordered as (start, stop, step)
 *
 * @copyright Copyright (c) 2023
 */

#ifndef _DA_PREPROCESSOR_RANGE_HPP_
#define _DA_PREPROCESSOR_RANGE_HPP_

#include <da/preprocessor/base.hpp>
#include <da/preprocessor/compare.hpp>
#include <da/preprocessor/conditional.hpp>
#include <da/preprocessor/logical.hpp>
#include <da/preprocessor/tuple.hpp>

#define DA_IS_RANGE(x)          DA_AND2(DA_IS_TUPLE(x), DA_LESS_EQUAL(DA_TUPLE_SIZE(x), 3))
#define DA_IS_STANDARD_RANGE(x) DA_AND2(DA_IS_TUPLE(x), DA_EQUAL(DA_TUPLE_SIZE(x), 3))

#define DA_RANGE_STANDARDIZE(x)   DA_CAT2(DA_RANGE_STANDARDIZE_, DA_TUPLE_SIZE(x))(x)
#define DA_RANGE_STANDARDIZE_1(x) (0, DA_TUPLE_GET(0, x), 1)
#define DA_RANGE_STANDARDIZE_2(x) (DA_TUPLE_GET(0, x), DA_TUPLE_GET(1, x), 1)
#define DA_RANGE_STANDARDIZE_3(x) x

#define DA_RANGE_START(x) DA_TUPLE_GET(0, x)
#define DA_RANGE_STOP(x)  DA_TUPLE_GET(1, x)
#define DA_RANGE_STEP(x)  DA_TUPLE_GET(2, x)

#endif // _DA_PREPROCESSOR_RANGE_HPP_
