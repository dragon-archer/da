/**
 * @file      config.hpp
 * @brief     Some basic configs
 * @version   0.1
 * @author    dragon-archer (dragon-archer@outlook.com)
 *
 * @copyright Copyright (c) 2022
 */

#ifndef _UTILITY_CONFIG_HPP_
#define _UTILITY_CONFIG_HPP_

#include <cassert>
#include <cstddef>
#include <cstdlib>
#include <exception> // for std::terminate()

#ifndef __cplusplus
#error Utility need to be compiled under C++, not C
#elif __cplusplus < 201103L
#error Utility need to be compiled under at least C++11, C++98 is not supported
#elif __cplusplus < 201402L
#warning Most features of Utility need to be compiled under at least C++17, using C++11 may cause lots of errors
#define UTILITY_11
#elif __cplusplus < 201703L
#warning Most features of Utility need to be compiled under at least C++17, using C++11 may cause lots of errors
#define UTILITY_11
#define UTILITY_14
#elif __cplusplus < 202002L
#define UTILITY_11
#define UTILITY_14
#define UTILITY_17
#else
#define UTILITY_11
#define UTILITY_14
#define UTILITY_17
#define UTILITY_20
#endif

#if defined(UTILITY_11)
#define UTILITY_CONSTEXPR_11 constexpr
#else
#define UTILITY_CONSTEXPR_11
#endif

#if defined(UTILITY_14)
#define UTILITY_CONSTEXPR_14 constexpr
#else
#define UTILITY_CONSTEXPR_14
#endif

#if defined(UTILITY_17)
#define UTILITY_CONSTEXPR_17 constexpr
#else
#define UTILITY_CONSTEXPR_17
#endif

#if defined(UTILITY_20)
#define UTILITY_CONSTEXPR_20 constexpr
#else
#define UTILITY_CONSTEXPR_20
#endif

#if defined(__has_cpp_attribute)
#define UTILITY_HAS_CPP_ATTRIBUTE(x) __has_cpp_attribute(x)
#else
#define UTILITY_HAS_CPP_ATTRIBUTE(x) 0
#endif

#if defined(__has_include)
#define UTILITY_HAS_INCLUDE(x) __has_include(x)
#else
#define UTILITY_HAS_INCLUDE(x) 0
#endif

#if UTILITY_HAS_CPP_ATTRIBUTE(likely)
#define UTILITY_IFLIKELY(x)	  if(x) [[likely]]
#define UTILITY_IFUNLIKELY(x) if(x) [[unlikely]]
#elif UTILITY_11 // Most compiler support likely & unlikely since C++11
#define UTILITY_IFLIKELY(x)	  if(x) [[likely]]
#define UTILITY_IFUNLIKELY(x) if(x) [[unlikely]]
#else
#define UTILITY_IFLIKELY(x)	  if(x)
#define UTILITY_IFUNLIKELY(x) if(x)
#endif

// Use UTILITY_NO_EXCEPTION to disable all exceptions
#ifndef UTILITY_NO_EXCEPTION
#include <stdexcept>
#define UTILITY_TRY			try
#define UTILITY_CATCH(x)	catch(x)
#define UTILITY_THROW(x)	throw(x)
#define UTILITY_THROW_AGAIN throw;
#else
#define UTILITY_TRY			UTILITY_IFLIKELY(true)
#define UTILITY_CATCH		UTILITY_IFUNLIKELY(false)
#define UTILITY_THROW(x)	std::terminate()
#define UTILITY_THROW_AGAIN std::terminate();
#endif

namespace da {
	using std::ptrdiff_t;
	using std::size_t;
}

#endif // _UTILITY_CONFIG_HPP_
