#include <memo/Memorizer.h>

#include <gtest/gtest.h>

#include <string>
#include <map>
#include <tuple>

std::string operator "" _s(const char* s, std::size_t len)
{
	return {s, len};
};

int counter;

auto fo(int a)
{
	++counter;
	return a;
}

auto foo(int a, int b)
{
	++counter;
	return a + b;
}

auto bar(const std::string& a, const std::string& b)
{
	++counter;
	return a + b;
}

TEST(memo, memorize_foo)
{
	{
		// using CacheType = std::map<int, int>;
		using CacheType = std::map<std::tuple<int>, int>;
		CacheType cache;
		memo::Memorizer m(fo, cache);

		counter = 0;
		EXPECT_EQ(m(1), 1);
		EXPECT_EQ(1, counter);
		EXPECT_EQ(m(2), 2);
		EXPECT_EQ(2, counter);
	}

	{
		using CacheType = std::map<std::tuple<int, int>, int>;
		CacheType cache;
		memo::Memorizer m(foo, cache);

		counter = 0;
		EXPECT_EQ(m(1, 2), 3);
		EXPECT_EQ(1, counter);
		EXPECT_EQ(m(1, 2), 3);
		EXPECT_EQ(2, counter);
	}

	{
		using CacheType = std::map<std::tuple<std::string, std::string>, std::string>;
		CacheType cache;
		memo::Memorizer m(bar, cache);

		counter = 0;
		EXPECT_EQ(m("hallo"_s, "welt"_s), "hallowelt");
		EXPECT_EQ(1, counter);
		EXPECT_EQ(m("hallo"_s, "welt"_s), "hallowelt");
		EXPECT_EQ(2, counter);
	}
}

TEST(memo, memorize_lambda)
{
	{
		auto lambda = [](const std::string& arg){return arg;};
		using CacheType = std::map<std::tuple<std::string>, std::string>;
		CacheType cache;
		memo::Memorizer m(lambda, cache);
		EXPECT_EQ(m(std::string("hello")), "hello");
	}

	{
		using CacheType = std::map<std::tuple<std::string>, std::string>;
		CacheType cache;
		memo::Memorizer m([](const std::string& arg){return arg;}, cache);
		EXPECT_EQ(m(std::string("hello")), "hello");
	}
}