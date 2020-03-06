#include <memo/Memorizer.h>

#include <gtest/gtest.h>

#include <map>
#include <numeric>
#include <string>
#include <tuple>

int call_counter;

auto identity(int a)
{
	++call_counter;
	return a;
}

TEST(memo, memorize_identity)
{
	memo::Memorizer m(memo::Cache<int, int>(), identity);

	call_counter = 0;
	for (int val=1; val<10; ++val)
	{
		EXPECT_EQ(m(val), val);		// calculated
		EXPECT_EQ(val, call_counter);
		EXPECT_EQ(m(val), val);		// from cache
		EXPECT_EQ(val, call_counter);
	}
}

auto add(int a, int b)
{
	++call_counter;
	return a + b;
}

TEST(memo, memorize_add)
{
	memo::Memorizer m(memo::Cache<int, int, int>(), add);

	call_counter = 0;
	for (int val=1; val<10; ++val)
	{
		EXPECT_EQ(m(val, 1), val + 1);		// calculated
		EXPECT_EQ(val, call_counter);
		EXPECT_EQ(m(val, 1), val + 1);		// from cache
		EXPECT_EQ(val, call_counter);
	}
}

auto concat(const std::string& a, const std::string& b)
{
	++call_counter;
	return a + b;
}

std::string operator "" _s(const char* s, std::size_t len)
{
	return {s, len};
};

TEST(memo, memorize_concat)
{
	memo::Memorizer m(memo::Cache<std::string, std::string, std::string>(), concat);

	call_counter = 0;
	EXPECT_EQ(m("hallo"_s, "welt"_s), "hallowelt");
	EXPECT_EQ(1, call_counter);
	EXPECT_EQ(m("hallo"_s, "welt"_s), "hallowelt");
	EXPECT_EQ(1, call_counter);
}

TEST(memo, memorize_lambda)
{
	{
		auto lambda = [](const std::string& val){++call_counter; return val;};
		memo::Memorizer m(memo::Cache<std::string, std::string>(), lambda);

		call_counter = 0;
		EXPECT_EQ(m("hello"_s), "hello");
		EXPECT_EQ(1, call_counter);
		EXPECT_EQ(m("hello"_s), "hello");
		EXPECT_EQ(1, call_counter);
	}

	{
		memo::Memorizer m(memo::Cache<std::string, std::string>(), [](const std::string& val){++call_counter; return val;});

		call_counter = 0;
		EXPECT_EQ(m("hello"_s), "hello");
		EXPECT_EQ(1, call_counter);
		EXPECT_EQ(m("hello"_s), "hello");
		EXPECT_EQ(1, call_counter);
	}
}