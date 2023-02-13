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
#define DA_TEST_MACRO_PRED(data) DA_TUPLE_GET(0, data)
#define DA_TEST_MACRO_OP(data)   (DA_DEC(DA_TUPLE_GET(0, data)), (DA_TUPLE_GET(1, data) + DA_TUPLE_GET(0, data)))

TEST_CASE("preprocessor::arithmatic") {
	SUBCASE("DA_ADD") {
		// Basic use
		CHECK_EQ(DA_ADD(0, 3), 3);
		CHECK_EQ(DA_ADD(1, 2), 3);
		CHECK_EQ(DA_ADD(2, 1), 3);
		CHECK_EQ(DA_ADD(3, 0), 3);

		// Edge case
		CHECK_EQ(DA_ADD(0, 0), 0);
		CHECK_EQ(DA_ADD(0, 256), 256);
		CHECK_EQ(DA_ADD(1, 255), 256);
		CHECK_EQ(DA_ADD(255, 1), 256);
		CHECK_EQ(DA_ADD(256, 0), 256);
	}

	SUBCASE("DA_SUB") {
		// Basic use
		CHECK_EQ(DA_SUB(2, 1), 1);
		CHECK_EQ(DA_SUB(3, 0), 3);

		// Edge case
		CHECK_EQ(DA_SUB(0, 0), 0);
		CHECK_EQ(DA_SUB(256, 1), 255);
		CHECK_EQ(DA_SUB(256, 0), 256);
	}
}

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

		// Stringify multiple arguments
		CHECK_EQ(DA_STR(ab, cd), "ab, cd");
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

