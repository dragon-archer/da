/* SPDX-License-Identifier: MIT */
/**
 * @file      typelist.hpp
 * @brief     Container for varidic types
 * @version   0.1
 * @author    dragon-archer
 *
 * @copyright Copyright (c) 2023 dragon-archer
 */

#ifndef _DA_TYPE_TRAITS_TYPELIST_HPP_
#define _DA_TYPE_TRAITS_TYPELIST_HPP_

#include <da/type_traits/config.hpp>
#include <da/type_traits/sequence.hpp>

DA_BEGIN_DETAIL

template<size_t N, typename... Ts>
struct nth_type;

template<typename T0, typename... Ts>
struct nth_type<0, T0, Ts...> {
	using type = T0;
};

template<typename T0, typename T1, typename... Ts>
struct nth_type<1, T0, T1, Ts...> {
	using type = T1;
};

template<typename T0, typename T1, typename T2, typename... Ts>
struct nth_type<2, T0, T1, T2, Ts...> {
	using type = T2;
};

template<size_t N, typename T0, typename T1, typename T2, typename... Ts>
	requires(N >= 3)
struct nth_type<N, T0, T1, T2, Ts...>
	: nth_type<N - 3, Ts...> {
};

template<template<typename...> typename T>
struct rebind {
	template<typename U>
	struct helper;

	template<template<typename...> typename U, typename... Ts>
	struct helper<U<Ts...>> {
		using type = T<Ts...>;
	};

	template<typename U>
	using type = typename helper<U>::type;
};

DA_END_DETAIL

DA_BEGIN_NAMESPACE

/**
 * @brief traits type for nth_type_t
 */
template<size_t N, typename... Ts>
	requires(N < sizeof...(Ts))
using nth_type = _DA_DETAIL nth_type<N, Ts...>;

/**
 * @brief Nth type in Ts...
 */
template<size_t N, typename... Ts>
	requires(N < sizeof...(Ts))
using nth_type_t = typename nth_type<N, Ts...>::type;

/**
 * @brief traits type for rebind_t
 */
template<template<typename...> typename T>
using rebind = _DA_DETAIL rebind<T>;

/**
 * @brief Rebind U's template arguments to T
 */
template<template<typename...> typename T, typename U>
	requires requires { typename rebind<T>::template type<U>; }
using rebind_t = typename rebind<T>::template type<U>;

DA_END_NAMESPACE

DA_BEGIN_DETAIL

template<typename... Ts>
struct typelist;

template<typename... Ts>
struct typelist_base {
	// Basic functions
	static constexpr size_t size() noexcept {
		return sizeof...(Ts);
	}
	template<size_t N>
		requires(N < size())
	static constexpr auto get() noexcept {
		return nth_type_t<N, Ts...>{};
	}

	// STL functions
	template<typename... Us>
	static constexpr auto push_front() noexcept {
		return typelist<Us..., Ts...>{};
	}

	template<typename... Us>
	static constexpr auto push_back() noexcept {
		return typelist<Ts..., Us...>{};
	}

	// Additional functions
	template<typename... Us>
	static constexpr auto concat(typelist<Us...> = {}) noexcept {
		return typelist<Ts..., Us...>{};
	}

	// types
	template<typename... Us>
	using push_front_t = decltype(push_front<Us...>());
	template<typename... Us>
	using push_back_t = decltype(push_back<Us...>());
};

template<typename... Ts>
struct typelist : typelist_base<Ts...> {
	// Note: Assume sizeof...(Ts) >= 1

	using typelist_base<Ts...>::size;
	using typelist_base<Ts...>::get;

	template<size_t... Ns>
		requires((Ns < size()) && ...)
	static constexpr auto mask(std::index_sequence<Ns...> = {}) noexcept {
		return typelist<get_t<Ns>...>{};
	}

	static constexpr auto front() noexcept {
		return get<0>();
	}

	static constexpr auto back() noexcept {
		return get<size() - 1>();
	}

	static constexpr auto pop_front() noexcept {
		return mask(make_sequence<1, size()>());
	}

	static constexpr auto pop_back() noexcept {
		return mask(make_sequence<size() - 1>());
	}

	template<size_t N>
	using get_t = decltype(get<N>());

	using front_t     = decltype(front());
	using back_t      = decltype(back());
	using pop_front_t = decltype(pop_front());
	using pop_back_t  = decltype(pop_back());
};

template<>
struct typelist<> : typelist_base<> {
};

DA_END_DETAIL

DA_BEGIN_NAMESPACE

template<typename... Ts>
using typelist = _DA_DETAIL typelist<Ts...>;

DA_END_NAMESPACE

#endif // _DA_TYPE_TRAITS_TYPELIST_HPP_
