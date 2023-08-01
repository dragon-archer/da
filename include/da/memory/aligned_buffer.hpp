/* SPDX-License-Identifier: MIT */
/**
 * @file      aligned_buffer.hpp
 * @brief     A wrapper for aligned_buffer, like __gnu_cxx::aligned_buffer
 * @version   0.2
 * @author    dragon-archer
 *
 * @copyright Copyright (c) 2022-2023 dragon-archer
 */

#ifndef _DA_MEMORY_ALIGNED_BUFFER_HPP_
#define _DA_MEMORY_ALIGNED_BUFFER_HPP_

#include <da/config.hpp>

DA_BEGIN_NAMESPACE

template<typename T>
struct aligned_buffer {
	public:
	alignas(alignof(T)) unsigned char m_storage[sizeof(T)];

	aligned_buffer() = default;
	// Avoid value-initialization zeroing m_storage
	aligned_buffer(std::nullptr_t) { }

	inline void* addr() noexcept {
		return static_cast<void*>(&m_storage);
	}
	inline const void* addr() const noexcept {
		return static_cast<const void*>(&m_storage);
	}
	inline T* ptr() noexcept {
		return static_cast<T*>(&m_storage);
	}
	inline const T* ptr() const noexcept {
		return static_cast<const T*>(&m_storage);
	}
};

DA_END_NAMESPACE

#endif // _DA_MEMORY_ALIGNED_BUFFER_HPP_
