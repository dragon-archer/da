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

template class da::fixed_point<5>; // Explicit instantiation so that the coverage is real

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
			CHECK_CE(f5{}, 0);
			CHECK_CE(f5{1}, 1);
			CHECK_CE((f5{1, da::no_conversion}.raw()), 1);
			CHECK_CE(f5{f6{1}}, 1);
		}
		SUBCASE("getter & setter") {
			CHECK_CE(int(f5{1}), 1);
			f5 x;
			CHECK(x.set(1).get<int>() == 1);
			const f5 y{1};
			CHECK(y.raw() == 1e5);
		}
		SUBCASE("is_integer") {
			CHECK_CE(f5{1}.is_integer(), true);
			CHECK_CE(f5{1.5}.is_integer(), false);
		}
		SUBCASE("add") {
			CHECK_CE(f5{1} + 2, 3);
			CHECK_CE(2 + f5{1}, 3);
			CHECK_CE(f5{1} += 2, 3);
			CHECK_CE(f5{1} += f5{2}, 3);
		}
		SUBCASE("subtract") {
			CHECK_CE(f5{1} - 2, -1);
			CHECK_CE(2 - f5{1}, 1);
			CHECK_CE(f5{1} -= 2, -1);
			CHECK_CE(f5{1} -= f5{2}, -1);
		}
		SUBCASE("multiply") {
			CHECK_CE(f5{1} * 2, 2);
			CHECK_CE(2 * f5{1}, 2);
			CHECK_CE(f5{1} *= 2, 2);
			CHECK_CE(f5{1} *= f5{2}, 2);
		}
		SUBCASE("divide") {
			CHECK_CE(f5{1} / 2, 0.5);
			CHECK_CE(2 / f5{1}, 2);
			CHECK_CE(f5{1} /= 2, 0.5);
			CHECK_CE(f5{1} /= f5{2}, 0.5);
		}
		SUBCASE("mix") {
			CHECK_CE(((-f5{1} + f5{2} - f5{0.5}) * f5{3} / f5{5}), 0.3);
		}
		SUBCASE("comparison") {
			CHECK_CE(f5{1} < f5{2}, true);
			CHECK_CE(f5{2} > f5{1}, true);
			CHECK_CE(f5{1} <= f5{1}, true);
			CHECK_CE(f5{1} >= f5{-1}, true);
			CHECK_CE(f5{1} == f5{1}, true);
			CHECK_CE(f5{1} != f5{2}, true);

			CHECK_CE(f5{1} < 2, true);
			CHECK_CE(f5{2} > 1, true);
			CHECK_CE(f5{1} <= 1, true);
			CHECK_CE(f5{1} >= -1, true);
			CHECK_CE(f5{1} == 1, true);
			CHECK_CE(f5{1} != 2, true);

			CHECK_CE(2 > f5{1}, true);
			CHECK_CE(1 < f5{2}, true);
			CHECK_CE(1 >= f5{1}, true);
			CHECK_CE(-1 <= f5{1}, true);
			CHECK_CE(1 == f5{1}, true);
			CHECK_CE(2 != f5{1}, true);
		}
		SUBCASE("format") {
			CHECK_EQ(da::fmt::format("{}", f5{1}), "1");
			CHECK_EQ(da::fmt::format("{:*^+10.2f}", f5{1.502}), "**+1.50***");
		}
	}
}
