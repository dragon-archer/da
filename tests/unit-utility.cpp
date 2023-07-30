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

using namespace std::literals;

#define CHECK_CE(x, y)           \
	do {                         \
		DA_CONSTEXPR auto v = x; \
		CHECK_EQ(v, y);          \
	} while(0)

TEST_CASE("utility") {
	SUBCASE("hash") {
		DA_CONSTEXPR auto hash_of_password = 0x4b1a493507b3a318;
		SUBCASE("Any type") {
			CHECK(da::hash(42) == 0x8d9aadc8352fdf7f);
		}
		SUBCASE("std::string") {
			DA_STRING_CONSTEXPR auto x = da::hash("password"s);
			CHECK(x == hash_of_password);
		}
		SUBCASE("std::string_view") {
			CHECK_CE(da::hash("password"sv), hash_of_password);
		}
		SUBCASE("const char*") {
			DA_CONSTEXPR auto p = "password";
			CHECK_CE(da::hash(p), hash_of_password);
		}
		SUBCASE("const char[]") {
			CHECK_CE(da::hash("password"), hash_of_password);
		}
	}

	SUBCASE("math") {
		SUBCASE("pow") {
			CHECK_CE(da::pow(0, 0), 0);
			CHECK_CE(da::pow(0, 42), 0);
			CHECK_CE(da::pow(0, -42), 0);

			CHECK_CE(da::pow(1, 0), 1);
			CHECK_CE(da::pow(1, 42), 1);
			CHECK_CE(da::pow(1, -42), 1);

			CHECK_CE(da::pow(2, 0), 1);
			CHECK_CE(da::pow(2, 2), 4);
			CHECK_CE(da::pow(2, -1), 1);
			CHECK_CE(da::pow(2, -2), 0);

			CHECK_CE(da::pow(3.0, 10), 59049.0);
		}
	}
}
