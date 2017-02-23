//          Copyright Maikel Nadolski 2017.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef FUB_POSITIVE_HPP
#define FUB_POSITIVE_HPP

#include "fub/constrained.hpp"
#include "fub/functional.hpp"

namespace fub
{
	template <typename T>
	using positive = constrained<T, is_positive>;
}

namespace fub::constrain
{
	template <typename T>
	struct default_value<positive<T>> {
		static constexpr T value = T{1};
	};
}

#endif