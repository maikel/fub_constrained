//          Copyright Maikel Nadolski 2017.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef FUB_CONSTRAINED_CONCEPTS_HPP
#define FUB_CONSTRAINED_CONCEPTS_HPP

#include <experimental/ranges/concepts>

namespace fub
{
	namespace ranges = std::experimental::ranges;
}

namespace fub::constrain
{
	// TODO Do I need std::add_lvalue_reference_t ?
	//      Is this even being used with reference types ?
	//      They are not regular!
	template <typename EP, typename T, ranges::Predicate<T> P>
	concept bool ErrorPolicy() {
		return ranges::Invocable<EP, T&, const T&, P>();
	}

	template <typename T, typename S>
	concept bool LessThanComparable() {
		return requires (const T& left, const T& right) {
			{ left < right } -> ranges::Boolean;
		};
	}
}

#endif
