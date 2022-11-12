/**
 * @file      string.hpp
 * @brief     interface of string
 * @version   0.1
 * @author    dragon-archer (dragon-archer@outlook.com)
 *
 * @copyright Copyright (c) 2022
 */

#ifndef _DA_STRING_HPP_
#define _DA_STRING_HPP_

#include "config.hpp"
#include "string/string_fwd.hpp"
#include "string/normal_string.hpp"
#include "string/sso_string.hpp"
#include "type_traits.hpp"

DA_BEGIN_NAMESPACE

template<typename Char, typename Traits, typename Alloc,
		 template<typename, typename, typename> typename StringImpl>
class string_base : protected StringImpl<Char, Traits, Alloc> { // Not public inherit to wrap the interface
private:
	typedef StringImpl<Char, Traits, Alloc>				 Impl;
	typedef string_base<Char, Traits, Alloc, StringImpl> Self;

public:
	typedef typename Impl::value_type			  value_type;
	typedef typename Impl::traits_type			  traits_type;
	typedef typename Impl::allocator_type		  allocator_type;
	typedef typename Impl::alloc_traits			  alloc_traits;
	typedef typename Impl::pointer				  pointer;
	typedef typename Impl::const_pointer		  const_pointer;
	typedef typename Impl::reference			  reference;
	typedef typename Impl::const_reference		  const_reference;
	typedef typename Impl::iterator				  iterator;
	typedef typename Impl::const_iterator		  const_iterator;
	typedef typename Impl::reverse_iterator		  reverse_iterator;
	typedef typename Impl::const_reverse_iterator const_reverse_iterator;
	typedef typename Impl::size_type			  size_type;
	typedef typename Impl::difference_type		  difference_type;

	static constexpr size_type npos			  = Impl::npos;
	static constexpr size_type start_capacity = 16; // Capacity should be no less than this

private: // Declare feature test structures
	/**
	 * @brief Naming rule:
	 *        1. Start with has_, followed by the function name
	 *        2. Connect with each parameter's mangled name by underline
	 *        Mangling rule:
	 *        1. Use one letter for basic class:
	 *        - i = size_type, p = pointer, v = value_type, s = string_base, w = const char*, t = iterator
	 *        2. Add descriptor after it if exists
	 *        - r = left reference, R = right reference, c = const, l = std::initializer_list
	 */
	DA_DECLARE_MEMBER_FUNCTION_TEST(has_destructor, ~Impl)

	DA_DECLARE_MEMBER_FUNCTION_TEST(has__M_get_alloc, _M_get_alloc)
	DA_DECLARE_MEMBER_FUNCTION_TEST(has__M_allocate_i, _M_allocate, size_type)
	DA_DECLARE_MEMBER_FUNCTION_TEST(has__M_deallocate_p_i, _M_deallocate, pointer, size_type)
	DA_DECLARE_MEMBER_FUNCTION_TEST(has__S_copy_p_pc_i, _S_copy, pointer, const_pointer, size_type)
	DA_DECLARE_MEMBER_FUNCTION_TEST(has__S_copy_backward_p_pc_i, _S_copy_backward, pointer, const_pointer, size_type)
	DA_DECLARE_MEMBER_FUNCTION_TEST(has__S_assign_vr_vcr, _S_assign, reference, const_reference)
	DA_DECLARE_MEMBER_FUNCTION_TEST(has__S_assign_p_i_v, _S_assign, pointer, size_type, value_type)
	DA_DECLARE_MEMBER_FUNCTION_TEST(has__S_length_pc, _S_length, const_pointer)

	DA_DECLARE_MEMBER_FUNCTION_TEST(has__M_data_p, _M_data, pointer)
	DA_DECLARE_MEMBER_FUNCTION_TEST(has__M_size_i, _M_size, size_type)
	DA_DECLARE_MEMBER_FUNCTION_TEST(has__M_capacity_i, _M_capacity, size_type)
	DA_DECLARE_MEMBER_FUNCTION_TEST(has__M_create_ir_i, _M_create, size_type&, size_type)
	DA_DECLARE_MEMBER_FUNCTION_TEST(has__M_check_length_i_i_w, _M_check_length, size_type, size_type, const char*)
	DA_DECLARE_MEMBER_FUNCTION_TEST(has__M_check_pos_i_w, _M_check_pos, size_type, const char*)
	DA_DECLARE_MEMBER_FUNCTION_TEST(has__M_dispose, _M_dispose)
	DA_DECLARE_MEMBER_FUNCTION_TEST(has__M_destroy_i, _M_destroy)
	DA_DECLARE_MEMBER_FUNCTION_TEST(has__M_limit_length_i_i, _M_limit_length, size_type, size_type)

	DA_DECLARE_MEMBER_FUNCTION_TEST(has_data, data)
	DA_DECLARE_MEMBER_FUNCTION_TEST(has_size, size)
	DA_DECLARE_MEMBER_FUNCTION_TEST(has_capacity, capacity)
	DA_DECLARE_MEMBER_FUNCTION_TEST(has_max_size, max_size)
	DA_DECLARE_MEMBER_FUNCTION_TEST(has_length, length)

