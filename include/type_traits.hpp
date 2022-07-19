/**
 * @file      type_traits.hpp
 * @brief     Some classes and macros for type infos, some idea from boost::tti
 * @version   0.1
 * @author    dragon-archer (dragon-archer@outlook.com)
 *
 * @copyright Copyright (c) 2022
 */

#ifndef _UTILITY_TYPE_TRAITS_HPP_
#define _UTILITY_TYPE_TRAITS_HPP_

#include "config.hpp"
#include "preprocessor.hpp"
#include <type_traits>

/**
 * @brief Declare a struct to test whether a class has a member function called @param FN with parameters @param ...
 *        The @param SN is the name of the test struct
 * @param SN  aka. struct name
 * @param FN  aka. function name
 * @param ... aka. the type of each parameter
 * @note  The template param is connected with @param SN to avoid conflict with user code
 * @note  This macro has been rewrite using @see UTILITY_SUPER_FOREACH to avoid duplicate work
 */
#define UTILITY_DECLARE_MEMBER_FUNCTION_TEST(SN, FN, ...)                                                  \
	template<typename T##SN>                                                                               \
	struct SN {                                                                                            \
	private:                                                                                               \
		template<typename T2##SN>                                                                          \
		static auto f(int)                                                                                 \
			-> decltype(std::declval<T2##SN>().FN(UTILITY_SUPER_FOREACH(std::declval<, >(), __VA_ARGS__)), \
						std::true_type());                                                                 \
		template<typename T2##SN>                                                                          \
		static std::false_type f(...);                                                                     \
                                                                                                           \
	public:                                                                                                \
		static constexpr bool value = decltype(f<T##SN>(0))::value;                                        \
	};                                                                                                     \
	template<typename T##SN>                                                                               \
	inline static constexpr bool SN##_v = SN<T##SN>::value;

/**
 * @brief Call OBJ.FN() and returns RT if exist, otherwise call the user-defined function below
 * @param OBJ aka. the name of the object
 * @param FN  aka. the function name
 * @param RT  aka. the return type
 * @param PnT aka. the type of nth. parameter
 * @param PnN aka. the name of nth. parameter
 */
#define UTILITY_USE_IF_EXIST_3(OBJ, FN, RT)         \
	UTILITY_DECLARE_MEMBER_FUNCTION_TEST(S##FN, FN) \
	template<typename T##FN>                        \
	std::enable_if_t<S##FN##_v<T##FN>, RT>          \
		F0##FN() {                                  \
		return OBJ.FN();                            \
	}                                               \
	RT FN() {                                       \
		return F0##FN<decltype(OBJ)>();             \
	}                                               \
	template<typename T##FN>                        \
	std::enable_if_t<!S##FN##_v<T##FN>, RT>         \
		F0##FN()

#define UTILITY_USE_IF_EXIST_5(OBJ, FN, RT, P1T, P1N)    \
	UTILITY_DECLARE_MEMBER_FUNCTION_TEST(S##FN, FN, P1T) \
	template<typename T##FN>                             \
	std::enable_if_t<S##FN##_v<T##FN>, RT>               \
		F1##FN(P1T P1N) {                                \
		return OBJ.FN(P1N);                              \
	}                                                    \
	RT FN(P1T P1N) {                                     \
		return F1##FN<decltype(OBJ)>(P1N);               \
	}                                                    \
	template<typename T##FN>                             \
	std::enable_if_t<!S##FN##_v<T##FN>, RT>              \
		F1##FN(P1T P1N)

#define UTILITY_USE_IF_EXIST_7(OBJ, FN, RT, P1T, P1N, P2T, P2N) \
	UTILITY_DECLARE_MEMBER_FUNCTION_TEST(S##FN, FN, P1T, P2T)   \
	template<typename T##FN>                                    \
	std::enable_if_t<S##FN##_v<T##FN>, RT>                      \
		F2##FN(P1T P1N, P2T P2N) {                              \
		return OBJ.FN(P1N, P2N);                                \
	}                                                           \
	RT FN(P1T P1N, P2T P2N) {                                   \
		return F2##FN<decltype(OBJ)>(P1N, P2N);                 \
	}                                                           \
	template<typename T##FN>                                    \
	std::enable_if_t<!S##FN##_v<T##FN>, RT>                     \
		F2##FN(P1T P1N, P2T P2N)

#define UTILITY_USE_IF_EXIST_9(OBJ, FN, RT, P1T, P1N, P2T, P2N, P3T, P3N) \
	UTILITY_DECLARE_MEMBER_FUNCTION_TEST(S##FN, FN, P1T, P2T, P3T)        \
	template<typename T##FN>                                              \
	std::enable_if_t<S##FN##_v<T##FN>, RT>                                \
		F3##FN(P1T P1N, P2T P2N, P3T P3N) {                               \
		return OBJ.FN(P1N, P2N, P3N);                                     \
	}                                                                     \
	RT FN(P1T P1N, P2T P2N, P3T P3N) {                                    \
		return F3##FN<decltype(OBJ)>(P1N, P2N, P3N);                      \
	}                                                                     \
	template<typename T##FN>                                              \
	std::enable_if_t<!S##FN##_v<T##FN>, RT>                               \
		F3##FN(P1T P1N, P2T P2N, P3T P3N)

#define UTILITY_USE_IF_EXIST_11(OBJ, FN, RT, P1T, P1N, P2T, P2N, P3T, P3N, P4T, P4N) \
	UTILITY_DECLARE_MEMBER_FUNCTION_TEST(S##FN, FN, P1T, P2T, P3T, P4T)              \
	template<typename T##FN>                                                         \
	std::enable_if_t<S##FN##_v<T##FN>, RT>                                           \
		F4##FN(P1T P1N, P2T P2N, P3T P3N, P4T P4N) {                                 \
		return OBJ.FN(P1N, P2N, P3N, P4N);                                           \
	}                                                                                \
	RT FN(P1T P1N, P2T P2N, P3T P3N, P4T P4N) {                                      \
		return F4##FN<decltype(OBJ)>(P1N, P2N, P3N, P4N);                            \
	}                                                                                \
	template<typename T##FN>                                                         \
	std::enable_if_t<!S##FN##_v<T##FN>, RT>                                          \
		F4##FN(P1T P1N, P2T P2N, P3T P3N, P4T P4N)

/**
 * @brief General version of `UTILITY_USE_IF_EXIST_n`
 *        To use this macro:
 *        UTILITY_USE_IF_EXIST(Object, Return Type, Function Name, Param1 Type, Param1 Name, ...) {
 *            // Your codes goes here
 *        }
 * @note  If you want to use functions from the base class, just use `*static_cast<T*>(this)` as Object,
 *        where T is the name of the base class
 * @note  This macro foward the parameters AS IS, BY VALUE.
 *        You may need to use const T& instead of T as Param Type to reduce the fowarding cost
 * @note  The generated function name is F ## number of parameters ## Function Name,
 *        which may not work proper with overloading
 * @note  Currently the max number of parameters is 4
 */
#define UTILITY_USE_IF_EXIST(...)                                        \
	UTILITY_CONCAT(UTILITY_USE_IF_EXIST_, UTILITY_VA_COUNT(__VA_ARGS__)) \
	(__VA_ARGS__)

#endif // _UTILITY_TYPE_TRAITS_HPP_
