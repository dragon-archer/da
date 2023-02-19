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
#include <string_view>

DA_BEGIN_NAMESPACE

class cmdline_parser {
	public:
	constexpr uint32_t flags() {
		return _flags;
	}

	constexpr bool enabled(uint32_t flag) {
		return (_flags & flag) == flag;
	}

	constexpr void enable(uint32_t flag) {
		_flags |= flag;
	}

	constexpr void disable(uint32_t flag) {
		_flags &= ~flag;
	}

	private:
	uint32_t _flags;
};

DA_END_NAMESPACE

#endif // _DA_CMDLINE_PARSER_HPP_
