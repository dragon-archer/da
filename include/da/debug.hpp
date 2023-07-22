/* SPDX-License-Identifier: MIT */
/**
 * @file      debug.hpp
 * @brief     Debug utilities
 * @version   0.1
 * @author    dragon-archer
 *
 * @copyright Copyright (c) 2023 dragon-archer
 */

#ifndef _DA_DEBUG_HPP_
#define _DA_DEBUG_HPP_

#include <da/config.hpp>
#include <typeinfo>

#if !DA_MSVC
	#include <cxxabi.h>
#endif

DA_BEGIN_NAMESPACE

template<typename T>
std::string demangle() {
#if DA_MSVC
	return typeid(T).name();
#else
	char*       buf = abi::__cxa_demangle(typeid(T).name(), nullptr, nullptr, nullptr);
	std::string ret(buf);
	std::free(buf);
	return ret;
#endif
}

DA_END_NAMESPACE

#endif //_DA_DEBUG_HPP_
