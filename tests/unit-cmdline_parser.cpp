/**
 * @file      unit-cmdline_parser.cpp
 * @brief     Unit test for module cmdline_parser
 * @version   0.1
 * @author    dragon-archer
 *
 * @copyright Copyright (c) 2023
 */

#include <da/cmdline_parser.hpp>
#include <doctest/doctest.h>

TEST_CASE("cmdline_parser::base") {
	using namespace da;
	cmdline_parser cp{};
	cp.enable(1);
	cp.disable(1);
	(void)cp.enabled(1);
	(void)cp.flags();
	CHECK(true);
}
