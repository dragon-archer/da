/* SPDX-License-Identifier: MIT */
/**
 * @file      config.hpp
 * @brief     Config for script
 * @version   0.1
 * @author    dragon-archer
 *
 * @copyright Copyright (c) 2023 dragon-archer
 */

#ifndef _DA_SCRIPT_CONFIG_HPP_
#define _DA_SCRIPT_CONFIG_HPP_

#include <da/config.hpp>
#include <cstring>
#include <string_view>

#define DA_BEGIN_SCRIPT \
	DA_BEGIN_NAMESPACE  \
	namespace script {
#define DA_END_SCRIPT \
	}                 \
	DA_END_NAMESPACE

#endif // _DA_SCRIPT_CONFIG_HPP_
