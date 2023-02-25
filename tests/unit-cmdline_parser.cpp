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

TEST_CASE("cmdline_parser") {
	using namespace da;

	int                        argc      = 2;
	char const*                argv[]    = {"program", "--option"};
	std::string_view           name      = "option";
	char                       shortname = 'o';
	cmdline_parser::callback_t callback  = [](std::string_view content) {};

	SUBCASE("constructors") {
		SUBCASE("empty constructor") {
			cmdline_parser cp{};
			CHECK(true);
		}

		SUBCASE("construct with argc and argv") {
			cmdline_parser cp{argc, argv};
			CHECK(true);
		}
	}

	SUBCASE("add_option") {
		SUBCASE("no short option") {
			cmdline_parser cp{};
			CHECK(cp.add_option(name, callback));
		}

		SUBCASE("with short option") {
			cmdline_parser cp{};
			CHECK(cp.add_option(name, shortname, callback));
		}
	}
}
