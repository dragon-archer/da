/**
 * @file      cmdline_parser.hpp
 * @brief     Command line parser
 * @version   0.1
 * @author    dragon-archer
 *
 * @copyright Copyright (c) 2023
 */

#ifndef _DA_CMDLINE_PARSER_HPP_
#define _DA_CMDLINE_PARSER_HPP_

#include <da/config.hpp>
#include <da/preprocessor/enum.hpp>
#include <functional>
#include <map>
#include <string_view>

DA_BEGIN_NAMESPACE

class cmdline_parser {
	public:
	using callback_t = std::function<void(std::string_view)>;

	cmdline_parser()
		: _argc(0)
		, _argv(nullptr) { }

	cmdline_parser(int argc, char const** argv)
		: _argc(argc)
		, _argv(argv) { }

	bool add_option(std::string_view name, callback_t const& callback) {
		return add_option(name, '\0', callback);
	}

	bool add_option(std::string_view name, char shortname, callback_t const& callback) {
		return !name.empty()
			&& _options.emplace(name, callback).second
			&& ((shortname == '\0')
				|| _shortoptions.emplace(shortname, callback).second);
	}

	private:
	int                                    _argc;
	char const**                           _argv;
	std::map<std::string_view, callback_t> _options;
	std::map<char, callback_t>             _shortoptions;
};

DA_END_NAMESPACE

#endif // _DA_CMDLINE_PARSER_HPP_
