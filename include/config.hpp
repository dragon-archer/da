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

#include <cstddef>
#include <cstdlib>
#include <exception> // for std::terminate()

#if defined(__has_cpp_attribute) && __has_cpp_attribute(likely)
#define UTILITY_IFLIKELY(x)	  if(x) [[likely]]
#define UTILITY_IFUNLIKELY(x) if(x) [[unlikely]]
#elif __cplusplus >= 201103L // Most compiler support likely & unlikely since C++11
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
