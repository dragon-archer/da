/**
 * @file      string_fwd.hpp
 * @brief     Common featrues for string
 * @version   0.1
 * @author    dragon-archer (dragon-archer@outlook.com)
 *
 * @copyright Copyright (c) 2022
 */

#ifndef _DA_STRING_STRING_FWD_HPP_
#define _DA_STRING_STRING_FWD_HPP_

#include "../config.hpp"
#include "../format.hpp"
#include "../iterator.hpp"
#include <bits/alloc_traits.h> // for std::alloc_traits
#include <bits/char_traits.h>  // for std::char_traits
#include <limits>              // for std::numeric_limits
#include <type_traits>         // for std::enable_if etc.

DA_BEGIN_NAMESPACE

template<typename Char, typename Traits = std::char_traits<Char>, typename Alloc = std::allocator<Char>>
class string_traits;

template<typename Char, typename Traits = std::char_traits<Char>, typename Alloc = std::allocator<Char>>
class sso_string_base;

template<typename Char, typename Traits = std::char_traits<Char>, typename Alloc = std::allocator<Char>>
class cow_string_base;

template<typename Char, typename Traits = std::char_traits<Char>, typename Alloc = std::allocator<Char>>
class normal_string_base;

template<typename Char, typename Traits, typename Alloc,
		 template<typename, typename, typename> typename StringImpl>
class string_base;

template<typename Char, template<typename, typename, typename> typename StringImpl = normal_string_base>
using string_base_helper = string_base<Char, std::char_traits<Char>, std::allocator<Char>, StringImpl>;

using string      = string_base_helper<char>;
using wstring     = string_base_helper<wchar_t>;
using sso_string  = string_base_helper<char, sso_string_base>;
using sso_wstring = string_base_helper<wchar_t, sso_string_base>;
using cow_string  = string_base_helper<char, cow_string_base>;
using cow_wstring = string_base_helper<wchar_t, cow_string_base>;

DA_END_NAMESPACE

#endif // _DA_STRING_STRING_FWD_HPP_
