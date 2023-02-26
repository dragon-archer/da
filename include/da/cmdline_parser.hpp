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
	using handle_t   = int;
	using string_t   = std::string_view;
	using callback_t = std::function<void(string_t)>;

	static constexpr handle_t invalid_handle = 0;

	enum error_code {
		SUCCESS = 0,
		MISSING_ARGUMENT,
		MISSING_OPTION,
		UNEXPECTED_ARGUMENT,
		UNEXPECTED_END,
		UNKNOWN_OPTION,
		_MAX_ERROR_CODE
	};

	cmdline_parser()
		: _max_handle(0) { }

	handle_t add_option(string_t name, callback_t const& callback) {
		return add_option(name, '\0', callback);
	}

	handle_t add_option(string_t name, char shortname, callback_t const& callback) {
		DA_IFUNLIKELY(name.empty()) {
			return invalid_handle;
		}
		++_max_handle;
		auto const [it1, ok1] = _options.try_emplace(name, _max_handle);
		DA_IFLIKELY(ok1) {
			do {
				if(shortname != '\0') {
					auto const [it2, ok2] = _shortoptions.try_emplace(shortname, _max_handle);
					DA_IFUNLIKELY(!ok2) {
						break;
					}
				}
				auto const [it3, ok3] = _records.try_emplace(_max_handle, callback);
				DA_ASSUME(ok3);
				return _max_handle;
			} while(false);
			// Revert actions starts here
			_options.erase(it1);
		}
		--_max_handle;
		return invalid_handle;
	}

	handle_t get_handle(string_t name) const {
		auto const it = _options.find(name);
		DA_IFUNLIKELY(it == _options.cend()) {
			return invalid_handle;
		}
		return it->second;
	}

	handle_t get_handle(char shortname) const {
		auto const it = _shortoptions.find(shortname);
		DA_IFUNLIKELY(it == _shortoptions.cend()) {
			return invalid_handle;
		}
		return it->second;
	}

	error_code parse(int argc, char const** argv) {
		DA_IFUNLIKELY(argc == 0 || argv == nullptr) {
			return UNEXPECTED_END;
		}
		for(int i = 1; i < argc; ++i) {
			auto p = argv[i];
			DA_IFUNLIKELY(p == nullptr) {
				return UNEXPECTED_END;
			}
			DA_IFUNLIKELY(*p == '\0') {
				continue;
			}
			DA_IFLIKELY(*p == '-') {
				++p;
				if(*p == '-') { // Long option
					++p;
					DA_IFUNLIKELY(*p == '\0') {
						return MISSING_OPTION;
					}
					string_t   s{p};
					auto const it = s.find('=');
					DA_IFUNLIKELY(it == string_t::npos) {
						return MISSING_ARGUMENT;
					}
					auto const it2 = _options.find(s.substr(0, it));
					DA_IFUNLIKELY(it2 == _options.end()) {
						return UNKNOWN_OPTION;
					}
					auto const it3 = _records.find(it2->second);
					DA_ASSUME(it3 != _records.end());
					it3->second(s.substr(it + 1));
				} else { // Short option
					DA_IFUNLIKELY(*p == '\0') {
						return MISSING_OPTION;
					}
					auto const it = _shortoptions.find(*p);
					DA_IFUNLIKELY(it == _shortoptions.end()) {
						return UNKNOWN_OPTION;
					}
					auto const it2 = _records.find(it->second);
					DA_ASSUME(it2 != _records.end());
					++p;
					DA_IFUNLIKELY(*p == '\0') {
						return MISSING_ARGUMENT;
					}
					it2->second(string_t{p});
				}
			} else {
				return UNEXPECTED_ARGUMENT;
			}
		}
		return SUCCESS;
	}

	private:
	handle_t                       _max_handle;
	std::map<handle_t, callback_t> _records;
	std::map<string_t, handle_t>   _options;
	std::map<char, handle_t>       _shortoptions;
};

DA_END_NAMESPACE

#endif // _DA_CMDLINE_PARSER_HPP_