	DA_DECLARE_MEMBER_FUNCTION_TEST(has_begin, begin)
	DA_DECLARE_MEMBER_FUNCTION_TEST(has_end, end)
	DA_DECLARE_MEMBER_FUNCTION_TEST(has_rbegin, rbegin)
	DA_DECLARE_MEMBER_FUNCTION_TEST(has_rend, rend)
	DA_DECLARE_MEMBER_FUNCTION_TEST(has_cbegin, cbegin)
	DA_DECLARE_MEMBER_FUNCTION_TEST(has_cend, cend)
	DA_DECLARE_MEMBER_FUNCTION_TEST(has_crbegin, crbegin)
	DA_DECLARE_MEMBER_FUNCTION_TEST(has_crend, crend)

	DA_DECLARE_MEMBER_FUNCTION_TEST(has_reserve, reserve)
	DA_DECLARE_MEMBER_FUNCTION_TEST(has_reserve_i, reserve, size_type)
	DA_DECLARE_MEMBER_FUNCTION_TEST(has_shrink_to_fit, shrink_to_fit)
	DA_DECLARE_MEMBER_FUNCTION_TEST(has_clear, clear)
	DA_DECLARE_MEMBER_FUNCTION_TEST(has_empty, empty)

	DA_DECLARE_MEMBER_FUNCTION_TEST(has_operator_square_i, operator[], size_type)
	DA_DECLARE_MEMBER_FUNCTION_TEST(has_at_i, at, size_type)
	DA_DECLARE_MEMBER_FUNCTION_TEST(has_front, front)
	DA_DECLARE_MEMBER_FUNCTION_TEST(has_back, back)

	DA_DECLARE_MEMBER_FUNCTION_TEST(has_replace_i_i_pc_i, replace, size_type, size_type, const_pointer, size_type)
	DA_DECLARE_MEMBER_FUNCTION_TEST(has_replace_i_i_i_v, replace, size_type, size_type, size_type, value_type)
	DA_DECLARE_MEMBER_FUNCTION_TEST(has_replace_i_i_pc, replace, size_type, size_type, const_pointer)
	DA_DECLARE_MEMBER_FUNCTION_TEST(has_replace_i_i_scr, replace, size_type, size_type, const Self&)
	DA_DECLARE_MEMBER_FUNCTION_TEST(has_replace_i_i_scr_i_i, replace, size_type, size_type, const Self&, size_type, size_type)
	DA_DECLARE_MEMBER_FUNCTION_TEST(has_replace_tc_tc_pc_i, replace, const_iterator, const_iterator, const_pointer, size_type)
	DA_DECLARE_MEMBER_FUNCTION_TEST(has_replace_tc_tc_i_v, replace, const_iterator, const_iterator, size_type, value_type)
	DA_DECLARE_MEMBER_FUNCTION_TEST(has_replace_tc_tc_pc, replace, const_iterator, const_iterator, const_pointer)
	DA_DECLARE_MEMBER_FUNCTION_TEST(has_replace_tc_tc_scr, replace, const_iterator, const_iterator, const Self&)
	DA_DECLARE_MEMBER_FUNCTION_TEST(has_replace_tc_tc_p_p, replace, const_iterator, const_iterator, const_pointer, const_pointer)
	DA_DECLARE_MEMBER_FUNCTION_TEST(has_replace_tc_tc_pc_pc, replace, const_iterator, const_iterator, pointer, pointer)
	DA_DECLARE_MEMBER_FUNCTION_TEST(has_replace_tc_tc_t_t, replace, const_iterator, const_iterator, iterator, iterator)
	DA_DECLARE_MEMBER_FUNCTION_TEST(has_replace_tc_tc_tc_tc, replace, const_iterator, const_iterator, const_iterator, const_iterator)
	DA_DECLARE_MEMBER_FUNCTION_TEST(has_replace_tc_tc_vl, replace, const_iterator, const_iterator, std::initializer_list<value_type>)

	DA_DECLARE_MEMBER_FUNCTION_TEST(has_append_pc_i, append, const_pointer, size_type)
	DA_DECLARE_MEMBER_FUNCTION_TEST(has_append_pc, append, const_pointer)
	DA_DECLARE_MEMBER_FUNCTION_TEST(has_append_scr, append, const Self&)
	DA_DECLARE_MEMBER_FUNCTION_TEST(has_append_scr_i_i, append, const Self&, size_type, size_type)
	DA_DECLARE_MEMBER_FUNCTION_TEST(has_append_vl, append, std::initializer_list<value_type>)
	DA_DECLARE_MEMBER_FUNCTION_TEST(has_append_i_v, append, size_type, value_type)
	DA_DECLARE_MEMBER_FUNCTION_TEST(has_push_back_v, push_back, value_type)
	DA_DECLARE_MEMBER_FUNCTION_TEST(has_operator_plusequal_pc, operator+=, const_pointer)
	DA_DECLARE_MEMBER_FUNCTION_TEST(has_operator_plusequal_scr, operator+=, const Self&)
	DA_DECLARE_MEMBER_FUNCTION_TEST(has_operator_plusequal_v, operator+=, value_type)
	DA_DECLARE_MEMBER_FUNCTION_TEST(has_operator_plusequal_vl, operator+=, std::initializer_list<value_type>)

