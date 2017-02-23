Basic module to build constrained types from other regular types.
This library is inspired by boost constrained but uses C++-Concepts and cmcstl2.
It also uses policies to define the constrain, behaviour on error and utilizes the empty base class optimization.

This module also defines the constrained types `not_null<Pointer>` and `positive<T>` based on `basic_constrained<T, P, E>`.