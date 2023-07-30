/* SPDX-License-Identifier: MIT */
/**
 * @file      concepts.hpp
 * @brief     Concepts
 * @version   0.1
 * @author    dragon-archer
 *
 * @copyright Copyright (c) 2022-2023 dragon-archer
 */

#ifndef _DA_CONCEPTS_HPP_
#define _DA_CONCEPTS_HPP_

#include <da/config.hpp>
#include <concepts>

DA_BEGIN_NAMESPACE

/// Invocable
using std::invocable;

template<typename Func, typename Ret, typename... Args>
concept invocable_r = std::is_invocable_r_v<Ret, Func, Args...>;

/// Arithmatic
using std::integral;
using std::signed_integral;
using std::unsigned_integral;

using std::floating_point;

template<typename T>
concept arithmetic = std::is_arithmetic_v<T>;

DA_END_NAMESPACE

#endif // _DA_CONCEPTS_HPP_
