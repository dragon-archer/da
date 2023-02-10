/**
 * @file      enum.hpp
 * @brief     Generate enums
 * @version   0.1
 * @author    dragon-archer
 *
 * @copyright Copyright (c) 2023
 */

#ifndef _LIBDA_PREPROCESSOR_ENUM_HPP_
#define _LIBDA_PREPROCESSOR_ENUM_HPP_

#include "base.hpp"
#include "cat.hpp"
#include <type_traits>

/**
 * @section DA_ASSERT_ENUM
 * @brief   Assert @param enum_ is an enum
 */
#define DA_ASSERT_ENUM(enum_) \
	static_assert(std::is_enum_v<enum_>, DA_STR(enum_) " is not an enum")

/**
 * @section DA_ENUM_BINARY_OP
 * @brief   Define binary operation @param op for @param enum_
 */
#define DA_ENUM_BINARY_OP(enum_, op)                                       \
	DA_ASSERT_ENUM(enum_);                                                 \
	inline constexpr enum_ operator op(enum_ x, enum_ y) {                 \
		using t = std::underlying_type_t<enum_>;                           \
		return static_cast<enum_>(static_cast<t>(x) op static_cast<t>(y)); \
	}                                                                      \
	DA_STATEMENT()

/**
 * @section DA_ENUM_UNARY_OP
 * @brief   Define unary operation @param op for @param enum_
 */
#define DA_ENUM_UNARY_OP(enum_, op)                      \
	DA_ASSERT_ENUM(enum_);                               \
	inline constexpr enum_ operator op(enum_ x) {        \
		using t = std::underlying_type_t<enum_>;         \
		return static_cast<enum_>(op static_cast<t>(x)); \
	}                                                    \
	DA_STATEMENT()

/**
 * @section DA_ENUM_ASSIGN_OP
 * @brief   Define assignment operation @param op= for @param enum_
 */
#define DA_ENUM_ASSIGN_OP(enum_, op)                                     \
	DA_ASSERT_ENUM(enum_);                                               \
	inline constexpr enum_& operator DA_CAT2(op, =)(enum_& x, enum_ y) { \
		return x = x op y;                                               \
	}                                                                    \
	DA_STATEMENT()

#define DA_MASK_ENUM_OPS(enum_)  \
	DA_ENUM_BINARY_OP(enum_, &); \
	DA_ENUM_BINARY_OP(enum_, |); \
	DA_ENUM_BINARY_OP(enum_, ^); \
	DA_ENUM_ASSIGN_OP(enum_, &); \
	DA_ENUM_ASSIGN_OP(enum_, |); \
	DA_ENUM_ASSIGN_OP(enum_, ^); \
	DA_ENUM_UNARY_OP(enum_, ~);

#endif // _LIBDA_PREPROCESSOR_ENUM_HPP_
