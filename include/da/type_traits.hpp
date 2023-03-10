/* SPDX-License-Identifier: MIT */
/**
 * @file      type_traits.hpp
 * @brief     Some classes and macros for type infos, some idea from boost::tti
 * @version   0.1
 * @author    dragon-archer (dragon-archer@outlook.com)
 *
 * @copyright Copyright (c) 2022-2023 dragon-archer
 */

#ifndef _DA_TYPE_TRAITS_HPP_
#define _DA_TYPE_TRAITS_HPP_

#include <da/config.hpp>

#include <type_traits>

DA_BEGIN_NAMESPACE

/// Classes
/// nth_type
template<size_t N, typename... Ts>
struct nth_type {
};

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

/// make_sequence
template<size_t Begin, ssize_t Step, size_t... Ns>
inline constexpr auto _make_sequence(std::index_sequence<Ns...> = {}) {
	return std::index_sequence<(Begin + Step * Ns)...>{};
}

template<size_t Begin, size_t End, ssize_t Step>
inline constexpr auto make_sequence() {
	static_assert(Step != 0);
	constexpr size_t count = (Step > 0) ? ((End - Begin + Step - 1) / Step)
										: (ssize_t(End - Begin + Step + 1) / Step);
	return _make_sequence<Begin, Step>(std::make_index_sequence<count>{});
}

template<size_t Begin, size_t End>
inline constexpr auto make_sequence() {
	return make_sequence<Begin, End, 1>();
}

template<size_t End>
inline constexpr auto make_sequence() {
	return make_sequence<0, End, 1>();
}

template<typename... Ts>
struct typelist {
	template<size_t N>
	using type = typename nth_type<N, Ts...>::type;

	// Basic functions
	static inline constexpr auto size() {
		return sizeof...(Ts);
	}

	template<size_t... Ns>
	static inline constexpr auto mask(std::index_sequence<Ns...> = {}) {
		return typelist<type<Ns>...>{};
	}

	// Remove
	template<size_t N>
	static inline constexpr auto remove_tail() {
		static_assert(size() >= N);
		return mask(make_sequence<size() - N>());
	}

	template<size_t N>
	static inline constexpr auto remove_front() {
		static_assert(size() >= N);
		return mask(make_sequence<N, size()>());
	}

	template<size_t N>
	static inline constexpr auto remove_tail_to() {
		static_assert(size() >= N);
		return mask(make_sequence<N>());
	}

	template<size_t N>
	static inline constexpr auto remove_front_to() {
		static_assert(size() >= N);
		return mask(make_sequence<size() - N, size()>());
	}

	static inline constexpr auto remove_last() {
		static_assert(size() >= 1);
		return remove_tail<1>();
	}

	static inline constexpr auto remove_first() {
		static_assert(size() >= 1);
		return remove_front<1>();
	}

	// Append
	template<typename... Ts2>
	static inline constexpr auto concat(typelist<Ts2...> = {}) {
		return typelist<Ts..., Ts2...>{};
	}

	// Compare
	template<typename... Ts2>
	static inline constexpr bool same_with(typelist<Ts2...> = {}) {
		return std::is_same_v<typelist<Ts...>, typelist<Ts2...>>;
	}

	template<typename... Ts2>
	static inline constexpr bool start_with(typelist<Ts2...> = {}) {
		return (size() >= sizeof...(Ts2))
			&& typelist<Ts2...>::same_with(remove_tail_to<sizeof...(Ts2)>());
	}

	template<typename... Ts2>
	static inline constexpr bool end_with(typelist<Ts2...> = {}) {
		return (size() >= sizeof...(Ts2))
			&& typelist<Ts2...>::same_with(remove_front_to<sizeof...(Ts2)>());
	}
};

template<template<typename... Ts> typename T1>
struct __rebind_types {
	template<typename T>
	struct rebind;

	template<template<typename... Ts> typename T2, typename... Ts>
		requires requires { typename T1<Ts...>; }
	struct rebind<T2<Ts...>> {
		using type = T1<Ts...>;
	};

	template<typename T2>
	using type = typename rebind<T2>::type;
};

template<template<typename... Ts> typename T1, typename T2>
using rebind_types = typename __rebind_types<T1>::template type<T2>;

DA_END_NAMESPACE

#endif // _DA_TYPE_TRAITS_HPP_
