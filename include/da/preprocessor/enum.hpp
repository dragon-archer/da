/* SPDX-License-Identifier: MIT */
/**
 * @file      enum.hpp
 * @brief     Generate enums
 * @version   0.2
 * @author    dragon-archer
 *
 * @copyright Copyright (c) 2023 dragon-archer
 */

#ifndef _DA_PREPROCESSOR_ENUM_HPP_
#define _DA_PREPROCESSOR_ENUM_HPP_

#include <da/preprocessor/config.hpp>
#include <da/preprocessor/fold.hpp>
#include <da/preprocessor/tuple.hpp>
#include <type_traits>

/**
 * @brief Define a scoped mask enum e
 */
#define DA_DEFINE_SCOPED_MASK_ENUM(e, ...)             \
	enum class e {                                     \
		__VA_OPT__(DA_DEFINE_MASK_ENUM_I(__VA_ARGS__)) \
	}

/**
 * @brief Define a mask enum e
 */
#define DA_DEFINE_MASK_ENUM(e, ...)                    \
	enum e {                                           \
		__VA_OPT__(DA_DEFINE_MASK_ENUM_I(__VA_ARGS__)) \
	}

// clang-format off
#define DA_DEFINE_MASK_ENUM_I(x, ...) \
	x = 1                             \
	DA_TUPLE_UNPACK(                  \
		DA_TUPLE_REMOVE_HEAD(         \
			DA_FOLD_LEFT(DA_DEFINE_MASK_ENUM_O, (x), __VA_ARGS__)))
// clang-format on
#define DA_DEFINE_MASK_ENUM_O(x, y) \
	(y, DA_TUPLE_UNPACK(DA_TUPLE_REMOVE_HEAD(x)), y = DA_TUPLE_HEAD(x) << 1)

/**
 * @brief Assert e is an enum
 */
#define DA_ASSERT_ENUM(e) \
	static_assert(std::is_enum_v<e>, DA_STR(e) " is not an enum")

/**
 * @brief Define binary operation op for e
 */
#define DA_ENUM_BINARY_OP(e, op, prefix)                               \
	prefix e operator op(e x, e y) noexcept {                          \
		using t = std::underlying_type_t<e>;                           \
		return static_cast<e>(static_cast<t>(x) op static_cast<t>(y)); \
	}                                                                  \
	DA_STATEMENT()

/**
 * @brief Define unary operation op for e
 */
#define DA_ENUM_UNARY_OP(e, op, prefix)              \
	prefix e operator op(e x) noexcept {             \
		using t = std::underlying_type_t<e>;         \
		return static_cast<e>(op static_cast<t>(x)); \
	}                                                \
	DA_STATEMENT()

/**
 * @brief Define assignment operation op= for e
 */
#define DA_ENUM_ASSIGN_OP(e, op, prefix)                    \
	prefix e& operator DA_CAT2(op, =)(e& x, e y) noexcept { \
		return x = x op y;                                  \
	}                                                       \
	DA_STATEMENT()

/**
 * @brief Define bit operations for enum e
 */
#define DA_DEFINE_ENUM_OPS(e, prefix) \
	DA_ENUM_BINARY_OP(e, &, prefix);  \
	DA_ENUM_BINARY_OP(e, |, prefix);  \
	DA_ENUM_BINARY_OP(e, ^, prefix);  \
	DA_ENUM_ASSIGN_OP(e, &, prefix);  \
	DA_ENUM_ASSIGN_OP(e, |, prefix);  \
	DA_ENUM_ASSIGN_OP(e, ^, prefix);  \
	DA_ENUM_UNARY_OP(e, ~, prefix);

#endif // _DA_PREPROCESSOR_ENUM_HPP_