	DA_DECLARE_MEMBER_FUNCTION_TEST(has_assign_pc_i, assign, const_pointer, size_type)
	DA_DECLARE_MEMBER_FUNCTION_TEST(has_assign_sR, assign, Self&&)
	DA_DECLARE_MEMBER_FUNCTION_TEST(has_assign_pc, assign, const_pointer)
	DA_DECLARE_MEMBER_FUNCTION_TEST(has_assign_scr, assign, const Self&)
	DA_DECLARE_MEMBER_FUNCTION_TEST(has_assign_scr_i_i, assign, const Self&, size_type, size_type)
	DA_DECLARE_MEMBER_FUNCTION_TEST(has_assign_vl, assign, std::initializer_list<value_type>)
	DA_DECLARE_MEMBER_FUNCTION_TEST(has_assign_i_v, assign, size_type, value_type)
	DA_DECLARE_MEMBER_FUNCTION_TEST(has_operator_equal_sR, operator+=, Self&&)
	DA_DECLARE_MEMBER_FUNCTION_TEST(has_operator_equal_pc, operator+=, const_pointer)
	DA_DECLARE_MEMBER_FUNCTION_TEST(has_operator_equal_scr, operator+=, const Self&)
	DA_DECLARE_MEMBER_FUNCTION_TEST(has_operator_equal_v, operator+=, value_type)

	DA_DECLARE_MEMBER_FUNCTION_TEST(has_swap_scr, swap, const Self&)

public: // Constructors
	constexpr string_base() noexcept {
		size_type c = start_capacity;
		_M_data(_M_create(c, 0));
		_M_capacity(c);
		_M_size(0);
	}

	constexpr string_base(const_pointer s, size_type n) {
		size_type c = n;
		_M_data(_M_create(c, 0));
		_M_capacity(c);
		_S_copy(data(), s, n);
		_M_size(n);
	}

	constexpr string_base(size_type n, value_type v) {
		size_type c = n;
		_M_data(_M_create(c, 0));
		_M_capacity(c);
		_S_assign(data(), n, v);
		_M_size(n);
	}

	constexpr string_base(Self&& s) {
		swap(move(s));
	}

	template<forward_iterator Iter>
	constexpr string_base(Iter it1, Iter it2) {
		// TODO: Optimize this to avoid access two times, thus we can accept input iterator
		const size_type n = std::distance(it1, it2);
		size_type		c = n;
		_M_data(_M_create(c, 0));
		_M_capacity(c);
		_S_copy(data(), it1, n);
		_M_size(n);
	}

	constexpr string_base(const_pointer s)
		: string_base(s, _S_length(s)) { }

	constexpr string_base(const Self& s)
		: string_base(s.data(), s.size()) { }

	constexpr string_base(const Self& s, size_type pos)
		: string_base(s.data() + s._M_check_pos(pos, "da::string_base::string_base"), s._M_limit_length(pos, npos)) { }

	constexpr string_base(const Self& s, size_type pos, size_type n)
		: string_base(s.data() + s._M_check_pos(pos, "da::string_base::string_base"), s._M_limit_length(pos, n)) { }

	constexpr string_base(std::initializer_list<value_type> il)
		: string_base(il.begin(), il.size()) { }

	constexpr ~string_base() {
		if constexpr(has_destructor_v<Impl>) {
			Impl::~Impl();
			return;
		}
		_M_dispose();
	}

protected: // Traits-oriented
	constexpr allocator_type& _M_get_alloc() const noexcept {
		if constexpr(has__M_get_alloc_v<const Impl>) {
			return Impl::_M_get_alloc();
		}
		static_assert(has__M_get_alloc_v<Impl>, "The implemention of string should provide `allocator_type& _M_get_alloc()` as interface.");
	}

	constexpr pointer _M_allocate(size_type n) {
		if constexpr(has__M_allocate_i_v<Impl>) {
			return Impl::_M_allocate(n);
		}
		assert(n != 0);
		return alloc_traits::allocate(_M_get_alloc(), n);
	}

	constexpr void _M_deallocate(pointer p, size_type n) {
		if constexpr(has__M_deallocate_p_i_v<Impl>) {
			Impl::_M_deallocate(p, n);
			return;
		}
		assert(p != nullptr && n != 0);
		alloc_traits::deallocate(_M_get_alloc(), p, n);
	}

	static constexpr pointer _S_copy(pointer dest, const_pointer src, size_type n) noexcept {
		if constexpr(has__S_copy_p_pc_i_v<Impl>) {
			return Impl::_S_copy(dest, src, n);
		}
		DA_IFUNLIKELY(n == 0) {
			return dest;
		}
		DA_IFUNLIKELY(n == 1) {
			_S_assign(*dest, *src);
			return dest;
		}
		return traits_type::copy(dest, src, n);
	}

