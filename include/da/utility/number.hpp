/* SPDX-License-Identifier: MIT */
/**
 * @file      number.hpp
 * @brief     Some fast number classes
 * @version   0.1
 * @author    dragon-archer (dragon-archer@outlook.com)
 *
 * @copyright Copyright (c) 2022-2023 dragon-archer
 */

#ifndef _DA_NUMBER_HPP_
#define _DA_NUMBER_HPP_

#include <da/config.hpp>
#include <da/type_traits/config.hpp>
#include <da/concepts.hpp>
#include <da/utility/math.hpp>

DA_BEGIN_NAMESPACE

// Used to mark no conversion in constructor
struct no_conversion_t { };
inline constexpr no_conversion_t no_conversion;

template<size_t Precision, arithmetic Base = int64_t>
class fixed_point;

template<size_t Precision, arithmetic Base>
class fixed_point {
	static_assert(!std::is_same_v<Base, bool>, "bool is not supported to be base of fixed_point");
	// Use an approximate log, treat 1000 as 1024
	static_assert(Precision < sizeof(Base) * 8 * 0.3, "The Precision is too high for the Base type.");

	Base _value;

	public:
	static constexpr Base precision_in_10 = pow<Base>(10, Precision);

	/// Constructors
	constexpr fixed_point() noexcept
		: _value() { }

	template<arithmetic T>
	constexpr fixed_point(T value) noexcept
		: _value(value * precision_in_10) { }

	template<arithmetic T>
	constexpr fixed_point(T value, no_conversion_t) noexcept
		: _value(value) { }

	template<size_t P2, arithmetic B2>
	constexpr fixed_point(fixed_point<P2, B2> other) noexcept
		: _value(other.raw() * precision_in_10 / other.precision_in_10) { }

	/// getter & setter
	template<arithmetic T>
	[[nodiscard]] constexpr T get() const noexcept {
		return static_cast<T>(_value) / precision_in_10;
	}

	template<arithmetic T>
	[[nodiscard]] constexpr operator T() const noexcept {
		return get<T>();
	}

	template<arithmetic T>
	constexpr fixed_point& set(T v) noexcept {
		_value = v * precision_in_10;
		return *this;
	}

	[[nodiscard]] constexpr Base raw() const noexcept {
		return _value;
	}

	[[nodiscard]] constexpr Base& raw() noexcept {
		return _value;
	}

	[[nodiscard]] static constexpr fixed_point from_raw(Base value) noexcept {
		return {value, no_conversion};
	}

	/// Misc
	[[nodiscard]] constexpr bool is_integer() noexcept {
		return _value % precision_in_10 == 0;
	}

	/// Basic operations
	[[nodiscard]] constexpr fixed_point add(fixed_point other) const noexcept {
		return from_raw(_value + other._value);
	}

	template<arithmetic T>
	[[nodiscard]] constexpr fixed_point add(T other) const noexcept {
		return from_raw(_value + other * precision_in_10);
	}

	[[nodiscard]] constexpr fixed_point subtract(fixed_point other) const noexcept {
		return from_raw(_value - other._value);
	}

	template<arithmetic T>
	[[nodiscard]] constexpr fixed_point subtract(T other) const noexcept {
		return from_raw(_value - other * precision_in_10);
	}

	[[nodiscard]] constexpr fixed_point multiply(fixed_point other) const noexcept {
		return from_raw(_value * other._value / precision_in_10);
	}

	template<arithmetic T>
	[[nodiscard]] constexpr fixed_point multiply(T other) const noexcept {
		return from_raw(_value * other);
	}

	[[nodiscard]] constexpr fixed_point divide(fixed_point other) const noexcept {
		return from_raw(_value * precision_in_10 / other._value);
	}

	template<arithmetic T>
	[[nodiscard]] constexpr fixed_point divide(T other) const noexcept {
		return from_raw(_value / other);
	}

