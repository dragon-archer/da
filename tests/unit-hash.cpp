/* SPDX-License-Identifier: MIT */
/**
 * @file      unit-hash.cpp
 * @brief     Unit test for hash
 * @version   0.1
 * @author    dragon-archer
 *
 * @copyright Copyright (c) 2023 dragon-archer
 */

#include <da/utility/hash.hpp>
#include <doctest/doctest.h>

TEST_CASE("hash") {
	CHECK_EQ(da::hash("password"), 0x4b1a493507b3a318);
	CHECK_EQ(da::hash(42), 0x8d9aadc8352fdf7f);
}
