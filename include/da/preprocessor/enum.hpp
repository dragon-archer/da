/**
 * @file      enum.hpp
 * @brief     Generate enums
 * @version   0.1
 * @author    dragon-archer
 *
 * @copyright Copyright (c) 2023
 */

#ifndef _DA_PREPROCESSOR_ENUM_HPP_
#define _DA_PREPROCESSOR_ENUM_HPP_

#include <da/preprocessor/base.hpp>
#include <da/preprocessor/tuple.hpp>
#include <da/preprocessor/while.hpp>
#include <type_traits>

/**
 * @brief Define a scoped mask enum e
 */
#define DA_DEFINE_SCOPED_MASK_ENUM(e, ...) \
	enum class e {                         \
		DA_DEFINE_MASK_ENUM_I(__VA_ARGS__) \
	}

/**
 * @brief Define a mask enum e
 */
#define DA_DEFINE_MASK_ENUM(e, ...)        \
	enum e {                               \
		DA_DEFINE_MASK_ENUM_I(__VA_ARGS__) \
	}

#define DA_DEFINE_MASK_ENUM_I(...)         \
	DA_TUPLE_UNPACK(                       \
		DA_TUPLE_REMOVE_HEAD(              \
			DA_TUPLE_GET(                  \
				2,                         \
				DA_WHILE(                  \
					DA_DEFINE_MASK_ENUM_P, \
					DA_DEFINE_MASK_ENUM_O, \
					(0, (__VA_ARGS__), ())))))
#define DA_DEFINE_MASK_ENUM_P(d) DA_TUPLE_SIZE(DA_TUPLE_GET(1, d))
#define DA_DEFINE_MASK_ENUM_O(d)               \
	(DA_INC(DA_TUPLE_HEAD(d)),                 \
	 DA_TUPLE_REMOVE_HEAD(DA_TUPLE_GET(1, d)), \
	 DA_TUPLE_INSERT_TAIL(                     \
		 DA_TUPLE_GET(2, d),                   \
		 DA_TUPLE_HEAD(DA_TUPLE_GET(1, d)) = 1 << DA_TUPLE_HEAD(d)))

/**
 * @brief Assert e is an enum
 */
#define DA_ASSERT_ENUM(e) \
	static_assert(std::is_enum_v<e>, DA_STR(e) " is not an enum")

/**
 * @brief Define binary operation op for e
 */
#define DA_ENUM_BINARY_OP(e, op)                                       \
	DA_ASSERT_ENUM(e);                                                 \
	inline static constexpr e operator op(e x, e y) noexcept {         \
		using t = std::underlying_type_t<e>;                           \
		return static_cast<e>(static_cast<t>(x) op static_cast<t>(y)); \
	}                                                                  \
	DA_STATEMENT()

/**
 * @brief Define unary operation op for e
 */
#define DA_ENUM_UNARY_OP(e, op)                           \
	DA_ASSERT_ENUM(e);                                    \
	inline static constexpr e operator op(e x) noexcept { \
		using t = std::underlying_type_t<e>;              \
		return static_cast<e>(op static_cast<t>(x));      \
	}                                                     \
	DA_STATEMENT()

/**
 * @brief Define assignment operation op= for e
 */
#define DA_ENUM_ASSIGN_OP(e, op)                                             \
	DA_ASSERT_ENUM(e);                                                       \
	inline static constexpr e& operator DA_CAT2(op, =)(e& x, e y) noexcept { \
		return x = x op y;                                                   \
	}                                                                        \
	DA_STATEMENT()

/**
 * @brief Define bit operations for enum e
 */
#define DA_DEFINE_ENUM_OPS(e) \
	DA_ENUM_BINARY_OP(e, &);  \
	DA_ENUM_BINARY_OP(e, |);  \
	DA_ENUM_BINARY_OP(e, ^);  \
	DA_ENUM_ASSIGN_OP(e, &);  \
	DA_ENUM_ASSIGN_OP(e, |);  \
	DA_ENUM_ASSIGN_OP(e, ^);  \
	DA_ENUM_UNARY_OP(e, ~);

#endif // _DA_PREPROCESSOR_ENUM_HPP_
