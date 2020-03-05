#include <memo/Memorizer.h>

#include <gtest/gtest.h>

#include <map>
#include <string>
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
		using CacheType = std::map<std::tuple<int>, int>;
		memo::Memorizer m(fo, CacheType());

		counter = 0;
		EXPECT_EQ(m(1), 1);	// calculated
		EXPECT_EQ(1, counter);
		EXPECT_EQ(m(1), 1);	// from cache
		EXPECT_EQ(1, counter);

		EXPECT_EQ(m(2), 2);	// calculated
		EXPECT_EQ(2, counter);
		EXPECT_EQ(m(2), 2);	// from cache
		EXPECT_EQ(2, counter);
	}

	{
		using CacheType = std::map<std::tuple<int, int>, int>;
		memo::Memorizer m(foo, CacheType());

		counter = 0;
		EXPECT_EQ(m(1, 2), 3);
		EXPECT_EQ(1, counter);
		EXPECT_EQ(m(1, 2), 3);
		EXPECT_EQ(1, counter);
	}

	{
		using CacheType = std::map<std::tuple<std::string, std::string>, std::string>;
		memo::Memorizer m(bar, CacheType());

		counter = 0;
		EXPECT_EQ(m("hallo"_s, "welt"_s), "hallowelt");
		EXPECT_EQ(1, counter);
		EXPECT_EQ(m("hallo"_s, "welt"_s), "hallowelt");
		EXPECT_EQ(1, counter);
	}
}

TEST(memo, memorize_lambda)
{
	{
		auto lambda = [](const std::string& arg){++counter; return arg;};
		using CacheType = std::map<std::tuple<std::string>, std::string>;
		memo::Memorizer m(lambda, CacheType());

		counter = 0;
		EXPECT_EQ(m("hello"_s), "hello");
		EXPECT_EQ(1, counter);
		EXPECT_EQ(m("hello"_s), "hello");
		EXPECT_EQ(1, counter);
	}

	{
		using CacheType = std::map<std::tuple<std::string>, std::string>;
		memo::Memorizer m([](const std::string& arg){++counter; return arg;}, CacheType());

		counter = 0;
		EXPECT_EQ(m("hello"_s), "hello");
		EXPECT_EQ(1, counter);
		EXPECT_EQ(m("hello"_s), "hello");
		EXPECT_EQ(1, counter);
	}
}