	static constexpr pointer _S_copy_backward(pointer dest, const_pointer src, size_type n) noexcept {
		if constexpr(has__S_copy_backward_p_pc_i_v<Impl>) {
			return Impl::_S_copy_backward(dest, src, n);
		}
		DA_IFUNLIKELY(n == 0) {
			return dest;
		}
		DA_IFUNLIKELY(n == 1) {
			_S_assign(*dest, *src);
			return dest;
		}
		return std::copy_backward(src, src + n, dest);
	}

	static constexpr void _S_assign(reference dest, const_reference src) noexcept {
		if constexpr(has__S_assign_vr_vcr_v<Impl>) {
			Impl::_S_assign(dest, src);
			return;
		}
		traits_type::assign(dest, src);
	}

	static constexpr pointer _S_assign(pointer dest, size_type n, value_type src) noexcept {
		if constexpr(has__S_assign_p_i_v_v<Impl>) {
			return Impl::_S_assign(dest, n, src);
		}
		DA_IFUNLIKELY(n == 0) {
			return dest;
		}
		DA_IFUNLIKELY(n == 1) {
			_S_assign(*dest, src);
			return dest;
		}
		return traits_type::assign(dest, n, src);
	}

	static constexpr size_type _S_length(const_pointer p) noexcept {
		if constexpr(has__S_length_pc_v<Impl>) {
			return Impl::_S_length(p);
		}
		return traits_type::length(p);
	}

protected: // Internal functions
	constexpr void _M_data(pointer p) noexcept {
		if constexpr(has__M_data_p_v<Impl>) {
			Impl::_M_data(p);
			return;
		}
		static_assert(has__M_data_p_v<Impl>, "The implemention of string should provide `void _M_data(pointer)` as interface.");
	}

	constexpr void _M_size(size_type n) noexcept {
		if constexpr(has__M_size_i_v<Impl>) {
			Impl::_M_size(n);
			return;
		}
		static_assert(has__M_size_i_v<Impl>, "The implemention of string should provide `void _M_size(size_type)` as interface.");
	}

	constexpr void _M_capacity(size_type n) noexcept {
		if constexpr(has__M_capacity_i_v<Impl>) {
			Impl::_M_capacity(n);
			return;
		}
		static_assert(has__M_capacity_i_v<Impl>, "The implemention of string should provide `void _M_capacity(size_type)` as interface.");
	}

	constexpr pointer _M_create(size_type& new_capacity, size_type old_capacity) {
		if constexpr(has__M_create_ir_i_v<Impl>) {
			return Impl::_M_create(new_capacity, old_capacity);
		}
		DA_IFUNLIKELY(new_capacity > max_size()) {
			DA_THROW(std::length_error(fmt::format("da::string_base::_M_create: The new capacity (which is {}) > max_size() (which is {})", new_capacity, max_size())));
		}
		if(new_capacity > old_capacity && new_capacity < 2 * old_capacity) {
			new_capacity = 2 * old_capacity;
			if(new_capacity > max_size()) {
				new_capacity = max_size();
			}
		}
		return _M_allocate(new_capacity + 1); // One more element for '\0'
	}

	/**
	 * @brief Check whether it is safe to replace a string with length n1 to another string with length n2
	 * @param n1   The origin string's length
	 * @param n2   The replace string's length
	 * @param what If errors, the string to be throw
	 */
	constexpr void _M_check_length(size_type n1, size_type n2, const char* what = "da::string_base::_M_check_length") const {
		if constexpr(has__M_check_length_i_i_w_v<Impl>) {
			Impl::_M_check_length(n1, n2, what);
			return;
		}
		DA_IFUNLIKELY(max_size() - (size() - n1) < n2) {
			DA_THROW(std::length_error(fmt::format("{}: the size after operation (which is {}) > max_size (which is {})", what, size() - n1 + n2, max_size())));
		}
	}

	/**
	 * @brief  Check whether the position is inside the string
	 * @param  p    The position to check
	 * @param  what If errors, the string to be throw
	 * @return @param p
	 * @note   Access to the '\0' letter is allowed here
	 */
	constexpr size_type _M_check_pos(size_type p, const char* what) const {
		if constexpr(has__M_check_pos_i_w_v<Impl>) {
			return Impl::_M_check_pos(p, what);
		}
		DA_IFUNLIKELY(p > size()) {
			DA_THROW(std::out_of_range(fmt::format("{}: the position (which is {}) > size (which is {})", what, p, size())));
		}
		return p;
	}

	constexpr void _M_dispose() {
		if constexpr(has__M_dispose_v<Impl>) {
			Impl::_M_dispose();
			return;
		}
		_M_destroy(capacity());
	}

