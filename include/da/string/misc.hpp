/* SPDX-License-Identifier: MIT */
/**
 * @file      misc.hpp
 * @brief     Misc
 * @version   0.2
 * @author    dragon-archer
 *
 * @copyright Copyright (c) 2023 dragon-archer
 */

#ifndef _DA_STRING_MISC_HPP_
#define _DA_STRING_MISC_HPP_

#include <da/config.hpp>

DA_BEGIN_NAMESPACE

DA_CONSTEXPR size_t strlen(const char* str) noexcept {
	DA_ASSUME(str != nullptr);
	size_t ret = 0;
	while(*str != '\0') {
		++ret;
		++str;
	}
	return ret;
}

DA_END_NAMESPACE

#endif // _DA_STRING_MISC_HPP_
