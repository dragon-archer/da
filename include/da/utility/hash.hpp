/* SPDX-License-Identifier: MIT */
/**
 * @file      hash.hpp
 * @brief     Hash function
 * @version   0.1
 * @author    dragon-archer
 *
 * @copyright Copyright (c) 2023 dragon-archer
 */

#ifndef _DA_UTILITY_HASH_HPP_
#define _DA_UTILITY_HASH_HPP_

#include <da/config.hpp>
#include <da/string/misc.hpp>
#include <string>
#include <string_view>

DA_BEGIN_NAMESPACE

#if(DA_GCC && (DA_GCC < 12)) || (DA_CLANG && (DA_CLANG < 15))
	#define DA_STRING_CONSTEXPR_OR_INLINE inline
	#define DA_STRING_CONSTEXPR
#else
	#define DA_STRING_CONSTEXPR_OR_INLINE DA_CONSTEXPR
	#define DA_STRING_CONSTEXPR           DA_CONSTEXPR
#endif

DA_CONSTEXPR size_t fnv1a_hash(const char* p, size_t len) noexcept {
	DA_CONSTEXPR size_t fnv_prime        = 0x00000100000001B3;
	DA_CONSTEXPR size_t fnv_offset_basis = 0xCBF29CE484222325;

	DA_ASSUME(p != nullptr);

	size_t v = fnv_offset_basis;
	while(len--) {
		v ^= static_cast<size_t>(*p);
		v *= fnv_prime;
		++p;
	}
	return v;
}

template<typename T>
inline size_t hash(const T& x) noexcept {
	return fnv1a_hash(reinterpret_cast<const char*>(&x), sizeof(T));
}

template<>
DA_STRING_CONSTEXPR_OR_INLINE size_t hash(const std::string& x) noexcept {
	return fnv1a_hash(x.data(), x.size());
}

template<>
DA_CONSTEXPR size_t hash(const std::string_view& x) noexcept {
	return fnv1a_hash(x.data(), x.size());
}

template<>
DA_CONSTEXPR size_t hash(const char* const& x) noexcept {
	DA_ASSUME(x != nullptr);
	return fnv1a_hash(x, strlen(x));
}

template<size_t N>
DA_CONSTEXPR size_t hash(const char (&x)[N]) noexcept {
	return fnv1a_hash(x, N - 1); // Discard '\0'
}

DA_END_NAMESPACE

#endif // _DA_UTILITY_HASH_HPP_