	constexpr void _M_destroy(size_type n) {
		if constexpr(has__M_destroy_i_v<Impl>) {
			Impl::_M_destroy(n);
			return;
		}
		DA_IFUNLIKELY(data() == nullptr) {
			return;
		}
		_M_deallocate(data(), n + 1);
	}

	/**
	 * @brief  Check whether the offset is ok
	 * @param  pos    The position start
	 * @param  offset The offset
	 * @return The max accepted offset
	 * @note   This function DO NOT check the pos
	 */
	constexpr size_type _M_limit_length(size_type pos, size_type offset) const noexcept {
		if constexpr(has__M_limit_length_i_i_v<Impl>) {
			return Impl::_M_limit_length(pos, offset);
		}
		bool ok = offset < (size() - pos);
		return ok ? offset : (size() - pos);
	}

public: // Basic operations
	constexpr pointer data() const noexcept {
		if constexpr(has_data_v<const Impl>) {
			return Impl::data();
		}
		static_assert(has_data_v<const Impl>, "The implemention of string should provide `pointer data() const` as interface.");
	}

	constexpr size_type size() const noexcept {
		if constexpr(has_size_v<const Impl>) {
			return Impl::size();
		}
		static_assert(has_size_v<const Impl>, "The implemention of string should provide `size_type size() const` as interface.");
	}

	constexpr size_type capacity() const noexcept {
		if constexpr(has_capacity_v<const Impl>) {
			return Impl::capacity();
		}
		static_assert(has_capacity_v<const Impl>, "The implemention of string should provide `size_type capacity() const` as interface.");
	}

	constexpr size_type length() const noexcept {
		if constexpr(has_length_v<const Impl>) {
			return Impl::length();
		}
		return size(); // Use size() instead
	}

	constexpr size_type max_size() const noexcept {
		if constexpr(has_max_size_v<const Impl>) {
			return Impl::max_size();
		}
		// Apply npos if the implemention requires
		return std::min(npos, alloc_traits::max_size(_M_get_alloc())) - 1;
	}

public: // Iterators
	constexpr iterator begin() noexcept {
		if constexpr(has_begin_v<Impl>) {
			return Impl::begin();
		}
		return iterator(data());
	}

	constexpr const_iterator begin() const noexcept {
		if constexpr(has_begin_v<const Impl>) {
			return Impl::begin();
		}
		return const_iterator(data());
	}

	constexpr iterator end() noexcept {
		if constexpr(has_end_v<Impl>) {
			return Impl::end();
		}
		return iterator(data() + size());
	}

	constexpr const_iterator end() const noexcept {
		if constexpr(has_end_v<const Impl>) {
			return Impl::end();
		}
		return const_iterator(data() + size());
	}

	constexpr reverse_iterator rbegin() noexcept {
		if constexpr(has_rbegin_v<Impl>) {
			return Impl::rbegin();
		}
		return reverse_iterator(end());
	}

	constexpr const_reverse_iterator rbegin() const noexcept {
		if constexpr(has_rbegin_v<const Impl>) {
			return Impl::rbegin();
		}
		return const_reverse_iterator(end());
	}

	constexpr reverse_iterator rend() noexcept {
		if constexpr(has_rend_v<Impl>) {
			return Impl::rend();
		}
		return reverse_iterator(begin());
	}

	constexpr const_reverse_iterator rend() const noexcept {
		if constexpr(has_rend_v<const Impl>) {
			return Impl::rend();
		}
		return const_reverse_iterator(begin());
	}

	constexpr const_iterator cbegin() const noexcept {
		if constexpr(has_cbegin_v<const Impl>) {
			return Impl::cbegin();
		}
		return const_iterator(data());
	}

	constexpr const_iterator cend() const noexcept {
		if constexpr(has_cend_v<const Impl>) {
			return Impl::cend();
		}
		return const_iterator(data() + size());
	}

	constexpr const_reverse_iterator crbegin() const noexcept {
		if constexpr(has_crbegin_v<const Impl>) {
			return Impl::crbegin();
		}
		return const_reverse_iterator(end());
	}

	constexpr const_reverse_iterator crend() const noexcept {
		if constexpr(has_crend_v<const Impl>) {
			return Impl::crend();
		}
		return const_reverse_iterator(begin());
	}

public: // Size-oriented
	constexpr void reserve() {
		if constexpr(has_reserve_v<Impl>) {
			return Impl::reserve();
		}
		const size_type s = size();
		if(s < capacity()) {
			pointer tmp = _M_create(s, 0); // Avoid extend
			_S_copy(tmp, data(), s + 1);
			_M_dispose();
			_M_data(tmp);
			_M_capacity(s);
		}
	}

	constexpr void reserve(size_type n) {
		if constexpr(has_reserve_i_v<Impl>) {
			Impl::reserve(n);
			return;
		}
		// since it will only extend the capacity, so just return back
		DA_IFUNLIKELY(n < capacity()) {
			return;
		}
		pointer p = _M_create(n, capacity());
		_S_copy(p, data(), size() + 1);
		_M_dispose();
		_M_data(p);
		_M_capacity(n);
	}
	constexpr void shrink_to_fit() {
		if constexpr(has_shrink_to_fit_v<Impl>) {
			Impl::shrink_to_fit();
			return;
		}
		reserve();
	}

