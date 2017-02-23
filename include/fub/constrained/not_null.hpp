//          Copyright Maikel Nadolski 2017.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef FUB_CONSTRAINED_NOT_NULL_HPP
#define FUB_CONSTRAINED_NOT_NULL_HPP

#include "fub/constrained/constrained.hpp"

namespace fub
{
	namespace constrain
	{
		/// Returns true if the given value is not `nullptr`.
		struct is_not_nullptr {
			template <typename T>
			constexpr bool operator()(T p) const noexcept
			{ return p != nullptr; }
		};
	}

	/// \typedef A vocabulary type to express non-nullness of pointers.
	template <typename T>
	using not_null = constrained<T, constrain::is_not_nullptr>;
}

#endif
