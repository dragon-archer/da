/**
 * @file      aligned_buffer.hpp
 * @brief     A wrapper for aligned_buffer, like __gnu_cxx::aligned_buffer
 * @version   0.1
 * @author    dragon-archer (dragon-archer@outlook.com)
 *
 * @copyright Copyright (c) 2022
 */

#ifndef _LIBDA_MEMORY_ALIGNED_BUFFER_HPP_
#define _LIBDA_MEMORY_ALIGNED_BUFFER_HPP_

#include "../config.hpp"

namespace da {
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
}

#endif // _LIBDA_MEMORY_ALIGNED_BUFFER_HPP_
