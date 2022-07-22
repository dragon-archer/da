/**
 * @file      config.hpp
 * @brief     Some basic configs
 * @version   0.1
 * @author    dragon-archer (dragon-archer@outlook.com)
 *
 * @copyright Copyright (c) 2022
 */

#ifndef _LIBDA_CONFIG_HPP_
#define _LIBDA_CONFIG_HPP_

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
#define DA_11
#elif __cplusplus < 201703L
#warning Most features of Utility need to be compiled under at least C++17, using C++11 may cause lots of errors
#define DA_11
#define DA_14
#elif __cplusplus < 202002L
#define DA_11
#define DA_14
#define DA_17
#else
#define DA_11
#define DA_14
#define DA_17
#define DA_20
#endif

#if defined(DA_11)
#define DA_CONSTEXPR_11 constexpr
#else
#define DA_CONSTEXPR_11
#endif

#if defined(DA_14)
#define DA_CONSTEXPR_14 constexpr
#else
#define DA_CONSTEXPR_14
#endif

#if defined(DA_17)
#define DA_CONSTEXPR_17 constexpr
#else
#define DA_CONSTEXPR_17
#endif

#if defined(DA_20)
#define DA_CONSTEXPR_20 constexpr
#else
#define DA_CONSTEXPR_20
#endif

#if defined(__has_cpp_attribute)
#define DA_HAS_CPP_ATTRIBUTE(x) __has_cpp_attribute(x)
#else
#define DA_HAS_CPP_ATTRIBUTE(x) 0
#endif

#if defined(__has_include)
#define DA_HAS_INCLUDE(x) __has_include(x)
#else
#define DA_HAS_INCLUDE(x) 0
#endif

#if DA_HAS_CPP_ATTRIBUTE(likely)
#define DA_IFLIKELY(x)	 if(x) [[likely]]
#define DA_IFUNLIKELY(x) if(x) [[unlikely]]
#elif DA_11 // Most compiler support likely & unlikely since C++11
#define DA_IFLIKELY(x)	 if(x) [[likely]]
#define DA_IFUNLIKELY(x) if(x) [[unlikely]]
#else
#define DA_IFLIKELY(x)	 if(x)
#define DA_IFUNLIKELY(x) if(x)
#endif

// Use DA_NO_EXCEPTION to disable all exceptions
#ifndef DA_NO_EXCEPTION
#include <stdexcept>
#define DA_TRY		   try
#define DA_CATCH(x)	   catch(x)
#define DA_THROW(x)	   throw(x)
#define DA_THROW_AGAIN throw;
#else
#define DA_TRY		   DA_IFLIKELY(true)
#define DA_CATCH	   DA_IFUNLIKELY(false)
#define DA_THROW(x)	   std::terminate()
#define DA_THROW_AGAIN std::terminate();
#endif

namespace da {
	using std::ptrdiff_t;
	using std::size_t;
}

#endif // _LIBDA_CONFIG_HPP_
