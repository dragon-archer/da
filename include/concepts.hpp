#ifndef _LIBDA_CONCEPTS_HPP_
#define _LIBDA_CONCEPTS_HPP_

#include "config.hpp"
#include <concepts>

DA_BEGIN_NAMESPACE

using std::invocable;

template<typename Func, typename Ret, typename... Args>
concept invocable_r = std::is_invocable_r_v<Ret, Func, Args...>;

DA_END_NAMESPACE

#endif // _LIBDA_CONCEPTS_HPP_