	constexpr void clear() noexcept {
		if constexpr(has_clear_v<Impl>) {
			Impl::clear();
			return;
		}
		_M_size(0);
	}

	constexpr bool empty() const noexcept {
		if constexpr(has_empty_v<const Impl>) {
			return Impl::empty();
		}
		return size() == 0;
	}

public: // Member access
	constexpr reference operator[](size_type n) {
		if constexpr(has_operator_square_i_v<Impl>) {
			return Impl::operator[](n);
		}
		assert(n <= size()); // Allow access the '\0'
		return data()[n];
	}

	constexpr const_reference operator[](size_type n) const noexcept {
		if constexpr(has_operator_square_i_v<const Impl>) {
			return Impl::operator[](n);
		}
		assert(n <= size()); // Allow access the '\0'
		return data()[n];
	}

	constexpr reference at(size_type n) {
		if constexpr(has_at_i_v<Impl>) {
			return Impl::at(n);
		}
		DA_IFUNLIKELY(n >= size()) {
			DA_THROW(std::out_of_range(fmt::format("da::string_base::at: n (which is {}) >= this->size() (which is {})", n, size())));
		}
		return data()[n];
	}

	constexpr const_reference at(size_type n) const {
		if constexpr(has_at_i_v<const Impl>) {
			return Impl::at(n);
		}
		DA_IFUNLIKELY(n >= size()) {
			DA_THROW(std::out_of_range(fmt::format("da::string_base::at: n (which is {}) >= this->size() (which is {})", n, size())));
		}
		return data()[n];
	}

	constexpr reference front() noexcept {
		if constexpr(has_front_v<Impl>) {
			return Impl::front();
		}
		assert(!empty());
		return operator[](0);
	}

	constexpr const_reference front() const noexcept {
		if constexpr(has_front_v<const Impl>) {
			return Impl::front();
		}
		assert(!empty());
		return operator[](0);
	}

	constexpr reference back() noexcept {
		if constexpr(has_back_v<Impl>) {
			return Impl::back();
		}
		assert(!empty());
		return operator[](size() - 1);
	}

	constexpr const_reference back() const noexcept {
		if constexpr(has_back_v<const Impl>) {
			return Impl::back();
		}
		assert(!empty());
		return operator[](size() - 1);
	}

public: // Replace
	/**
	 * @brief Change the content of the string in range [p, p + l1) to [s, s + l2)
	 * @param p  The start position to change
	 * @param l1 The origin length to change
	 * @param s  The string to be emplaced in the place
	 * @param l2 The length of s
	 * @note  Both @param l1 and @param l2 should not include '\0'
	 * @note  This function is the base of almost all insertion & deletion functions
	 */
	constexpr Self& replace(size_type p, size_type l1, const_pointer s, size_type l2) {
		if constexpr(has_replace_i_i_pc_i_v<Impl>) {
			return Impl::replace(p, l1, s, l2);
		}
		_M_check_pos(p, "da::string_base::replace");
		_M_check_pos(p + l1, "da::string_base::replace");
		_M_check_length(l1, l2, "da::string_base::replace");
		const pointer	dat			 = data(); // Cache
		const size_type remain_size	 = size() - l1 - p; // Remaining size of the origin string
		size_type		new_capacity = size() - l1 + l2; // New capacity
		if(new_capacity <= capacity()) { // No need to allocate the full string
			_S_copy_backward(dat + p + l2, dat + p + l1, remain_size);
			if(s) { // The replace string is not empty
				_S_copy(dat + p, s, l2);
			}
		} else {
			pointer tmp = _M_create(new_capacity, capacity());
			_S_copy(tmp, dat, p);
			if(s) { // The replace string is not empty
				_S_copy(tmp + p, s, l2);
			}
			_S_copy(tmp + p + l2, dat + p + l1, remain_size);
			_M_dispose();
			_M_data(tmp);
			_M_capacity(new_capacity);
		}
		_M_size(size() - l1 + l2); // Since new_capacity may has been extended, calculate it again;
		return *this;
	}

	/**
	 * @brief Change the content of the string in range [p, p + l1) to @param n times of @param c
	 * @param p The start position to change
	 * @param l The origin length to change
	 * @param n The number of characters
	 * @param c The character
	 * @note  This function is the base of almost all insertion & deletion functions
	 */
	constexpr Self& replace(size_type p, size_type l, size_type n, value_type c) {
		if constexpr(has_replace_i_i_i_v_v<Impl>) {
			return Impl::replace(p, l, n, c);
		}
		_M_check_pos(p, "da::string_base::replace");
		_M_check_pos(p + l, "da::string_base::replace");
		_M_check_length(l, n, "da::string_base::replace");
		const pointer	dat			 = data(); // Cache
		const size_type remain_size	 = size() - l - p; // Remaining size of the origin string
		size_type		new_capacity = size() - l + n; // New capacity
		if(new_capacity <= capacity()) { // No need to allocate the full string
			_S_copy_backward(dat + p + n, dat + p + l, remain_size);
			_S_assign(dat + p, n, c);
		} else {
			pointer tmp = _M_create(new_capacity, capacity());
			_S_copy(tmp, dat, p);
			_S_assign(tmp + p, n, c);
			_S_copy(tmp + p + n, dat + p + l, remain_size);
			_M_dispose();
			_M_data(tmp);
			_M_capacity(new_capacity);
		}
		_M_size(size() - l + n); // Since new_capacity may has been extended, calculate it again;
		return *this;
	}

