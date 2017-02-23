//          Copyright Maikel Nadolski 2016.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include "fub/constrained.hpp"

struct is_even
{
	constexpr bool operator()(int i) const noexcept
	{ return i % 2 == 0; }
};

template <typename T, typename Pred>
using constrained = fub::constrain::basic_constrained<T, Pred, fub::constrain::throw_exception<>>;

#define CATCH_CONFIG_MAIN
#include "catch.hpp"

TEST_CASE("uses ebo")
{
	auto c1 = constrained<int, is_even>{};
	REQUIRE(sizeof(c1) == sizeof(int));
}

TEST_CASE("throws on construction")
{
	auto c1 = constrained<int, is_even>{};
	REQUIRE( c1 == 0 );
	REQUIRE_THROWS( c1 = 1 );
	REQUIRE( c1 == 0 );
}

TEST_CASE("positive gets initialized with 1")
{
	auto p = fub::positive<int>{};
	REQUIRE( p == 1 );
}

TEST_CASE("not_null is not default constructible")
{
	REQUIRE( !std::is_default_constructible<fub::not_null<int*>>::value );
	REQUIRE(( std::is_nothrow_constructible<fub::not_null<int*>, int*>::value ));
}

TEST_CASE("Test some not_null semantics")
{
	int a = 1;
	fub::not_null<int*> ptr = &a;
	REQUIRE( ptr == &a );
	*ptr = 2;
	REQUIRE( a == 2 );
}