/**
 * @file      test_preprocessor.cpp
 * @brief     Test module preprocessor
 * @version   0.1
 * @author    dragon-archer
 *
 * @copyright Copyright (c) 2023
 */

#include "../include/preprocessor.hpp"
#include <gtest/gtest.h>

/**
 * @section preprocessor.dependency_graph
 * @brief   Dependency graph of preprocessor
 *
 * base ----> seq ----> fold ----> cat
 *      \
 *       ---> foreach
 */

/**
 * @section preprocessor.base
 * @brief   Tests for preprocessor module base
 * @note    No tests for @ref DA_HAS_VA_OPT and @ref DA_EXPAND
 */

TEST(preprocessor, DA_STR) {
#define DA_TEST_VAR 123

	// Nothing => empty string
	EXPECT_STREQ(DA_STR(), "");

	// Default usage
	EXPECT_STREQ(DA_STR(abcd), "abcd");

	// Punctuations
	// Note: '\' should be replaced by '\\'
	EXPECT_STREQ(DA_STR((,.{}[]`~!@#$%^&*-_=+|\\:;?/""'0')), "(,.{}[]`~!@#$%^&*-_=+|\\:;?/\"\"'0')");

	// Already quoted string
	EXPECT_STREQ(DA_STR("abcd"), "\"abcd\"");

	// Macro => expand and quote
	EXPECT_STREQ(DA_STR(DA_TEST_VAR), "123");

#undef DA_TEST_VAR
}

TEST(preprocessor, DA_CNT) {
	// Nothing => 0
	EXPECT_EQ(DA_CNT(), 0);

	// Single => 1
	EXPECT_EQ(DA_CNT(a), 1);
	EXPECT_EQ(DA_CNT(42), 1);

	// Mix identifier, number, non-identifier and keyword
	EXPECT_EQ(DA_CNT(a, 42, 1a, int), 4);

	// Test for edge case
	EXPECT_EQ(
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

/**
 * @section preprocessor.fold
 * @brief   Tests for preprocessor module fold
 * @note    No tests for @ref DA_FOLD as it is just a warpper of DA_FOLD_LEFT
 */

TEST(preprocessor, DA_FOLD_LEFT) {
#define DA_TEST_MACRO_PLUS(a, b)     (a + b)
#define DA_TEST_MACRO_SUBTRACT(a, b) (a - b)

	// Empty => nothing
	EXPECT_STREQ(DA_STR(DA_FOLD_LEFT(DA_TEST_MACRO_PLUS)), "");

	// Simple operations
	EXPECT_EQ(DA_FOLD_LEFT(DA_TEST_MACRO_PLUS, 1, 2, 3, 4, 5), 15);
	EXPECT_EQ(DA_FOLD_LEFT(DA_TEST_MACRO_SUBTRACT, 1, 2, 3, 4, 5), -13);

#undef DA_TEST_MACRO_PLUS
#undef DA_TEST_MACRO_SUBTRACT
}

/**
 * @section preprocessor.seq
 * @brief   Tests for preprocessor module seq
 */

TEST(preprocessor, DA_SEQ_HEAD) {
	// Empty => nothing
	EXPECT_STREQ(DA_STR(DA_SEQ_HEAD()), "");

	// Varadic arguments => rest of arguments ignored, can be anything
	EXPECT_EQ(DA_SEQ_HEAD(42, 1a, int, ()), 42);
}

TEST(preprocessor, DA_SEQ_REVERSE) {
	// Empty => nothing
	EXPECT_STREQ(DA_STR(DA_SEQ_REVERSE()), "");

	// Single => change nothing
	EXPECT_EQ(DA_SEQ_REVERSE(1), 1);

	// Varadic arguments => reverse
	auto sequence_dependent_func = [](int a, int b, int c, int d) {
		return a * 1 + b * 2 + c * 3 + d * 4;
	};
	EXPECT_EQ(sequence_dependent_func(DA_SEQ_REVERSE(1, 2, 3, 4)),
			  sequence_dependent_func(4, 3, 2, 1));
}

TEST(preprocessor, DA_SEQ_TAIL) {
	// Empty => nothing
	EXPECT_STREQ(DA_STR(DA_SEQ_TAIL()), "");

	// Varadic arguments => rest of arguments ignored, can be anything
	EXPECT_EQ(DA_SEQ_TAIL(1a, int, (), 42), 42);
}

/**
 * @section preprocessor.cat
 * @brief   Tests for preprocessor module cat
 */

TEST(preprocessor, DA_CAT) {
#define DA_TEST_VAR 345

	// Empty => nothing
	EXPECT_STREQ(DA_STR(DA_CAT()), "");

	// Single => just expand
	EXPECT_EQ(DA_CAT(1), 1);
	EXPECT_EQ(DA_CAT(DA_TEST_VAR), 345);

	// Multiple => expand and concat
	EXPECT_EQ(DA_CAT(1, 2), 12);
	EXPECT_EQ(DA_CAT(1, 2, DA_TEST_VAR), 12345);

	// Make identifier
	int a1 = 42;
	EXPECT_EQ(DA_CAT(a, 1), 42);

	// Non-identifier can be concat inside a string
	EXPECT_STREQ(DA_STR(DA_CAT(1, a)), "1a");

#undef DA_TEST_VAR
}

/**
 * @section preprocessor.foreach
 * @brief   Tests for preprocessor module foreach
 */

TEST(preprocessor, DA_FOREACH) {
#define DA_TEST_MACRO_ASSIGN(x) int x = 1;

	// Empty => nothing
	EXPECT_STREQ(DA_STR(DA_FOREACH(DA_TEST_MACRO_ASSIGN)), "");

	// Varadic arguments
	DA_FOREACH(DA_TEST_MACRO_ASSIGN, a, b, c);
	EXPECT_EQ(a, 1);
	EXPECT_EQ(b, 1);
	EXPECT_EQ(c, 1);

#undef DA_TEST_MACRO_ASSIGN
}
