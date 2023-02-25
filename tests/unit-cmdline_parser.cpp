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
	std::string_view           name2     = "option2";
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

		SUBCASE("fail if already existed") {
			cmdline_parser cp1{}, cp2{};

			CHECK(!cp1.add_option("", callback));
			CHECK(cp1.add_option(name, callback));
			CHECK(!cp1.add_option(name, shortname, callback));
			CHECK(cp1.add_option(name2, shortname, callback));

			CHECK(cp2.add_option(name, shortname, callback));
			CHECK(!cp2.add_option(name2, shortname, callback));
			CHECK(!cp2.add_option(name2, callback));
		}
	}
}
