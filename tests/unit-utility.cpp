/* SPDX-License-Identifier: MIT */
/**
 * @file      unit-hash.cpp
 * @brief     Unit test for hash
 * @version   0.1
 * @author    dragon-archer
 *
 * @copyright Copyright (c) 2023 dragon-archer
 */

#include <da/utility.hpp>
#include <doctest/doctest.h>

TEST_CASE("utility") {
	SUBCASE("hash") {
		SUBCASE("Any type") {
			CHECK_EQ(da::hash(42), 0x8d9aadc8352fdf7f);
		}
		SUBCASE("std::string") {
			constexpr auto           sv = std::string_view("password");
			DA_STRING_CONSTEXPR auto s  = sv;
			DA_STRING_CONSTEXPR auto x  = da::hash(s);
			CHECK_EQ(x, 0x4b1a493507b3a318);
		}
		SUBCASE("std::string_view") {
			constexpr auto sv = std::string_view("password");
			constexpr auto x  = da::hash(sv);
			CHECK_EQ(x, 0x4b1a493507b3a318);
		}
		SUBCASE("const char*") {
			constexpr auto p = "password";
			constexpr auto x = da::hash(p);
			CHECK_EQ(x, 0x4b1a493507b3a318);
		}
		SUBCASE("const char[]") {
			constexpr auto x = da::hash("password");
			CHECK_EQ(x, 0x4b1a493507b3a318);
		}
	}
}
