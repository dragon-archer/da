/**
 * @file      cat.hpp
 * @brief     Implement DA_CAT
 * @version   0.1
 * @author    dragon-archer
 *
 * @copyright Copyright (c) 2023
 */

#ifndef _LIBDA_PREPROCESSOR_CAT_HPP_
#define _LIBDA_PREPROCESSOR_CAT_HPP_

#include "base.hpp"
#include "fold.hpp"

/**
 * @section DA_CAT2
 * @brief   Concat exact 2 params
 */
#define DA_CAT2(_1, _2)   DA_CAT2_I(_1, _2)
#define DA_CAT2_I(_1, _2) _1##_2

/**
 * @section DA_CAT
 * @brief   Concat everything
 */
#define DA_CAT(...) __VA_OPT__(DA_FOLD(DA_CAT2, __VA_ARGS__))

#endif // _LIBDA_PREPROCESSOR_CAT_HPP_
