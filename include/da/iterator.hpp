/**
 * @file      iterator.hpp
 * @brief     wrappers of iterators
 * @version   0.1
 * @author    dragon-archer (dragon-archer@outlook.com)
 *
 * @copyright Copyright (c) 2022
 */

#ifndef _LIBDA_ITERATOR_HPP_
#define _LIBDA_ITERATOR_HPP_

#include <da/config.hpp>
#include <compare>
#include <iterator>

DA_BEGIN_NAMESPACE

template<typename Iter, typename Container>
class normal_iterator {
	protected:
	Iter m_iter;
	template<typename It>
	using convertible_from = std::enable_if_t<std::is_convertible<It, Iter>::value>;

	typedef normal_iterator Self;

	public:
	typedef std::iterator_traits<Iter>            traits_type;
	typedef Iter                                  iterator_type;
	typedef std::random_access_iterator_tag       iterator_catagory;
	typedef typename traits_type::value_type      value_type;
	typedef typename traits_type::difference_type difference_type;
	typedef typename traits_type::reference       reference;
	typedef typename traits_type::pointer         pointer;

	constexpr normal_iterator() noexcept
		: m_iter(Iter()) { }

	explicit constexpr normal_iterator(const Iter& i) noexcept
		: m_iter(i) { }

	template<typename It, typename = convertible_from<It>>
	explicit constexpr normal_iterator(const It& i) noexcept
		: m_iter(i.base()) { }

	constexpr const Iter& base() const noexcept {
		return m_iter;
	}

	constexpr reference operator*() noexcept {
		return *m_iter;
	}

	constexpr pointer operator->() noexcept {
		return m_iter;
	}

	// Use comma expression to make this compile under C++11
	constexpr Self& operator++() noexcept {
		return (++m_iter, *this);
	}

	constexpr Self operator++(int) noexcept {
		return Self(m_iter++);
	}

	constexpr Self& operator--() noexcept {
		return (--m_iter, *this);
	}

	constexpr Self operator--(int) noexcept {
		return Self(m_iter--);
	}

	constexpr reference operator[](difference_type n) const {
		return m_iter[n];
	}

	constexpr Self& operator+=(difference_type n) {
		return (m_iter += n, *this);
	}

	constexpr Self operator+(difference_type n) const {
		return Self(m_iter + n);
	}

	constexpr Self& operator-=(difference_type n) {
		return (m_iter -= n, *this);
	}

	constexpr Self operator-(difference_type n) const {
		return Self(m_iter - n);
	}
};

template<typename Iter1, typename Iter2, typename Container>
constexpr bool operator==(const normal_iterator<Iter1, Container>& x,
						  const normal_iterator<Iter2, Container>& y) noexcept {
	return x.base() == y.base();
}

template<typename Iter1, typename Iter2, typename Container>
constexpr std::strong_ordering operator<=>(const normal_iterator<Iter1, Container>& x,
										   const normal_iterator<Iter2, Container>& y) noexcept {
	return x.base() <=> y.base();
}

/// Iterator concepts

using std::bidirectional_iterator;
using std::contiguous_iterator;
using std::forward_iterator;
using std::input_iterator;
using std::input_or_output_iterator;
using std::output_iterator;
using std::random_access_iterator;

DA_END_NAMESPACE

#endif // _LIBDA_ITERATOR_HPP_