	/// Operators
	[[nodiscard]] constexpr fixed_point operator-() const noexcept {
		return from_raw(-_value);
	}

	constexpr fixed_point& operator+=(fixed_point other) noexcept {
		_value += other._value;
		return *this;
	}

	template<arithmetic T>
	constexpr fixed_point& operator+=(T other) noexcept {
		_value += other * precision_in_10;
		return *this;
	}

	constexpr fixed_point& operator-=(fixed_point other) noexcept {
		_value -= other._value;
		return *this;
	}

	template<arithmetic T>
	constexpr fixed_point& operator-=(T other) noexcept {
		_value -= other * precision_in_10;
		return *this;
	}

	constexpr fixed_point& operator*=(fixed_point other) noexcept {
		_value = _value * other._value / precision_in_10;
		return *this;
	}

	template<arithmetic T>
	constexpr fixed_point& operator*=(T other) noexcept {
		_value = _value * other;
		return *this;
	}

	constexpr fixed_point& operator/=(fixed_point other) noexcept {
		_value = _value * precision_in_10 / other._value;
		return *this;
	}

	template<arithmetic T>
	constexpr fixed_point& operator/=(T other) noexcept {
		_value /= other;
		return *this;
	}
};

template<size_t P, arithmetic B>
[[nodiscard]] constexpr fixed_point<P, B> operator+(fixed_point<P, B> x, fixed_point<P, B> y) noexcept {
	return x.add(y);
}

template<size_t P, arithmetic B, arithmetic T>
[[nodiscard]] constexpr fixed_point<P, B> operator+(fixed_point<P, B> x, T y) noexcept {
	return x.add(y);
}

template<size_t P, arithmetic B, arithmetic T>
[[nodiscard]] constexpr fixed_point<P, B> operator+(T x, fixed_point<P, B> y) noexcept {
	return y.add(x);
}

template<size_t P, arithmetic B>
[[nodiscard]] constexpr fixed_point<P, B> operator-(fixed_point<P, B> x, fixed_point<P, B> y) noexcept {
	return x.subtract(y);
}

template<size_t P, arithmetic B, arithmetic T>
[[nodiscard]] constexpr fixed_point<P, B> operator-(fixed_point<P, B> x, T y) noexcept {
	return x.subtract(y);
}

template<size_t P, arithmetic B, arithmetic T>
[[nodiscard]] constexpr fixed_point<P, B> operator-(T x, fixed_point<P, B> y) noexcept {
	return fixed_point<P, B>(x).subtract(y);
}

template<size_t P, arithmetic B>
[[nodiscard]] constexpr fixed_point<P, B> operator*(fixed_point<P, B> x, fixed_point<P, B> y) noexcept {
	return x.multiply(y);
}

template<size_t P, arithmetic B, arithmetic T>
[[nodiscard]] constexpr fixed_point<P, B> operator*(fixed_point<P, B> x, T y) noexcept {
	return x.multiply(y);
}

template<size_t P, arithmetic B, arithmetic T>
[[nodiscard]] constexpr fixed_point<P, B> operator*(T x, fixed_point<P, B> y) noexcept {
	return y.multiply(x);
}

template<size_t P, arithmetic B>
[[nodiscard]] constexpr fixed_point<P, B> operator/(fixed_point<P, B> x, fixed_point<P, B> y) noexcept {
	return x.divide(y);
}

template<size_t P, arithmetic B, arithmetic T>
[[nodiscard]] constexpr fixed_point<P, B> operator/(fixed_point<P, B> x, T y) noexcept {
	return x.divide(y);
}

template<size_t P, arithmetic B, arithmetic T>
[[nodiscard]] constexpr fixed_point<P, B> operator/(T x, fixed_point<P, B> y) noexcept {
	return fixed_point<P, B>(x).divide(y);
}

DA_END_NAMESPACE

#endif // _DA_NUMBER_HPP_
