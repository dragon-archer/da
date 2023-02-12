/**
 * @file      unit-preprocessor.cpp
 * @brief     Unit test for module preprocessor
 * @version   0.1
 * @author    dragon-archer
 *
 * @copyright Copyright (c) 2023
 */

#include <da/preprocessor.hpp>
#include <doctest/doctest.h>

#define DA_TEST_VAR              123
#define DA_TEST_MACRO_ADD(a, b)  (a + b)
#define DA_TEST_MACRO_SUB(a, b)  (a - b)
#define DA_TEST_MACRO_DECLARE(x) int x = 1;

TEST_CASE("preprocessor::base") {
	SUBCASE("DA_STR") {
		// Nothing => empty string
		CHECK_EQ(DA_STR(), "");

		// Default usage
		CHECK_EQ(DA_STR(abcd), "abcd");

		// Punctuations
		// Note: '\' should be replaced by '\\'
		CHECK_EQ(DA_STR((,.{}[]`~!@#$%^&*-_=+|\\:;?/""'0')), "(,.{}[]`~!@#$%^&*-_=+|\\:;?/\"\"'0')");

		// Already quoted string
		CHECK_EQ(DA_STR("abcd"), "\"abcd\"");

		// Macro => expand and stringify
		CHECK_EQ(DA_STR(DA_TEST_VAR), "123");
	}

	SUBCASE("DA_CNT") {
		// Nothing => 0
		CHECK_EQ(DA_CNT(), 0);

		// Single => 1
		CHECK_EQ(DA_CNT(a), 1);
		CHECK_EQ(DA_CNT(42), 1);

		// Mix identifier, number, non-identifier and keyword
		CHECK_EQ(DA_CNT(a, 42, 1a, int), 4);

		// Test for edge case
		CHECK_EQ(
			DA_CNT(
				01, 02, 03, 04, 05, 06, 07, 08, 09, 10,
				11, 12, 13, 14, 15, 16, 17, 18, 19, 20,
				21, 22, 23, 24, 25, 26, 27, 28, 29, 30,
				31, 32, 33, 34, 35, 36, 37, 38, 39, 40,
				41, 42, 43, 44, 45, 46, 47, 48, 49, 50,
				51, 52, 53, 54, 55, 56, 57, 58, 59, 60,
				61, 62, 63, 64),
			64);
	}
}

TEST_CASE("preprocessor::cat") {
	SUBCASE("DA_CAT") {
		// Empty => nothing
		CHECK_EQ(DA_STR(DA_CAT()), "");

		// Single => just expand
		CHECK_EQ(DA_CAT(1), 1);
		CHECK_EQ(DA_CAT(DA_TEST_VAR), 123);

		// Multiple => expand and concat
		CHECK_EQ(DA_CAT(1, 2), 12);
		CHECK_EQ(DA_CAT(1, 2, DA_TEST_VAR), 12123);

		// Make identifier
		int a1 = 42;
		CHECK_EQ(DA_CAT(a, 1), 42);

		// Non-identifier can be concat inside a string
		CHECK_EQ(DA_STR(DA_CAT(1, a)), "1a");
	}
}

TEST_CASE("preprocessor::fold") {
	SUBCASE("DA_FOLD_LEFT") {
		// Empty => nothing
		CHECK_EQ(DA_STR(DA_FOLD_LEFT(DA_TEST_MACRO_ADD)), "");

		// Simple operations
		CHECK_EQ(DA_FOLD_LEFT(DA_TEST_MACRO_ADD, 1, 2, 3, 4, 5), 15);
		CHECK_EQ(DA_FOLD_LEFT(DA_TEST_MACRO_SUB, 1, 2, 3, 4, 5), -13);
	}
}

TEST_CASE("preprocessor::foreach") {
	SUBCASE("DA_FOREACH") {
		// Empty => nothing
		CHECK_EQ(DA_STR(DA_FOREACH(DA_TEST_MACRO_DECLARE)), "");

		// Varadic arguments
		DA_FOREACH(DA_TEST_MACRO_DECLARE, a, b, c);
		CHECK_EQ(a, 1);
		CHECK_EQ(b, 1);
		CHECK_EQ(c, 1);
	}
}

TEST_CASE("preprocessor::seq") {
	SUBCASE("DA_SEQ_HEAD") {
		// Empty => nothing
		CHECK_EQ(DA_STR(DA_SEQ_HEAD()), "");

		// Varadic arguments => rest of arguments ignored, can be anything
		CHECK_EQ(DA_SEQ_HEAD(42, 1a, int, ()), 42);
	}

	SUBCASE("DA_SEQ_REVERSE") {
		// Empty => nothing
		CHECK_EQ(DA_STR(DA_SEQ_REVERSE()), "");

		// Single => change nothing
		CHECK_EQ(DA_SEQ_REVERSE(1), 1);

		// Varadic arguments => reverse
		auto sequence_dependent_func = [](int a, int b, int c, int d) {
			return a * 1 + b * 2 + c * 3 + d * 4;
		};
		CHECK_EQ(sequence_dependent_func(DA_SEQ_REVERSE(1, 2, 3, 4)),
				 sequence_dependent_func(4, 3, 2, 1));
	}

	SUBCASE("DA_SEQ_TAIL") {
		// Empty => nothing
		CHECK_EQ(DA_STR(DA_SEQ_TAIL()), "");

		// Varadic arguments => rest of arguments ignored, can be anything
		CHECK_EQ(DA_SEQ_TAIL(1a, int, (), 42), 42);
	}
}

#undef DA_TEST_VAR
#undef DA_TEST_MACRO_ADD
#undef DA_TEST_MACRO_SUB
#undef DA_TEST_MACRO_DECLARE
