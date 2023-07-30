/* SPDX-License-Identifier: MIT */
/**
 * @file      function_detect.hpp
 * @brief     Detect functions
 * @version   0.1
 * @author    dragon-archer
 *
 * @copyright Copyright (c) 2023 dragon-archer
 */

#ifndef _DA_TYPE_TRAITS_FUNCTION_DETECT_HPP_
#define _DA_TYPE_TRAITS_FUNCTION_DETECT_HPP_

#include <da/type_traits/config.hpp>
#include <da/preprocessor/foreach.hpp>
#include <da/preprocessor/tuple.hpp>

/**
 * @brief Declare a struct to test whether a class has a member function called @ref FN with parameters @ref ...
 *        The @ref SN is the name of the test struct
 * @param SN  struct name
 * @param FN  function name
 * @param ... the type of each parameter
 * @note  The template param is connected with @ref SN to avoid conflict with user code
 */
#define DA_DECLARE_MEMBER_FUNCTION_TEST(SN, FN, ...)                              \
	template<typename T_##SN>                                                     \
	struct SN {                                                                   \
		private:                                                                  \
		template<typename U_##SN>                                                 \
		static auto f(int)                                                        \
			-> decltype(std::declval<U_##SN>().FN(                                \
							DA_TUPLE_UNPACK(DA_TUPLE_REMOVE_HEAD(                 \
								(DA_FOREACH(DA_DECLVAL_WRAPPER, __VA_ARGS__))))), \
						std::true_type());                                        \
		template<typename U_##SN>                                                 \
		static std::false_type f(...);                                            \
                                                                                  \
		public:                                                                   \
		static DA_CONSTEXPR bool value = decltype(f<T_##SN>(0))::value;           \
	};                                                                            \
	template<typename T_##SN>                                                     \
	inline static DA_CONSTEXPR bool SN##_v = SN<T_##SN>::value;

#define DA_DECLVAL_WRAPPER(type) , std::declval<type>()

#endif //  _DA_TYPE_TRAITS_FUNCTION_DETECT_HPP_
