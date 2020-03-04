#ifndef HEADER_CBEEA770_5E54_11EA_91B2_784F43782D09
#define HEADER_CBEEA770_5E54_11EA_91B2_784F43782D09

namespace memo
{

template<typename CALLABLE>
class Memorizer
{
	public:
	Memorizer(const CALLABLE& callable)
	: _callable(callable)
	{}

	template<typename... ARGS>
	auto operator()(ARGS&&... args)
	{
		return _callable(args...);
	}

	const CALLABLE& _callable;
};

} // memo

#endif // HEADER_CBEEA770_5E54_11EA_91B2_784F43782D09
