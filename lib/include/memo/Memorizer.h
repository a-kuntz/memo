#ifndef HEADER_CBEEA770_5E54_11EA_91B2_784F43782D09
#define HEADER_CBEEA770_5E54_11EA_91B2_784F43782D09

#include <iterator>
#include <map>
#include <tuple>
#include <utility>

namespace memo
{

template<typename RESULT, typename... ARGS>
using Cache = std::map<std::tuple<ARGS...>, RESULT>;

template<typename CACHE, typename CALLABLE>
class Memorizer
{
	public:
	Memorizer(CACHE, const CALLABLE& callable)
	: _callable(callable)
	{}

	template<typename... ARGS>
	auto operator()(ARGS&&... args)
	{
		auto it = _cache.find(std::tuple(args...));
		if (std::end(_cache) != it)
		{
			return it->second;
		}

		auto res = _callable(std::forward<ARGS>(args)...);
		_cache.emplace(std::tuple(args...), res);

		return res;
	}

	auto size() const
	{
		return _cache.size();
	}

	const CALLABLE& _callable;
	CACHE _cache;
};

} // memo

#endif // HEADER_CBEEA770_5E54_11EA_91B2_784F43782D09
