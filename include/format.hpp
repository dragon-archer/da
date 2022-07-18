/**
 * @file      format.hpp
 * @brief     A wrapper for std::format or fmt::format if std::format doesn't exist
 * @version   0.1
 * @author    dragon-archer (dragon-archer@outlook.com)
 *
 * @copyright Copyright (c) 2022
 */

#ifndef _UTILITY_FORMAT_HPP_
#define _UTILITY_FORMAT_HPP_

#include "config.hpp"

#if UTILITY_HAS_INCLUDE(<format>) // If there is format library as C++ standard, use it
#include <format>
namespace da {
	using format = std::format;
}
#elif UTILITY_HAS_INCLUDE(<fmt/format.h>) // Otherwise if there is fmt library already installed in the system, use it
#define FMT_HEADER_ONLY
#include <fmt/format.h>
namespace da {
	namespace format = ::fmt;
}
#elif UTILITY_HAS_INCLUDE("../thirdparty/fmt/include/fmt/format.h") // Finally, use our version of fmt. Current version: 9.0.0
#define FMT_HEADER_ONLY
#include "../thirdparty/fmt/include/fmt/format.h"
namespace da {
	namespace format = ::fmt;
}
#endif

#endif // _UTILITY_FORMAT_HPP_
