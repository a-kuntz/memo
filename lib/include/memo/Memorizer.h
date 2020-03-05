#ifndef HEADER_CBEEA770_5E54_11EA_91B2_784F43782D09
#define HEADER_CBEEA770_5E54_11EA_91B2_784F43782D09

#include <utility>
#include <tuple>

namespace memo
{

template<typename CACHE, typename CALLABLE>
class Memorizer
{
	public:
	Memorizer(const CALLABLE& callable, CACHE& cache)
	: _callable(callable)
	, _cache(cache)
	{}

	template<typename... ARGS>
	auto operator()(ARGS&&... args)
	{
		auto it = _cache.find(std::tuple(args...));
		if (it != _cache.end())
		{
			return it->second;
		}

		auto res = _callable(std::forward<ARGS>(args)...);
		_cache.emplace(std::tuple(args...), res);

		return res;
	}

	const CALLABLE& _callable;
	CACHE& _cache;
};

} // memo

#endif // HEADER_CBEEA770_5E54_11EA_91B2_784F43782D09