	constexpr Self& replace(size_type p, size_type l, const_pointer s) {
		if constexpr(has_replace_i_i_pc_v<Impl>) {
			return Impl::replace(p, l, s);
		}
		return replace(p, l, s, _S_length(s));
	}

	constexpr Self& replace(size_type p, size_type l, const Self& s) {
		if constexpr(has_replace_i_i_scr_v<Impl>) {
			return Impl::replace(p, l, s);
		}
		return replace(p, l, s.data(), s.size());
	}

	constexpr Self& replace(size_type p, size_type l, const Self& s, size_type p2, size_type n = npos) {
		if constexpr(has_replace_i_i_scr_i_i_v<Impl>) {
			return Impl::replace(p, l, s, p2, n);
		}
		return replace(p, l, s.data() + s._M_check_pos(p2, "da::string_base::replace"), s._M_limit_length(p2, n));
	}

	constexpr Self& replace(const_iterator it1, const_iterator it2, const_pointer s, size_type n) {
		if constexpr(has_replace_tc_tc_pc_i_v<Impl>) {
			return Impl::replace(it1, it2, s, n);
		}
		return replace(it1 - begin(), it2 - it1, s, n);
	}

	constexpr Self& replace(const_iterator it1, const_iterator it2, size_type n, value_type v) {
		if constexpr(has_replace_tc_tc_i_v_v<Impl>) {
			return Impl::replace(it1, it2, n, v);
		}
		return replace(it1 - begin(), it2 - it1, n, v);
	}

	constexpr Self& replace(const_iterator it1, const_iterator it2, const_pointer s) {
		if constexpr(has_replace_tc_tc_pc_v<Impl>) {
			return Impl::replace(it1, it2, s);
		}
		return replace(it1 - begin(), it2 - it1, s, _S_length(s));
	}

	constexpr Self& replace(const_iterator it1, const_iterator it2, const Self& s) {
		if constexpr(has_replace_tc_tc_scr_v<Impl>) {
			return Impl::replace(it1, it2, s);
		}
		return replace(it1 - begin(), it2 - it1, s.data(), s.size());
	}

	constexpr Self& replace(const_iterator it1, const_iterator it2, pointer p1, pointer p2) {
		if constexpr(has_replace_tc_tc_p_p_v<Impl>) {
			return Impl::replace(it1, it2, p1, p2);
		}
		return replace(it1 - begin(), it2 - it1, p1, p2 - p1);
	}

	constexpr Self& replace(const_iterator it1, const_iterator it2, const_pointer p1, const_pointer p2) {
		if constexpr(has_replace_tc_tc_pc_pc_v<Impl>) {
			return Impl::replace(it1, it2, p1, p2);
		}
		return replace(it1 - begin(), it2 - it1, p1, p2 - p1);
	}

	constexpr Self& replace(const_iterator it1, const_iterator it2, iterator p1, iterator p2) {
		if constexpr(has_replace_tc_tc_t_t_v<Impl>) {
			return Impl::replace(it1, it2, p1, p2);
		}
		return replace(it1 - begin(), it2 - it1, p1, p2 - p1);
	}

	constexpr Self& replace(const_iterator it1, const_iterator it2, const_iterator p1, const_iterator p2) {
		if constexpr(has_replace_tc_tc_tc_tc_v<Impl>) {
			return Impl::replace(it1, it2, p1, p2);
		}
		return replace(it1 - begin(), it2 - it1, p1, p2 - p1);
	}

	constexpr Self& replace(const_iterator it1, const_iterator it2, std::initializer_list<value_type> il) {
		if constexpr(has_replace_tc_tc_vl_v<Impl>) {
			return Impl::replace(it1, it2, il);
		}
		return replace(it1 - begin(), it2 - it1, il.begin(), il.size());
	}

	template<forward_iterator Iter>
	constexpr Self& replace(const_iterator it1, const_iterator it2, Iter p1, Iter p2) {
		Self tmp(p1, p2);
		return replace(it1 - begin(), it2 - it1, tmp.data(), tmp.size());
	}

public: // Append
	/**
	 * @brief  Append a string with length n to the end of the origin string
	 * @param  p The string to append
	 * @param  n The length of the string
	 * @return The string itself to make it can be called again
	 * @note   This function is the base of all append functions
	 */
	constexpr Self& append(const_pointer p, size_type n) {
		if constexpr(has_append_pc_i_v<Impl>) {
			return Impl::append(p, n);
		}
		return replace(size(), 0, p, n);
	}

