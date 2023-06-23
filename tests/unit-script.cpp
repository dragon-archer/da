/* SPDX-License-Identifier: MIT */
/**
 * @file      unit-script.cpp
 * @brief     Unit test for module script
 * @version   0.1
 * @author    dragon-archer
 *
 * @copyright Copyright (c) 2023 dragon-archer
 */

#include <da/script.hpp>
#include <doctest/doctest.h>
using namespace da;

TEST_CASE("script") {
	SUBCASE("hash") {
		CHECK_EQ(script::hash("password"), 0x4b1a493507b3a318);
	}
}
