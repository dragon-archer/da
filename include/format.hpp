/**
 * @file      format.hpp
 * @brief     A wrapper for std::format or fmt::format if std::format doesn't exist
 * @version   0.1
 * @author    dragon-archer (dragon-archer@outlook.com)
 *
 * @copyright Copyright (c) 2022
 */

#ifndef _LIBDA_FORMAT_HPP_
#define _LIBDA_FORMAT_HPP_

#include "config.hpp"

#if DA_HAS_INCLUDE(<format>) // If there is format library as C++ standard, use it
#include <format>
DA_BEGIN_NAMESPACE
namespace fmt {
	using std::format;
	using std::format_to;
	using std::format_to_n;
	using std::formatted_size;
	using std::vformat;
	using std::vformat_to;
}
DA_END_NAMESPACE
#elif DA_HAS_INCLUDE(<fmt / format.h>) // Otherwise if there is fmt library already installed in the system, use it
#define FMT_HEADER_ONLY
#include <fmt/format.h>
DA_BEGIN_NAMESPACE
namespace fmt = ::fmt;
DA_END_NAMESPACE
#endif

#endif // _LIBDA_FORMAT_HPP_