	/**
	 * @brief This function is similar to the function above, the only difference is that the length is calculated dynamically
	 */
	constexpr Self& append(const_pointer p) {
		if constexpr(has_append_pc_v<Impl>) {
			return Impl::append(p);
		}
		return append(p, _S_length(p));
	}

	constexpr Self& append(const Self& s) {
		if constexpr(has_append_scr_v<Impl>) {
			return Impl::append(s);
		}
		return append(s.data(), s.size());
	}

	constexpr Self& append(const Self& s, size_type p, size_type n = npos) {
		if constexpr(has_append_scr_i_i_v<Impl>) {
			return Impl::append(s, p, n);
		}
		return append(s.data() + s._M_check_pos(p, "da::string_base::append"), s._M_limit_length(p, n));
	}

	constexpr Self& append(std::initializer_list<Char> il) {
		if constexpr(has_append_vl_v<Impl>) {
			return Impl::append(il);
		}
		return append(il.begin(), il.size());
	}

	constexpr Self& append(size_type n, value_type c) {
		if constexpr(has_append_i_v_v<Impl>) {
			return Impl::append(n, c);
		}
		return replace(size(), 0, n, c);
	}

	template<forward_iterator Iter>
	constexpr Self& append(Iter it1, Iter it2) {
		return replace(size(), 0, it1, it2);
	}

	constexpr void push_back(value_type c) {
		if constexpr(has_push_back_v_v<Impl>) {
			Impl::push_back(c);
			return;
		}
		size_type s = size();
		if(s == capacity()) {
			replace(s, 0, nullptr, 1); // Extend the string length
		}
		_S_assign(data()[s], c);
	}

	constexpr Self& operator+=(const Self& s) {
		if constexpr(has_operator_plusequal_scr_v<Impl>) {
			return Impl::operator+=(s);
		}
		return append(s);
	}

	constexpr Self& operator+=(const_pointer s) {
		if constexpr(has_operator_plusequal_pc_v<Impl>) {
			return Impl::operator+=(s);
		}
		return append(s);
	}

	constexpr Self& operator+=(value_type c) {
		if constexpr(has_operator_plusequal_v_v<Impl>) {
			return Impl::operator+=(c);
		}
		push_back(c);
		return *this;
	}

	constexpr Self& operator+=(std::initializer_list<value_type> il) {
		if constexpr(has_operator_plusequal_vl_v<Impl>) {
			return Impl::operator+=(il);
		}
		return append(il);
	}

public: // Assignment
	constexpr Self& assign(const_pointer p, size_type n) {
		if constexpr(has_assign_pc_i_v<Impl>) {
			return Impl::assign(p, n);
		}
		if(data() == p) {
			return *this;
		}
		return replace(0, size(), p, n);
	}

	constexpr Self& assign(Self&& s) {
		if constexpr(has_assign_sR_v<Impl>) {
			return Impl::assign(s);
		}
		swap(move(s));
		return *this;
	}

	constexpr Self& assign(const_pointer p) {
		if constexpr(has_assign_pc_v<Impl>) {
			return Impl::assign(p);
		}
		return assign(p, _S_length(p));
	}

	constexpr Self& assign(const Self& s) {
		if constexpr(has_assign_scr_v<Impl>) {
			return Impl::assign(s);
		}
		return assign(s.data(), s.size());
	}

	constexpr Self& assign(const Self& s, size_type p, size_type n = npos) {
		if constexpr(has_assign_scr_i_i_v<Impl>) {
			return Impl::assign(s, p, n);
		}
		return assign(s.data() + s._M_check_pos(p, "da::string_base::assign"), s._M_limit_length(p, n));
	}

	constexpr Self& assign(std::initializer_list<Char> il) {
		if constexpr(has_assign_vl_v<Impl>) {
			return Impl::assign(il);
		}
		return assign(il.begin(), il.size());
	}

	constexpr Self& assign(size_type n, value_type c) {
		if constexpr(has_assign_i_v_v<Impl>) {
			return Impl::assign(n, c);
		}
		return replace(0, size(), n, c);
	}

	template<forward_iterator Iter>
	constexpr Self& assign(Iter it1, Iter it2) {
		return replace(0, size(), it1, it2);
	}

	constexpr Self& operator=(Self&& s) {
		if constexpr(has_operator_equal_sR_v<Impl>) {
			return Impl::operator=(s);
		}
		return assign(s);
	}

public: // Others
	constexpr void swap(const Self& s) {
		if constexpr(has_swap_scr_v<Impl>) {
			Impl::swap(s);
			return;
		}
		const pointer p = data();
		_M_data(s.data());
		s._M_data(p);
		const size_type c = capacity();
		_M_capacity(s.capacity());
		s._M_capacity(c);
		c = size();
		_M_size(s.size());
		s._M_size(c);
	}
};

DA_END_NAMESPACE

#endif // _DA_STRING_HPP_
