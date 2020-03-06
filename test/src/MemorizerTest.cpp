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
	memo::Memorizer cached_identity(identity, memo::Cache<int, int>());

	call_counter = 0;
	for (int val=1; val<10; ++val)
	{
		EXPECT_EQ(val, cached_identity(val));		// calculated
		EXPECT_EQ(val, cached_identity.size());
		EXPECT_EQ(val, call_counter);
		EXPECT_EQ(val, cached_identity(val));		// from cache
		EXPECT_EQ(val, cached_identity.size());
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
	memo::Memorizer cached_add(add, memo::Cache<int, int, int>());

	call_counter = 0;
	for (int val=1; val<10; ++val)
	{
		EXPECT_EQ(val + 1, cached_add(val, 1));		// calculated
		EXPECT_EQ(val, cached_add.size());
		EXPECT_EQ(val, call_counter);
		EXPECT_EQ(val + 1, cached_add(val, 1));		// from cache
		EXPECT_EQ(val, cached_add.size());
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
	memo::Memorizer cached_concat(concat, memo::Cache<std::string, std::string, std::string>());

	call_counter = 0;
	EXPECT_EQ("hallowelt", cached_concat("hallo"_s, "welt"_s));
	EXPECT_EQ(1, cached_concat.size());
	EXPECT_EQ(1, call_counter);
	EXPECT_EQ("hallowelt", cached_concat("hallo"_s, "welt"_s));
	EXPECT_EQ(1, cached_concat.size());
	EXPECT_EQ(1, call_counter);
}

TEST(memo, memorize_lambda)
{
	{
		auto lambda = [](const std::string& val){++call_counter; return val;};
		memo::Memorizer cached_lambda(lambda, memo::Cache<std::string, std::string>());

		call_counter = 0;
		EXPECT_EQ("hello", cached_lambda("hello"_s));
		EXPECT_EQ(1, cached_lambda.size());
		EXPECT_EQ(1, call_counter);
		EXPECT_EQ("hello", cached_lambda("hello"_s));
		EXPECT_EQ(1, cached_lambda.size());
		EXPECT_EQ(1, call_counter);
	}

	{
		memo::Memorizer cached_lambda([](const std::string& val){++call_counter; return val;}, memo::Cache<std::string, std::string>());

		call_counter = 0;
		EXPECT_EQ("hello", cached_lambda("hello"_s));
		EXPECT_EQ(1, cached_lambda.size());
		EXPECT_EQ(1, call_counter);
		EXPECT_EQ("hello", cached_lambda("hello"_s));
		EXPECT_EQ(1, cached_lambda.size());
		EXPECT_EQ(1, call_counter);
	}
}