//          Copyright Maikel Nadolski 2017.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef FUB_CONSTRAINED_ERROR_POLICIES_HPP
#define FUB_CONSTRAINED_ERROR_POLICIES_HPP

#include "fub/constrained/concepts.hpp"

namespace fub::constrain
{
	/// This policy terminates the program upon constrain failure.
	struct terminate {
		template <typename T, typename Pred>
		void operator()(T&, const T& new_value, Pred pred) const noexcept
		{
			if (!std::invoke(pred, new_value)) {
				std::terminate();
			}
		}
	};

	/// This policy throws an exception on constrain violation and leaves the
	/// old value untouched.
	template <typename Exception = std::logic_error>
	struct throw_exception {
		template <typename T, typename Pred>
		void operator()(T&, const T& new_value, Pred pred) const
		{
			if (!std::invoke(pred, new_value)) {
				throw Exception{"Constrain Error."};
			}
		}
	};
}

#endif