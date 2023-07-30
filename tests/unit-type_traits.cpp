/* SPDX-License-Identifier: MIT */
/**
 * @file      unit-type_traits.cpp
 * @brief     Unit test for module type_traits
 * @version   0.1
 * @author    dragon-archer
 *
 * @copyright Copyright (c) 2023 dragon-archer
 */

#include <da/type_traits.hpp>
#include <doctest/doctest.h>
using namespace da;

TEST_CASE("type_traits") {
	SUBCASE("get") {
		typelist<int, char, bool>::get_t<0> a{};
		CHECK((std::is_same_v<decltype(a), int>));
	}

	SUBCASE("pop_front") {
		typelist<int, char, bool>::pop_front_t b{};
		CHECK((std::is_same_v<decltype(b), typelist<char, bool>>));
	}

	SUBCASE("push_front") {
		typelist<int, char, bool>::push_front_t<long> c{};
		CHECK((std::is_same_v<decltype(c), typelist<long, int, char, bool>>));
	}

	SUBCASE("size") {
		DA_CONSTEXPR auto d = typelist<>::size();
		CHECK(d == 0);
		DA_CONSTEXPR auto e = typelist<long, int, char, bool>::size();
		CHECK(e == 4);
	}
}
