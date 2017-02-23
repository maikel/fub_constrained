//          Copyright Maikel Nadolski 2017.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef FUB_CONSTRAINED_POSITIVE_HPP
#define FUB_CONSTRAINED_POSITIVE_HPP

#include "fub/constrained/constrained.hpp"
#include "fub/constrained/functional.hpp"

namespace fub
{
	template <typename T>
	using positive = constrained<T, is_positive>;

	template <typename T>
	struct constrain::default_value<positive<T>> {
		static constexpr T value = T{1};
	};
}

#endif