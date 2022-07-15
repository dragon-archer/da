/**
 * @file      string.hpp
 * @brief     interface of string
 * @version   0.1
 * @author    dragon-archer (dragon-archer@outlook.com)
 *
 * @copyright Copyright (c) 2022
 */

#ifndef _UTILITY_STRING_HPP_
#define _UTILITY_STRING_HPP_

#include "config.hpp"
#include "string/string_fwd.hpp"
#include "string/sso_string.hpp"
#include <boost/static_string.hpp>

namespace da {
	struct string_tag { };

	struct sso_string_tag : public string_tag { };

	struct normal_string_tag : public string_tag { };

	struct cow_string_tag : public string_tag { };

	template<typename Char, typename Traits, typename Alloc,
			 template<typename, typename, typename> typename StringImpl>
	class string_base : public StringImpl<Char, Traits, Alloc> {
	private:
		typedef StringImpl<Char, Traits, Alloc> Impl;

	public:
		typedef typename Impl::value_type			  value_type;
		typedef typename Impl::traits_type			  traits_type;
		typedef typename Impl::allocator_type		  allocator_type;
		typedef typename Impl::alloc_traits			  alloc_traits;
		typedef typename Impl::pointer				  pointer;
		typedef typename Impl::const_pointer		  const_pointer;
		typedef typename Impl::reference			  reference;
		typedef typename Impl::const_reference		  const_reference;
		typedef typename Impl::iterator				  iterator;
		typedef typename Impl::const_iterator		  const_iterator;
		typedef typename Impl::reverse_iterator		  reverse_iterator;
		typedef typename Impl::const_reverse_iterator const_reverse_iterator;
		typedef typename Impl::size_type			  size_type;
		typedef typename Impl::difference_type		  difference_type;

		constexpr string_base() noexcept
			: Impl{} { }
	};
} // namespace da

#endif // _UTILITY_STRING_HPP_
