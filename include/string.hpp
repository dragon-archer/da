/**
 * @file      string.hpp
 * @brief     interface of string
 * @version   0.1
 * @author    dragon-archer (dragon-archer@outlook.com)
 *
 * @copyright Copyright (c) 2022
 */

#ifndef _UTILITY_STRING_HPP_
#define _UTILITY_STRING_HPP_

#include "config.hpp"
#include "string/string_fwd.hpp"
#include "string/sso_string.hpp"
#include "type_traits.hpp"

namespace da {
	template<typename Char, typename Traits, typename Alloc,
			 template<typename, typename, typename> typename StringImpl>
	class string_base : protected StringImpl<Char, Traits, Alloc> { // Not public inherit to wrap the interface
	private:
		typedef StringImpl<Char, Traits, Alloc> Impl;
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

		static constexpr size_type npos = Impl::npos;

		// Constructors
	public:
		constexpr string_base() noexcept
			: Impl {} { }

	private: // Declare feature test structures
		/**
		 * @brief Naming rule:
		 *        1. Start with has_, followed by the function name
		 *        2. Connect with each parameter's mangled name by underline
		 *        Mangling rule:
		 *        1. Use one letter for basic class:
		 *        - i = size_type, p = pointer, v = value_type
		 *        2. Add descriptor after it if exists
		 *        - r = reference, c = const, il = std::initializer_list
		 */
		UTILITY_DECLARE_MEMBER_FUNCTION_TEST(has_get_alloc, get_alloc)
		UTILITY_DECLARE_MEMBER_FUNCTION_TEST(has_allocate_n, allocate_n)
		UTILITY_DECLARE_MEMBER_FUNCTION_TEST(has_deallocate_n, deallocate_n)
		UTILITY_DECLARE_MEMBER_FUNCTION_TEST(has_copy, copy)
		UTILITY_DECLARE_MEMBER_FUNCTION_TEST(has_copy_backward, copy_backward)
		UTILITY_DECLARE_MEMBER_FUNCTION_TEST(has_assign, assign)
		UTILITY_DECLARE_MEMBER_FUNCTION_TEST(has_create_ir_i, create, size_type&, size_type)

		UTILITY_DECLARE_MEMBER_FUNCTION_TEST(has_data, data)
		UTILITY_DECLARE_MEMBER_FUNCTION_TEST(has_size, size)
		UTILITY_DECLARE_MEMBER_FUNCTION_TEST(has_capacity, capacity)
		UTILITY_DECLARE_MEMBER_FUNCTION_TEST(has_data_p, data, pointer)
		UTILITY_DECLARE_MEMBER_FUNCTION_TEST(has_size_i, size, size_type)
		UTILITY_DECLARE_MEMBER_FUNCTION_TEST(has_capacity_i, capacity, size_type)
		UTILITY_DECLARE_MEMBER_FUNCTION_TEST(has_max_size, max_size)
		UTILITY_DECLARE_MEMBER_FUNCTION_TEST(has_length, length)

		UTILITY_DECLARE_MEMBER_FUNCTION_TEST(has_begin, begin)
		UTILITY_DECLARE_MEMBER_FUNCTION_TEST(has_end, end)
		UTILITY_DECLARE_MEMBER_FUNCTION_TEST(has_rbegin, rbegin)
		UTILITY_DECLARE_MEMBER_FUNCTION_TEST(has_rend, rend)
		UTILITY_DECLARE_MEMBER_FUNCTION_TEST(has_cbegin, cbegin)
		UTILITY_DECLARE_MEMBER_FUNCTION_TEST(has_cend, cend)
		UTILITY_DECLARE_MEMBER_FUNCTION_TEST(has_crbegin, crbegin)
		UTILITY_DECLARE_MEMBER_FUNCTION_TEST(has_crend, crend)

		UTILITY_DECLARE_MEMBER_FUNCTION_TEST(has_reserve, reserve)
		UTILITY_DECLARE_MEMBER_FUNCTION_TEST(has_reserve_i, reserve, size_type)
		UTILITY_DECLARE_MEMBER_FUNCTION_TEST(has_shrink_to_fit, shrink_to_fit)
		UTILITY_DECLARE_MEMBER_FUNCTION_TEST(has_clear, clear)
		UTILITY_DECLARE_MEMBER_FUNCTION_TEST(has_empty, empty)

		UTILITY_DECLARE_MEMBER_FUNCTION_TEST(has_operator_square_i, operator[], size_type)
		UTILITY_DECLARE_MEMBER_FUNCTION_TEST(has_at_i, at, size_type)
		UTILITY_DECLARE_MEMBER_FUNCTION_TEST(has_front, front)
		UTILITY_DECLARE_MEMBER_FUNCTION_TEST(has_back, back)

