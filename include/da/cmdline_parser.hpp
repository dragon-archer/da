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
	using handle_t   = int;

	static constexpr handle_t invalid_handle = 0;

	cmdline_parser()
		: _max_handle(0) { }

	handle_t add_option(std::string_view name, callback_t const& callback) {
		return add_option(name, '\0', callback);
	}

	handle_t add_option(std::string_view name, char shortname, callback_t const& callback) {
		DA_IFUNLIKELY(name.empty()) {
			return invalid_handle;
		}
		++_max_handle;
		const auto& [it1, ok1] = _options.try_emplace(name, _max_handle);
		DA_IFLIKELY(ok1) {
			do {
				if(shortname != '\0') {
					const auto& [it2, ok2] = _shortoptions.try_emplace(shortname, _max_handle);
					DA_IFUNLIKELY(!ok2) {
						break;
					}
				}
				const auto& [it3, ok3] = _records.try_emplace(_max_handle, callback);
				DA_ASSUME(ok3);
				return _max_handle;
			} while(false);
			// Revert actions starts here
			_options.erase(it1);
		}
		--_max_handle;
		return invalid_handle;
	}

	private:
	handle_t                             _max_handle;
	std::map<handle_t, callback_t>       _records;
	std::map<std::string_view, handle_t> _options;
	std::map<char, handle_t>             _shortoptions;
};

DA_END_NAMESPACE

#endif // _DA_CMDLINE_PARSER_HPP_
