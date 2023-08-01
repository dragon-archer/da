/* SPDX-License-Identifier: MIT */
/**
 * @file      format.hpp
 * @brief     A wrapper for std::format or fmt::format if std::format doesn't exist
 * @version   0.1
 * @author    dragon-archer
 *
 * @copyright Copyright (c) 2022-2023 dragon-archer
 */

#ifndef _DA_FORMAT_HPP_
#define _DA_FORMAT_HPP_

#include <da/config.hpp>

// clang-format off

#if defined(DA_USE_STD_FORMAT) && DA_HAS_INCLUDE(<format>)
	#include <format>
	DA_BEGIN_NAMESPACE
	namespace fmt = std;
	DA_END_NAMESPACE
#elif DA_HAS_INCLUDE(<fmt/format.h>)
	#define FMT_HEADER_ONLY
	#include <fmt/format.h>
	DA_BEGIN_NAMESPACE
	namespace fmt = ::fmt;
	DA_END_NAMESPACE
#else
	#error No usable fmtlib, either define DA_USE_STD_FORMAT to use <format> or install fmtlib
#endif

// clang-format on

#endif // _DA_FORMAT_HPP_