		UTILITY_DECLARE_MEMBER_FUNCTION_TEST(has_mutate_i_i_pc_i, mutate, size_type, size_type, const_pointer, size_type)
		UTILITY_DECLARE_MEMBER_FUNCTION_TEST(has_append_scr, append, const Self&)
		UTILITY_DECLARE_MEMBER_FUNCTION_TEST(has_append_scr_i_i, append, const Self&, size_type, size_type)
		UTILITY_DECLARE_MEMBER_FUNCTION_TEST(has_append_pc, append, const_pointer)
		UTILITY_DECLARE_MEMBER_FUNCTION_TEST(has_append_pc_i, append, const_pointer, size_type)
		UTILITY_DECLARE_MEMBER_FUNCTION_TEST(has_append_i_v, append, size_type, value_type)
		UTILITY_DECLARE_MEMBER_FUNCTION_TEST(has_append_vil, append, std::initializer_list<value_type>)

	protected: // Allocator
		constexpr allocator_type& get_alloc() const noexcept {
			if constexpr(has_get_alloc_v<const Impl>) {
				return Impl::get_alloc();
			}
			static_assert(has_get_alloc_v<Impl>, "The implemention of string should provide `allocator_type& get_alloc()` as interface.");
		}

		constexpr pointer allocate_n(size_type n) {
			if constexpr(has_allocate_n_v<Impl>) {
				return Impl::allocate_n(n);
			}
			return alloc_traits::allocate(get_alloc(), n + 1); // One more element for '\0'
		}

		constexpr void deallocate_n(pointer p, size_type n) {
			if constexpr(has_deallocate_n_v<Impl>) {
				Impl::deallocate_n(p, n);
				return;
			}
			alloc_traits::deallocate(get_alloc(), p, n + 1); // One more element for '\0'
		}

		static constexpr void copy(pointer dest, const_pointer src, size_type n) noexcept {
			if constexpr(has_copy_v<Impl>) {
				Impl::copy(dest, src, n);
				return;
			}
			traits_type::copy(dest, src, n + 1); // One more element for '\0'
		}

		static constexpr void copy_backward(pointer dest, const_pointer src, size_type n) noexcept {
			if constexpr(has_copy_v<Impl>) {
				Impl::copy(dest, src, n);
				return;
			}
			std::copy_backward(src, src + n + 1, dest); // One more element for '\0'
		}

		static constexpr void assign(reference dest, const_reference src) noexcept {
			if constexpr(has_assign_v<Impl>) {
				Impl::assign(dest, src);
				return;
			}
			traits_type::assign(dest, src);
		}

