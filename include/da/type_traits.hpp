/**
 * @file      type_traits.hpp
 * @brief     Some classes and macros for type infos, some idea from boost::tti
 * @version   0.1
 * @author    dragon-archer (dragon-archer@outlook.com)
 *
 * @copyright Copyright (c) 2022 - 2023
 */

#ifndef _LIBDA_TYPE_TRAITS_HPP_
#define _LIBDA_TYPE_TRAITS_HPP_

#include <da/config.hpp>
#include <da/preprocessor.hpp>
#include <type_traits>

/// Macros

/**
 * @brief Declare a struct to test whether a class has a member function called @param FN with parameters @param ...
 *        The @param SN is the name of the test struct
 * @param SN  aka. struct name
 * @param FN  aka. function name
 * @param ... aka. the type of each parameter
 * @note  The template param is connected with @param SN to avoid conflict with user code
 * @note  This macro has been rewrite using @see DA_FOREACH to avoid duplicate work
 */
#define DA_DECLARE_MEMBER_FUNCTION_TEST(SN, FN, ...)                                            \
	template<typename T##SN>                                                                    \
	struct SN {                                                                                 \
		private:                                                                                \
		template<typename T2##SN>                                                               \
		static auto f(int)                                                                      \
			-> decltype(std::declval<T2##SN>().FN(DA_FOREACH(DA_DECLVAL_WRAPPER, __VA_ARGS__)), \
						std::true_type());                                                      \
		template<typename T2##SN>                                                               \
		static std::false_type f(...);                                                          \
                                                                                                \
		public:                                                                                 \
		static constexpr bool value = decltype(f<T##SN>(0))::value;                             \
	};                                                                                          \
	template<typename T##SN>                                                                    \
	inline static constexpr bool SN##_v = SN<T##SN>::value;

#define DA_DECLVAL_WRAPPER(type) std::declval<type>()

/**
 * @brief Call OBJ.FN() and returns RT if exist, otherwise call the user-defined function below
 * @param OBJ aka. the name of the object
 * @param FN  aka. the function name
 * @param RT  aka. the return type
 * @param PnT aka. the type of nth. parameter
 * @param PnN aka. the name of nth. parameter
 */
#define DA_USE_IF_EXIST_3(OBJ, FN, RT)         \
	DA_DECLARE_MEMBER_FUNCTION_TEST(S##FN, FN) \
	template<typename T##FN>                   \
	std::enable_if_t<S##FN##_v<T##FN>, RT>     \
		F0##FN() {                             \
		return OBJ.FN();                       \
	}                                          \
	RT FN() {                                  \
		return F0##FN<decltype(OBJ)>();        \
	}                                          \
	template<typename T##FN>                   \
	std::enable_if_t<!S##FN##_v<T##FN>, RT>    \
		F0##FN()

#define DA_USE_IF_EXIST_5(OBJ, FN, RT, P1T, P1N)    \
	DA_DECLARE_MEMBER_FUNCTION_TEST(S##FN, FN, P1T) \
	template<typename T##FN>                        \
	std::enable_if_t<S##FN##_v<T##FN>, RT>          \
		F1##FN(P1T P1N) {                           \
		return OBJ.FN(P1N);                         \
	}                                               \
	RT FN(P1T P1N) {                                \
		return F1##FN<decltype(OBJ)>(P1N);          \
	}                                               \
	template<typename T##FN>                        \
	std::enable_if_t<!S##FN##_v<T##FN>, RT>         \
		F1##FN(P1T P1N)

#define DA_USE_IF_EXIST_7(OBJ, FN, RT, P1T, P1N, P2T, P2N) \
	DA_DECLARE_MEMBER_FUNCTION_TEST(S##FN, FN, P1T, P2T)   \
	template<typename T##FN>                               \
	std::enable_if_t<S##FN##_v<T##FN>, RT>                 \
		F2##FN(P1T P1N, P2T P2N) {                         \
		return OBJ.FN(P1N, P2N);                           \
	}                                                      \
	RT FN(P1T P1N, P2T P2N) {                              \
		return F2##FN<decltype(OBJ)>(P1N, P2N);            \
	}                                                      \
	template<typename T##FN>                               \
	std::enable_if_t<!S##FN##_v<T##FN>, RT>                \
		F2##FN(P1T P1N, P2T P2N)

#define DA_USE_IF_EXIST_9(OBJ, FN, RT, P1T, P1N, P2T, P2N, P3T, P3N) \
	DA_DECLARE_MEMBER_FUNCTION_TEST(S##FN, FN, P1T, P2T, P3T)        \
	template<typename T##FN>                                         \
	std::enable_if_t<S##FN##_v<T##FN>, RT>                           \
		F3##FN(P1T P1N, P2T P2N, P3T P3N) {                          \
		return OBJ.FN(P1N, P2N, P3N);                                \
	}                                                                \
	RT FN(P1T P1N, P2T P2N, P3T P3N) {                               \
		return F3##FN<decltype(OBJ)>(P1N, P2N, P3N);                 \
	}                                                                \
	template<typename T##FN>                                         \
	std::enable_if_t<!S##FN##_v<T##FN>, RT>                          \
		F3##FN(P1T P1N, P2T P2N, P3T P3N)

#define DA_USE_IF_EXIST_11(OBJ, FN, RT, P1T, P1N, P2T, P2N, P3T, P3N, P4T, P4N) \
	DA_DECLARE_MEMBER_FUNCTION_TEST(S##FN, FN, P1T, P2T, P3T, P4T)              \
	template<typename T##FN>                                                    \
	std::enable_if_t<S##FN##_v<T##FN>, RT>                                      \
		F4##FN(P1T P1N, P2T P2N, P3T P3N, P4T P4N) {                            \
		return OBJ.FN(P1N, P2N, P3N, P4N);                                      \
	}                                                                           \
	RT FN(P1T P1N, P2T P2N, P3T P3N, P4T P4N) {                                 \
		return F4##FN<decltype(OBJ)>(P1N, P2N, P3N, P4N);                       \
	}                                                                           \
	template<typename T##FN>                                                    \
	std::enable_if_t<!S##FN##_v<T##FN>, RT>                                     \
		F4##FN(P1T P1N, P2T P2N, P3T P3N, P4T P4N)

/**
 * @brief General version of `DA_USE_IF_EXIST_n`
 *        To use this macro:
 *        DA_USE_IF_EXIST(Object, Return Type, Function Name, Param1 Type, Param1 Name, ...) {
 *            // Your codes goes here
 *        }
 * @note  If you want to use functions from the base class, just use `*static_cast<T*>(this)` as Object,
 *        where T is the name of the base class
 * @note  This macro forward the parameters AS IS, BY VALUE.
 *        You may need to use const T& instead of T as Param Type to reduce the fowarding cost
 * @note  The generated function name is F ## number of parameters ## Function Name,
 *        which may not work proper with overloading
 * @note  Currently the max number of parameters is 4
 */
#define DA_USE_IF_EXIST(...)                      \
	DA_CAT(DA_USE_IF_EXIST_, DA_CNT(__VA_ARGS__)) \
	(__VA_ARGS__)

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

#endif // _LIBDA_TYPE_TRAITS_HPP_
