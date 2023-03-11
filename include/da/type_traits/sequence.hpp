/* SPDX-License-Identifier: MIT */
/**
 * @file      sequence.hpp
 * @brief     Make advanced index sequence
 * @version   0.1
 * @author    dragon-archer
 *
 * @copyright Copyright (c) 2023 dragon-archer
 */

#ifndef _DA_TYPE_TRAITS_SEQUENCE_HPP_
#define _DA_TYPE_TRAITS_SEQUENCE_HPP_

#include <da/type_traits/config.hpp>

DA_BEGIN_DETAIL

template<size_t Start, ssize_t Step, size_t... Ns>
inline constexpr auto make_sequence_helper(std::index_sequence<Ns...> = {}) noexcept {
	return std::index_sequence<(Start + Step * Ns)...>{};
}

DA_END_DETAIL

DA_BEGIN_NAMESPACE

/**
 * @brief Make a index sequence with (Start, Stop, Step)
 */
template<size_t Start, size_t Stop, ssize_t Step>
	requires(Step != 0) && ((Stop - Start) / Step >= 0)
inline constexpr auto make_sequence() noexcept {
	constexpr size_t  count = (Step > 0) ? ((Stop - Start + Step - 1) / Step)
										 : (ssize_t(Stop - Start + Step + 1) / Step);
	return _DA_DETAIL make_sequence_helper<Start, Step>(std::make_index_sequence<count>{});
}

/**
 * @brief Make a index sequence with (Start, Stop, 1)
 */
template<size_t Start, size_t Stop>
	requires(Start <= Stop)
inline constexpr auto make_sequence() {
	return make_sequence<Start, Stop, 1>();
}

/**
 * @brief Make a index sequence with (0, Stop, 1)
 */
template<size_t Stop>
	requires(Stop >= 0)
inline constexpr auto make_sequence() {
	return make_sequence<0, Stop, 1>();
}

DA_END_NAMESPACE

#endif // _DA_TYPE_TRAITS_SEQUENCE_HPP_
