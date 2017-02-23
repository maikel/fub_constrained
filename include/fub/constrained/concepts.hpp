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
	template <typename P, typename T>
	concept bool Predicate() {
		return requires (const P& pred, const T& value) {
			{ pred(value) } noexcept -> ranges::Boolean;
		};
	}

	// TODO Do I need std::add_lvalue_reference_t ?
	//      Is this even being used with reference types ?
	//      They are not regular!
	template <typename EP, typename T, Predicate<T> P>
	concept bool ErrorPolicy() {
		return ranges::Invocable<EP, T&, const T&, P>();
	}
}

#endif
