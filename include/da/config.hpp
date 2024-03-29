/* SPDX-License-Identifier: MIT */
/**
 * @file      config.hpp
 * @brief     Some basic configs
 * @version   0.2
 * @author    dragon-archer
 *
 * @copyright Copyright (c) 2022- 2023 dragon-archer
 */

#ifndef _DA_CONFIG_HPP_
#define _DA_CONFIG_HPP_

/// Editable configs
/// Uncomment following lines to enable

// #define DA_NO_EXCEPTION // Disable exception
// #define DA_NO_NAMESPACE // Disable namespace

#define DA_VERSION_MAJOR 0
#define DA_VERSION_MINOR 2
#define DA_VERSION_PATCH 0
#define DA_VERSION       (DA_VERSION_MAJOR * 10000 + DA_VERSION_MINOR * 100 + DA_VERSION_PATCH)

/// Detect compiler & C++ Version
#ifdef __clang__
	#define DA_CLANG __clang__
	#define DA_GCC   0
	#define DA_MSVC  0
#elif defined(__GNUC__)
	#define DA_CLANG 0
	#define DA_GCC   __GNUC__
	#define DA_MSVC  0
#elif defined(_MSC_VER)
	#define DA_CLANG 0
	#define DA_GCC   0
	#define DA_MSVC  _MSC_VER
#else
	#error Unknown compiler! Please use Clang, GCC or MSVC
#endif

#if DA_MSVC
	#define DA_CPPVER _MSVC_LANG
#else
	#define DA_CPPVER __cplusplus
#endif

/// Verify we have at least C++20
#if DA_CPPVER < 202002L
	#error DA should be compiled under at least C++20
#endif

/// Feature test macros
#if defined(__has_builtin)
	#define DA_HAS_BUILTIN(x) __has_builtin(x)
#else
	#define DA_HAS_BUILTIN(x) 0
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

/// Likely & unlikely
#if DA_HAS_CPP_ATTRIBUTE(likely)
	#define DA_IFLIKELY(x)   if(x) [[likely]]
	#define DA_IFUNLIKELY(x) if(x) [[unlikely]]
#elif DA_HAS_BUILTIN(__builtin_expect)
	#define DA_IFLIKELY(x)   if(__builtin_expect(!!(x), 1))
	#define DA_IFUNLIKELY(x) if(__builtin_expect(!!(x), 0))
#else
	#define DA_IFLIKELY(x)   if(x)
	#define DA_IFUNLIKELY(x) if(x)
#endif

/// Standard headers
#include <cassert>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <exception> // for std::terminate()
#if DA_HAS_INCLUDE(<version>)
	#include <version>
#endif

/// Exception
#ifndef DA_NO_EXCEPTION
	#include <stdexcept>
	#define DA_TRY           try
	#define DA_CATCH(x)      catch(x)
	#define DA_THROW(x)      throw(x)
	#define DA_THROW_AGAIN() throw
#else
	#define DA_TRY           DA_IFLIKELY(true)
	#define DA_CATCH(x)      DA_IFUNLIKELY(false)
	#define DA_THROW(x)      std::terminate()
	#define DA_THROW_AGAIN() std::terminate()
#endif

/// Namespace
#ifndef DA_NO_NAMESPACE
	#define DA_BEGIN_NAMESPACE namespace da {
	#define DA_END_NAMESPACE   }
	#define DA_BEGIN_DETAIL    namespace da::detail {
	#define DA_END_DETAIL      }
	#define _DA                ::da::
	#define _DA_DETAIL         ::da::detail::
#else
	#define DA_BEGIN_NAMESPACE
	#define DA_END_NAMESPACE
	#define DA_BEGIN_DETAIL
	#define DA_END_DETAIL
	#define _DA        ::
	#define _DA_DETAIL ::
#endif

/// DA_CONSTEXPR
#ifdef DA_ON_CODE_COVERAGE
	#define DA_CONSTEXPR
#else
	#define DA_CONSTEXPR constexpr
#endif

/// Basic debug support

#ifdef DA_ON_CODE_COVERAGE
	#define DA_ASSERT(expr)
#else
	#define DA_ASSERT(expr) assert(expr)
#endif

// DA_ASSUME
// Note: whether expr will be executed is not determined
#ifdef DA_ON_CODE_COVERAGE // No tests for assume failure
	#define DA_ASSUME(expr)
#elif !defined(NDEBUG)
	#define DA_ASSUME(expr) assert(expr)
#elif DA_HAS_CPP_ATTRIBUTE(assume) // Prefer c++ attribute
	#define DA_ASSUME(expr) [[assume(expr)]]
#elif DA_HAS_BUILTIN(__assume) // Usually MSVC
	#define DA_ASSUME(expr) __assume(expr)
#elif DA_HAS_BUILTIN(__builtin_assume) // Usually Clang
	#define DA_ASSUME(expr) __builtin_assume(expr)
#else // No suitable assume
	#define DA_ASSUME(expr)
#endif

// DA_UNREACHABLE
#ifdef __cpp_lib_unreachable // Prefer std function
	#define DA_UNREACHABLE() ::std::unreachable()
#elif DA_HAS_BUILTIN(__builtin_unreachable) // Usually GCC or Clang
	#define DA_UNREACHABLE() __builtin_unreachable()
#else // Use assume to simulate
	#define DA_UNREACHABLE() DA_ASSUME(false)
#endif

// Make sure to import widely used types to da
DA_BEGIN_NAMESPACE

using std::size_t;
using ssize_t = std::ptrdiff_t;

DA_END_NAMESPACE

#endif // _DA_CONFIG_HPP_
