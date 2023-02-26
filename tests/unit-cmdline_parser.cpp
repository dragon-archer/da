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
#if DA_MSVC
	#include <iostream> // Fix for MSVC
#endif

TEST_CASE("cmdline_parser") {
	using namespace da;

	cmdline_parser::string_t   name       = "option";
	cmdline_parser::string_t   name2      = "option2";
	char                       shortname  = 'o';
	char                       shortname2 = 'p';
	cmdline_parser::callback_t callback   = [](std::string_view content) { CHECK_EQ(content, "hello"); };
	cmdline_parser::callback_t callback2  = [](std::string_view content) { CHECK_EQ(content, "hello2"); };

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

	SUBCASE("parse") {
		int            argc   = 5;
		char const*    argv[] = {"program", "--option=hello", "--option2=hello2", "-ohello", "-phello2", nullptr};
		cmdline_parser cp{};
		cp.add_option(name, shortname, callback);
		cp.add_option(name2, shortname2, callback2);

		SUBCASE("normal use") {
			CHECK_EQ(cp.parse(argc, argv), cmdline_parser::SUCCESS);
		}

		SUBCASE("unexpected end") {
			CHECK_EQ(cp.parse(0, argv), cmdline_parser::UNEXPECTED_END);
			CHECK_EQ(cp.parse(argc, nullptr), cmdline_parser::UNEXPECTED_END);
			CHECK_EQ(cp.parse(argc + 1, argv), cmdline_parser::UNEXPECTED_END);
		}

		SUBCASE("empty argument") {
			int         argc   = 2;
			char const* argv[] = {"program", "", nullptr};

			CHECK_EQ(cp.parse(argc, argv), cmdline_parser::SUCCESS);
		}

		SUBCASE("missing argument") {
			int         argc    = 2;
			char const* argv1[] = {"program", "--abcd", nullptr};
			char const* argv2[] = {"program", "-o", nullptr};

			CHECK_EQ(cp.parse(argc, argv1), cmdline_parser::MISSING_ARGUMENT);
			CHECK_EQ(cp.parse(argc, argv2), cmdline_parser::MISSING_ARGUMENT);
		}

		SUBCASE("missing option") {
			int         argc    = 2;
			char const* argv1[] = {"program", "--", nullptr};
			char const* argv2[] = {"program", "-", nullptr};

			CHECK_EQ(cp.parse(argc, argv1), cmdline_parser::MISSING_OPTION);
			CHECK_EQ(cp.parse(argc, argv2), cmdline_parser::MISSING_OPTION);
		}

		SUBCASE("unknown option") {
			int         argc    = 2;
			char const* argv1[] = {"program", "--unknown=1", nullptr};
			char const* argv2[] = {"program", "-u1", nullptr};

			CHECK_EQ(cp.parse(argc, argv1), cmdline_parser::UNKNOWN_OPTION);
			CHECK_EQ(cp.parse(argc, argv2), cmdline_parser::UNKNOWN_OPTION);
		}

		SUBCASE("unexpected argument") {
			int         argc    = 2;
			char const* argv[] = {"program", "unknown", nullptr};

			CHECK_EQ(cp.parse(argc, argv), cmdline_parser::UNEXPECTED_ARGUMENT);
		}
	}
}