		constexpr pointer create(size_type& new_capacity, size_type old_capacity) {
			if constexpr(has_create_ir_i_v<Impl>) {
				return Impl::create(new_capacity, old_capacity);
			}
			if(new_capacity > max_size()) {
				UTILITY_THROW(std::length_error(format::format("da::string_base::create: The new capacity (which is {}) > max_size() (which is {})", new_capacity, max_size())));
			}
			if(new_capacity > old_capacity && new_capacity < 2 * old_capacity) {
				new_capacity = 2 * old_capacity;
				if(new_capacity > max_size()) {
					new_capacity = max_size();
				}
			}
			return allocate_n(new_capacity);
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

		constexpr void data(pointer p) noexcept {
			if constexpr(has_data_p_v<Impl>) {
				Impl::data(p);
				return;
			}
			static_assert(has_data_p_v<Impl>, "The implemention of string should provide `void data(pointer)` as interface.");
		}

		constexpr void size(size_type n) noexcept {
			if constexpr(has_size_i_v<Impl>) {
				Impl::size(n);
				return;
			}
			static_assert(has_size_i_v<Impl>, "The implemention of string should provide `void size(size_type)` as interface.");
		}

		constexpr void capacity(size_type n) noexcept {
			if constexpr(has_capacity_i_v<Impl>) {
				Impl::capacity(n);
				return;
			}
			static_assert(has_capacity_i_v<Impl>, "The implemention of string should provide `void capacity(size_type)` as interface.");
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
			return std::min(npos, alloc_traits::max_size(get_alloc())) - 1;
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
		UTILITY_CONSTEXPR_20 void reserve() {
			if constexpr(has_reserve_v<Impl>) {
				return Impl::reserve();
			}
			size_type s = size();
			size_type c = capacity();
			if(s < c) {
				pointer tmp = allocate_n(s);
				copy(tmp, data(), s);
				deallocate_n(data(), c);
				capacity(s);
				data(tmp);
			}
		}

		UTILITY_CONSTEXPR_20 void reserve(size_type n) {
			if constexpr(has_reserve_i_v<Impl>) {
				Impl::reserve(n);
				return;
			}
			// since it will only extend the capacity, so just return back
			UTILITY_IFUNLIKELY(n < capacity()) {
				return;
			}
			pointer p = allocate_n(n);
			copy(p, data(), size());
			deallocate_n(data(), capacity());
			data(p);
			capacity(n);
		}
		UTILITY_CONSTEXPR_20 void shrink_to_fit() {
			if constexpr(has_shrink_to_fit_v<Impl>) {
				Impl::shrink_to_fit();
				return;
			}
			reserve();
		}

		UTILITY_CONSTEXPR_20 void clear() noexcept {
			if constexpr(has_clear_v<Impl>) {
				Impl::clear();
				return;
			}
			size(0);
		}

		UTILITY_CONSTEXPR_20 bool empty() const noexcept {
			if constexpr(has_empty_v<const Impl>) {
				return Impl::empty();
			}
			return size() == 0;
		}

	public: // Member access
		UTILITY_CONSTEXPR_20 reference operator[](size_type n) {
			if constexpr(has_operator_square_i_v<Impl>) {
				return Impl::operator[](n);
			}
			assert(n <= size()); // Allow access the '\0'
			return data()[n];
		}

		UTILITY_CONSTEXPR_20 const_reference operator[](size_type n) const noexcept {
			if constexpr(has_operator_square_i_v<const Impl>) {
				return Impl::operator[](n);
			}
			assert(n <= size()); // Allow access the '\0'
			return data()[n];
		}

		UTILITY_CONSTEXPR_20 reference at(size_type n) {
			if constexpr(has_at_i_v<Impl>) {
				return Impl::at(n);
			}
			if(n >= size()) {
				UTILITY_THROW(std::out_of_range(format::format("da::string_base::at: n (which is {}) >= this->size() (which is {})", n, size())));
			}
			return data()[n];
		}

		UTILITY_CONSTEXPR_20 const_reference at(size_type n) const {
			if constexpr(has_at_i_v<const Impl>) {
				return Impl::at(n);
			}
			if(n >= size()) {
				UTILITY_THROW(std::out_of_range(format::format("da::string_base::at: n (which is {}) >= this->size() (which is {})", n, size())));
			}
			return data()[n];
		}

		UTILITY_CONSTEXPR_20 reference front() noexcept {
			if constexpr(has_front_v<Impl>) {
				return Impl::front();
			}
			assert(!empty());
			return operator[](0);
		}

		UTILITY_CONSTEXPR_20 const_reference front() const noexcept {
			if constexpr(has_front_v<const Impl>) {
				return Impl::front();
			}
			assert(!empty());
			return operator[](0);
		}

		UTILITY_CONSTEXPR_20 reference back() noexcept {
			if constexpr(has_back_v<Impl>) {
				return Impl::back();
			}
			assert(!empty());
			return operator[](size() - 1);
		}

		UTILITY_CONSTEXPR_20 const_reference back() const noexcept {
			if constexpr(has_back_v<const Impl>) {
				return Impl::back();
			}
			assert(!empty());
			return operator[](size() - 1);
		}

	public: // Content change
		/**
		 * @brief Change the content of the string in range [p, p + l1) to [s, s + l2)
		 * @param p  The start position to change
		 * @param l1 The origin length to change
		 * @param s  The string to be emplaced in the place
		 * @param l2 The length of s
		 * @note  Both @param l1 and @param l2 should not include '\0'
		 */
		UTILITY_CONSTEXPR_20 void mutate(size_type p, size_type l1, const_pointer s, size_type l2) {
			if constexpr(has_mutate_i_i_pc_i_v<Impl>) {
				Impl::mutate(p, l1, s, l2);
				return;
			}
			size_type remain_size  = size() - p - l1; // Remaining size of the origin string
			size_type new_capacity = size() - l1 + l2; // New capacity
			if(new_capacity <= capacity()) { // No need to allocate the full string
				if(remain_size) {
					copy_backward(data() + p + l2, data() + p + l1, remain_size);
				}
				if(s && l2) { // The replace string is not empty
					copy(data() + p, s, l2);
				}
			} else {
				pointer tmp = create(new_capacity, capacity());
				if(p) {
					copy(tmp, data(), p);
				}
				if(s && l2) { // The replace string is not empty
					copy(tmp + p, s, l2);
				}
				if(remain_size) {
					copy(tmp + p + l2, data() + p + l1, remain_size);
				}
				deallocate_n(data(), capacity());
				data(tmp);
				capacity(new_capacity);
			}
			size(new_capacity);
		}
	};
} // namespace da

#endif // _UTILITY_STRING_HPP_
