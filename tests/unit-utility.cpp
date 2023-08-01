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
			CHECK_CE(da::pow(3, -1), 0);

			CHECK_CE(da::pow(3.0, 10), 59049.0);
			CHECK_CE(da::pow(3.0, -1), 1.0 / 3);
		}
	}

	SUBCASE("fixed_point") {
		using f5 = da::fixed_point<5>;
		using f6 = da::fixed_point<6>;
		SUBCASE("constructor") {
			CHECK_CE(f5().raw(), 0);
			CHECK_CE(f5(1).raw(), 1e5);
			CHECK_CE(f5(1, da::no_conversion).raw(), 1);
		}
		CHECK_CE((f5(2) * 3).raw(), 6e5);
		SUBCASE("format") {
			std::string s = da::fmt::format("{}", f5(1));
			CHECK(s == "1");
		}
	}
}
