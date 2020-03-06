# memo

Simple function memorizer library

## abstract

The memorizer stores results of expensive calculations and returns the cached value in case the same input is received a second time.

The memorizer provides automated return value caching for stateless callables such as functions and lambdas. The memorizer wraps the callable and mimics its signature. Thus it can be used as a replacement for the callable. When called with some argument, the memorizer delegates them to the callable. It then caches and returns the result value. In case the argument was seen before, the result is directly returned from the internal cache. The memorizer ensures that the callable is executed only once per argument. This pattern helps to minimize the number of expensive calculations.

```C++
Res foo(Arg arg /* ... */)
{
  /* some expensive calculation */
  return result;
}

memo::Memorizer cached_foo(foo, memo::Cache<Res, Arg>());

// assume Args contains possible arguments to foo(.)
for (const auto& arg : Args)
{
  assert(cached_foo(arg) == foo(arg));
}
```

## implementation details

The memorizer is implemented as decorator to a given function `foo(.)`. It provides an unlimited table based cache, which is implemented my means of `std::map<std::tuple<ARGS...>>`.

> Note: For recursive functions the memorizer is currently only able to cache the outermost invocation.