TEST_CASE("preprocessor::bool") {
	SUBCASE("DA_BOOL") {
		// 0 => 0
		CHECK_EQ(DA_BOOL(0), 0);

		// others => 1
		CHECK_EQ(DA_BOOL(1), 1);

		// Edge case
		CHECK_EQ(DA_BOOL(256), 1);

		// Valid for macros
		CHECK_EQ(DA_BOOL(DA_TEST_VAR), 1);
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

TEST_CASE("preprocessor::conditional") {
	SUBCASE("DA_IF") {
		// 0 => choose false branch
		CHECK_EQ(DA_IF(0, 1, 2), 2);

		// 1 => choose true branch
		CHECK_EQ(DA_IF(1, 1, 2), 1);

		// Valid for nesting
		CHECK_EQ(DA_IF(1, DA_IF(1, "a", "b"), DA_IF(0, "c", "d")), "a");
		CHECK_EQ(DA_IF(0, DA_IF(1, "a", "b"), DA_IF(0, "c", "d")), "d");

		// Valid for macros
		CHECK_EQ(DA_IF(DA_TEST_VAR, 1, 2), 1);
	}
}

TEST_CASE("preprocessor::dec") {
	SUBCASE("DA_DEC") {
		// 1 => 0
		CHECK_EQ(DA_DEC(1), 0);

		// Edge case
		CHECK_EQ(DA_DEC(256), 255);

		// Valid for macros
		CHECK_EQ(DA_DEC(DA_TEST_VAR), DA_TEST_VAR - 1);
	}
}

TEST_CASE("preprocessor::empty") {
	SUBCASE("DA_IS_EMPTY") {
		// nothing => true
		CHECK_EQ(DA_IS_EMPTY(), 1);

		// empty macro => true
		CHECK_EQ(DA_IS_EMPTY(DA_EMPTY()), 1);

		// macro => false
		CHECK_EQ(DA_IS_EMPTY(DA_EMPTY), 0);
		CHECK_EQ(DA_IS_EMPTY(DA_TEST_VAR), 0);

		// comma => false
		CHECK_EQ(DA_IS_EMPTY(, ), 0);
	}
}

TEST_CASE("preprocessor::fold") {
	SUBCASE("DA_FOLD") {
		// Empty => nothing
		CHECK_EQ(DA_STR(DA_FOLD(DA_TEST_MACRO_ADD)), "");

		// Simple operations
		CHECK_EQ(DA_FOLD(DA_TEST_MACRO_ADD, 1, 2, 3, 4, 5), 15);
		CHECK_EQ(DA_FOLD(DA_TEST_MACRO_SUB, 1, 2, 3, 4, 5), -13);
	}

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

		// Variadic arguments
		DA_FOREACH(DA_TEST_MACRO_DECLARE, a, b, c);
		CHECK_EQ(a, 1);
		CHECK_EQ(b, 1);
		CHECK_EQ(c, 1);
	}
}

TEST_CASE("preprocessor::inc") {
	SUBCASE("DA_INC") {
		// 0 => 1
		CHECK_EQ(DA_INC(0), 1);

		// Edge case
		CHECK_EQ(DA_INC(255), 256);

		// Valid for macros
		CHECK_EQ(DA_INC(DA_TEST_VAR), DA_TEST_VAR + 1);
	}
}

TEST_CASE("preprocessor::logical") {
	SUBCASE("DA_NOT") {
		// 0 => 1
		CHECK_EQ(DA_NOT(0), 1);

		// 1 => 0
		CHECK_EQ(DA_NOT(1), 0);

		// others => 0
		CHECK_EQ(DA_NOT(DA_TEST_VAR), 0);
	}

	SUBCASE("DA_AND2") {
		// 00 => 0
		CHECK_EQ(DA_AND2(0, 0), 0);

		// 01 => 0
		CHECK_EQ(DA_AND2(0, 1), 0);

		// 10 => 0
		CHECK_EQ(DA_AND2(1, 0), 0);

		// 11 => 1
		CHECK_EQ(DA_AND2(1, 1), 1);

		// others => equivalent to 1
		CHECK_EQ(DA_AND2(DA_TEST_VAR, 1), 1);
	}

	SUBCASE("DA_OR2") {
		// 00 => 0
		CHECK_EQ(DA_OR2(0, 0), 0);

		// 01 => 1
		CHECK_EQ(DA_OR2(0, 1), 1);

		// 10 => 1
		CHECK_EQ(DA_OR2(1, 0), 1);

		// 11 => 1
		CHECK_EQ(DA_OR2(1, 1), 1);

		// others => equivalent to 1
		CHECK_EQ(DA_OR2(DA_TEST_VAR, 0), 1);
	}

	SUBCASE("DA_AND") {
		// empty => 1
		CHECK_EQ(DA_AND(), 1);

		// same as DA_AND2()
		CHECK_EQ(DA_AND(0), 0);
		CHECK_EQ(DA_AND(1), 1);
		CHECK_EQ(DA_AND(0, 0), 0);
		CHECK_EQ(DA_AND(0, 1), 0);
		CHECK_EQ(DA_AND(1, 0), 0);
		CHECK_EQ(DA_AND(1, 1), 1);
		CHECK_EQ(DA_AND(0, 0, 0), 0);
		CHECK_EQ(DA_AND(0, 0, 1), 0);
		CHECK_EQ(DA_AND(0, 1, 0), 0);
		CHECK_EQ(DA_AND(0, 1, 1), 0);
		CHECK_EQ(DA_AND(1, 0, 0), 0);
		CHECK_EQ(DA_AND(1, 0, 1), 0);
		CHECK_EQ(DA_AND(1, 1, 0), 0);
		CHECK_EQ(DA_AND(1, 1, 1), 1);

		// short-circuited
		CHECK_EQ(DA_AND(0, syntax error), 0);
	}

	SUBCASE("DA_OR") {
		// empty => 1
		CHECK_EQ(DA_OR(), 0);

		// same as DA_OR2()
		CHECK_EQ(DA_OR(0), 0);
		CHECK_EQ(DA_OR(1), 1);
		CHECK_EQ(DA_OR(0, 0), 0);
		CHECK_EQ(DA_OR(0, 1), 1);
		CHECK_EQ(DA_OR(1, 0), 1);
		CHECK_EQ(DA_OR(1, 1), 1);
		CHECK_EQ(DA_OR(0, 0, 0), 0);
		CHECK_EQ(DA_OR(0, 0, 1), 1);
		CHECK_EQ(DA_OR(0, 1, 0), 1);
		CHECK_EQ(DA_OR(0, 1, 1), 1);
		CHECK_EQ(DA_OR(1, 0, 0), 1);
		CHECK_EQ(DA_OR(1, 0, 1), 1);
		CHECK_EQ(DA_OR(1, 1, 0), 1);
		CHECK_EQ(DA_OR(1, 1, 1), 1);

		// short-circuited
		CHECK_EQ(DA_OR(1, syntax error), 1);
	}
}

TEST_CASE("preprocessor::seq") {
	SUBCASE("DA_SEQ_HEAD") {
		// Empty => nothing
		CHECK_EQ(DA_STR(DA_SEQ_HEAD()), "");

		// Variadic arguments => rest of arguments ignored, can be anything
		CHECK_EQ(DA_SEQ_HEAD(42, 1a, int, ()), 42);
	}

	SUBCASE("DA_SEQ_REVERSE") {
		// Empty => nothing
		CHECK_EQ(DA_STR(DA_SEQ_REVERSE()), "");

		// Single => change nothing
		CHECK_EQ(DA_SEQ_REVERSE(1), 1);

		// Variadic arguments => reverse
		auto sequence_dependent_func = [](int a, int b, int c, int d) {
			return a * 1 + b * 2 + c * 3 + d * 4;
		};
		CHECK_EQ(sequence_dependent_func(DA_SEQ_REVERSE(1, 2, 3, 4)),
				 sequence_dependent_func(4, 3, 2, 1));
	}

	SUBCASE("DA_SEQ_TAIL") {
		// Empty => nothing
		CHECK_EQ(DA_STR(DA_SEQ_TAIL()), "");

		// Variadic arguments => rest of arguments ignored, can be anything
		CHECK_EQ(DA_SEQ_TAIL(1a, int, (), 42), 42);
	}

	SUBCASE("DA_SEQ_GET") {
		// Basic use
		CHECK_EQ(DA_SEQ_GET(0, "a"), "a");
		CHECK_EQ(DA_SEQ_GET(1, "a", "b"), "b");

		// Unused arguments ignored
		CHECK_EQ(DA_SEQ_GET(1, syntax error, 2, syntax error), 2);
	}
}

TEST_CASE("preprocessor::tuple") {
	SUBCASE("DA_IS_TUPLE") {
		// Empty => 0
		CHECK_EQ(DA_IS_TUPLE(), 0);

		// Empty tuple => 1
		CHECK_EQ(DA_IS_TUPLE(()), 1);

		// Basic use
		CHECK_EQ(DA_IS_TUPLE(seq), 0);
		CHECK_EQ(DA_IS_TUPLE((tuple1, tuple2)), 1);
	}

	SUBCASE("DA_TUPLE_UNPACK") {
		// Basic use
		int DA_TUPLE_UNPACK((a = 1, b = 2, c = 3, d = 4));
		CHECK_EQ(a, 1);
		CHECK_EQ(b, 2);
		CHECK_EQ(c, 3);
		CHECK_EQ(d, 4);
	}

	SUBCASE("DA_TUPLE_UNPACK_OPT") {
		// Basic use
		int DA_TUPLE_UNPACK_OPT((a = 1, b = 2));
		int DA_TUPLE_UNPACK_OPT(c = 3, d = 4);
		CHECK_EQ(a, 1);
		CHECK_EQ(b, 2);
		CHECK_EQ(c, 3);
		CHECK_EQ(d, 4);
	}

	SUBCASE("DA_TUPLE_SIZE") {
		// Basic use
		CHECK_EQ(DA_TUPLE_SIZE(()), 0);
		CHECK_EQ(DA_TUPLE_SIZE((1, 2)), 2);
	}

	SUBCASE("DA_TUPLE_GET") {
		// Basic use
		CHECK_EQ(DA_TUPLE_GET(0, ("a")), "a");
		CHECK_EQ(DA_TUPLE_GET(1, ("a", "b")), "b");

		// Unused arguments ignored
		CHECK_EQ(DA_TUPLE_GET(1, (syntax error, 2, syntax error)), 2);
	}
}

TEST_CASE("preprocessor::while") {
	SUBCASE("DA_WHILE") {
		// Basic use
		CHECK_EQ(DA_WHILE(DA_TEST_MACRO_PRED, DA_TEST_MACRO_OP, (2, 4)), 7);
	}
}

#undef DA_TEST_VAR
#undef DA_TEST_MACRO_ADD
#undef DA_TEST_MACRO_SUB
#undef DA_TEST_MACRO_DECLARE
#undef DA_TEST_MACRO_PRED
#undef DA_TEST_MACRO_OP
