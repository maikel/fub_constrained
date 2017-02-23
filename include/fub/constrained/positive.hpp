//          Copyright Maikel Nadolski 2017.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef FUB_CONSTRAINED_POSITIVE_HPP
#define FUB_CONSTRAINED_POSITIVE_HPP

#include "fub/constrained/constrained.hpp"

namespace fub
{
	namespace constrain
	{
		/// Returns true for a type `T` if a value `T x` is greater than `T{0}`.
		struct is_positive {
			template <typename T>
			constexpr bool operator()(const T& x) const noexcept
			{ return x > T{0}; }
		};
	}

	/// This type enforces positivity onto values.
	template <typename T>
	using positive = constrained<T, constrain::is_positive>;

	template <typename T>
	struct constrain::default_value<positive<T>> {
		static constexpr T value = T{1};
	};
}

#endif