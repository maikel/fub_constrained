//          Copyright Maikel Nadolski 2017.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef FUB_CONSTRAINED_CONSTRAINED_HPP
#define FUB_CONSTRAINED_CONSTRAINED_HPP

#include "fub/constrained/concepts.hpp"
#include "fub/constrained/error_policies.hpp"

namespace fub::constrain
{
	/// This meta function is used, such that a user can define new default
	/// values for its constrained value type.
	template <typename T>
	struct default_value {
		static constexpr T value = T{};
	};

	/// Specialize this class to indicate if a constrained type should not
	/// have any default construction (no matter what)
	template <typename T>
	struct is_default_construcible : std::true_type {};

	/// Check wether a given type is invocable with the given argument types
	template <typename T, typename... Args>
	struct is_nothrow_invocable {
		static constexpr bool value = noexcept (
				std::invoke(std::declval<T>(), std::declval<Args>()...)
		);
	};

	/// Check wether a given type has a noexcept-member-function check which
	/// is callable with Args...
	template <typename T, typename... Args>
	struct is_nothrow_check {
		static constexpr bool value = noexcept (
				std::declval<T>().check(std::declval<Args>()...)
		);
	};

	/// This is used to check if a given prvalue is constexpr evaluable.
	template <typename T> 
	constexpr typename std::remove_reference<T>::type makeprval(T && t) {
		return t;
	}
	#define isprvalconstexpr(e) noexcept(makeprval(e))

	/// We use this type_trait to check whether a predicate is fulfilled for
	/// given default value.
	/// If a) the predicate is not constexpr it returns true (fulfilled) and
	///       thus the constrained type gets default constructible
	///    b) the predicate *is* constexpr the trait evaluates it with the
	///       default value and returns the result.
	template <class Pred, class Default>
	struct fulfills_predicate : std::true_type {};

	template <class Pred, class T>
	requires( isprvalconstexpr(( Pred{}(default_value<T>::value) )) )
	struct fulfills_predicate<Pred, default_value<T>>
	{
		static constexpr bool value = Pred{}(default_value<T>::value);
	};

	/// A thin wrapper around some regular value type which enforces some
	/// constrain. We use empty base class optimization to make it a non-cost.
	template <ranges::Regular T, ranges::Predicate<T> CP, ErrorPolicy<T, CP> EP>
	class basic_constrained
		: private CP
		, private EP
	{
	public:
		using value_type       = T;
		using const_reference  = const T&;
		using error_policy     = EP;
		using constrain_policy = CP;

		// Check for constrained constructors

		/// Checks default value for constrain
		constexpr basic_constrained()
		noexcept(is_nothrow_check<basic_constrained&, value_type>::value)
		requires (
				is_default_construcible<basic_constrained>::value &&
				ranges::DefaultConstructible<constrain_policy>() &&
				ranges::DefaultConstructible<error_policy>() &&
				fulfills_predicate<constrain_policy, default_value<basic_constrained>>::value
				// For non-constexpr predicates this is true (can not be checked in compile time)
		)
			: m_value{check(default_value<basic_constrained>::value)}
		{}

		/// Implicit conversion from value_type
		constexpr basic_constrained(const value_type& value)
		noexcept(is_nothrow_check<basic_constrained&, value_type>::value)
		requires (
				ranges::DefaultConstructible<constrain_policy>() &&
				ranges::DefaultConstructible<error_policy>()
		)
			: m_value{check(value)}
		{}

		// Copy, move and destructor are defaulted.
		constexpr basic_constrained(const basic_constrained&) noexcept = default;
		constexpr basic_constrained(basic_constrained&&) noexcept = default;
		constexpr basic_constrained& operator=(const basic_constrained&) noexcept = default;
		constexpr basic_constrained& operator=(basic_constrained&&) noexcept = default;
		~basic_constrained() noexcept = default;

		/// Casts this class to its error_policy
		constexpr const error_policy&
		error_handler()
		const noexcept
		{
			return static_cast<const error_policy&>(*this);
		}

		/// Cast this class to its constrain_policy
		constexpr const constrain_policy&
		constrain_handler()
		const noexcept
		{
			return static_cast<const constrain_policy&>(*this);
		}

		/// Returns the value which is stored
		constexpr const_reference value() const noexcept
		{
			return m_value;
		}

		/// implicit conversion to its value_type
		constexpr operator const_reference() const noexcept
		{
			return m_value;
		}

	private:
		/// This function actually invoces the policy functions and thus calls
		/// all the logic.
		constexpr const_reference check(const value_type& value)
		noexcept(is_nothrow_invocable<
				const error_policy&, value_type&, const value_type&, constrain_policy>::value)
		{
			std::invoke(error_handler(), m_value, value, std::ref(constrain_handler()));
			return value;
		}

		/// This is the value which we actually wrap
		value_type m_value;
	};

	template <typename T, typename P, typename E>
	struct default_value<basic_constrained<T, P, E>> {
		static constexpr T value = T{};
	};
}

namespace fub
{
	using constrain::basic_constrained;

	/// This is a convenient typedef. Default behaviour is to terminate the
	/// program if the condition is broken.
	template <ranges::Regular T, ranges::Predicate<T> Pred>
	using constrained = basic_constrained<T, Pred, constrain::terminate>;
}

#endif