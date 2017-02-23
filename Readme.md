A tiny module to build constrained types from other `Regular` types.

This module is inspired by the [Boost Constrained Value Library](http://rk.hekko.pl/constrained_value)[1] which got proposed to boost but never actually accepted (as far as I know). This implementation here uses modern C++ and Concepts from [cmcstl2](https://github.com/CaseyCarter/cmcstl2)[2] and is integrated as a module into my [fub](https://github.com/maikel/fub)-library[3], which serves as a collection of useful day-to-day C++ constructs which I use.

As in [1] we use policies to define the constrain and behaviour on error. We also utilize the empty base class optimization.

One can easily define new constrained types by specializing the class `basic_constrained<T, Pred, OnError>`. That way we define proper `using`-declerations: `bounded<T, a, b>` (which bounds values of type `T` in a half open range `[a, b)`), `not_null<Pointer>` or `positive<T>`.

[1] - http://rk.hekko.pl/constrained_value <br/>
[2] - https://github.com/CaseyCarter/cmcstl2 <br/>
[3] - https://github.com/maikel/fub
