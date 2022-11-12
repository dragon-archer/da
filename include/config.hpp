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

/// Editable configs
/// Uncomment following lines to enable

// #define DA_NO_EXCEPTIONS // Disable exceptions
// #define DA_NO_NAMESPACE // Disable namespace

// clang-format off

/// Verify we have at least C++20
#if !defined(__cplusplus) || __cplusplus < 202002L
	#error LibDA should be compiled under at least C++20
#endif

/// Feature test macros
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

/// Likely & unlikely
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

/// Exception
#ifndef DA_NO_EXCEPTION
	#include <stdexcept>
	#define DA_TRY		   try
	#define DA_CATCH(x)	   catch(x)
	#define DA_THROW(x)	   throw(x)
	#define DA_THROW_AGAIN throw
#else
	#define DA_TRY		   DA_IFLIKELY(true)
	#define DA_CATCH	   DA_IFUNLIKELY(false)
	#define DA_THROW(x)	   std::terminate()
	#define DA_THROW_AGAIN std::terminate()
#endif

/// Namespace
#ifndef DA_NO_NAMESPACE
	#define DA_BEGIN_NAMESPACE namespace da {
	#define DA_END_NAMESPACE }
	#define DA_NAMESAPCE ::da::
#else
	#define DA_BEGIN_NAMESPACE
	#define DA_END_NAMESPACE
	#define DA_NAMESPACE
#endif

// clang-format on

DA_BEGIN_NAMESPACE

using std::ptrdiff_t;
using std::size_t;

DA_END_NAMESPACE

#endif // _LIBDA_CONFIG_HPP_
