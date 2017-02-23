//          Copyright Maikel Nadolski 2017.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef FUB_FUNCTIONAL_HPP
#define FUB_FUNCTIONAL_HPP

namespace fub
{
	struct is_positive {
		template <typename T>
		constexpr bool operator()(const T& x) const noexcept
		{ return x > T{0}; }
	};

	struct is_not_nullptr {
		template <typename T>
		constexpr bool operator()(T p) const noexcept
		{ return p != nullptr; }
	};
}

#endif