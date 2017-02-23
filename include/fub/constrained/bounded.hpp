//          Copyright Maikel Nadolski 2017.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef FUB_CONSTRAINED_BOUNDED_HPP
#define FUB_CONSTRAINED_BOUNDED_HPP

#include "fub/constrained/constrained.hpp"

namespace fub
{
	namespace constrain
	{
		/// Checks if a given value is in half open range [Lower, Upper)
		template <auto Lower, auto Upper>
		struct is_in_range {
			using lower_type = decltype(Lower);
			using upper_type = decltype(Upper);

			template <typename T>
				requires (
					constrain::LessThanComparable<T, lower_type>() &&
					constrain::LessThanComparable<T, upper_type>()
				)
			constexpr bool operator()(const T& value) const noexcept
			{
				return !(value < Lower) && value < Upper;
			}
		};
	}

	/// Bound Comparable Values in a half open range [Lower, Upper)
	template <typename T, auto Lower, auto Upper>
		requires ( ranges::ConvertibleTo<decltype(Lower), T>() )
	using bounded = constrained<T, constrain::is_in_range<Lower, Upper>>;

	/// If the default value is out of range we set the lower bound to be
	/// the new default value
	template <typename T, auto Lower, auto Upper>
		requires(
			ranges::ConvertibleTo<decltype(Lower), T>() &&
			! constrain::is_in_range<Lower, Upper>{}(T{})
		)
	struct constrain::default_value<bounded<T, Lower, Upper>> {
		static constexpr T value = T{Lower};
	};
}

#endif