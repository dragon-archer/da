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

	int                        argc       = 2;
	char const*                argv[]     = {"program", "--option"};
	std::string_view           name       = "option";
	std::string_view           name2      = "option2";
	char                       shortname  = 'o';
	char                       shortname2 = 'p';
	cmdline_parser::callback_t callback   = [](std::string_view content) {};

#define VALID_HANDLE(handle)   CHECK_NE((handle), cmdline_parser::invalid_handle)
#define INVALID_HANDLE(handle) CHECK_EQ((handle), cmdline_parser::invalid_handle)

	SUBCASE("constructors") {
		SUBCASE("empty constructor") {
			cmdline_parser cp{};

			CHECK(true);
		}
	}

	SUBCASE("add_option") {
		SUBCASE("no short option") {
			cmdline_parser cp{};

			VALID_HANDLE(cp.add_option(name, callback));
		}

		SUBCASE("with short option") {
			cmdline_parser cp{};

			VALID_HANDLE(cp.add_option(name, shortname, callback));
		}

		SUBCASE("fail if already existed") {
			cmdline_parser cp1{}, cp2{};

			INVALID_HANDLE(cp1.add_option("", callback));
			VALID_HANDLE(cp1.add_option(name, callback));
			INVALID_HANDLE(cp1.add_option(name, shortname, callback));
			VALID_HANDLE(cp1.add_option(name2, shortname, callback));

			VALID_HANDLE(cp2.add_option(name, shortname, callback));
			INVALID_HANDLE(cp2.add_option(name2, shortname, callback));
			VALID_HANDLE(cp2.add_option(name2, callback));
		}
	}

	SUBCASE("get_handle") {
		cmdline_parser cp{};
		auto           h = cp.add_option(name, shortname, callback);
		VALID_HANDLE(h);

		SUBCASE("get by name") {
			CHECK_EQ(cp.get_handle(name), h);
			INVALID_HANDLE(cp.get_handle(name2));
		}

		SUBCASE("get by short name") {
			CHECK_EQ(cp.get_handle(shortname), h);
			INVALID_HANDLE(cp.get_handle(shortname2));
		}
	}
}
