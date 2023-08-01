/* SPDX-License-Identifier: MIT */
/**
 * @file      singleton.hpp
 * @brief     Provide a base struct to make a singleton
 * @version   0.2
 * @author    dragon-archer
 *
 * @copyright Copyright (c) 2023 dragon-archer
 */

#ifndef _DA_UTILITY_SINGLETON_HPP_
#define _DA_UTILITY_SINGLETON_HPP_

#include <da/config.hpp>

DA_BEGIN_NAMESPACE

template<class T>
struct singleton {
	public:
	inline static T& get() {
		static T instance;
		return instance;
	}

	~singleton() = default;
	singleton(const singleton&) = delete;
	singleton& operator=(const singleton&) = delete;

	protected:
	singleton() = default;
};

DA_END_NAMESPACE

#endif // _DA_UTILITY_SINGLETON_HPP_
