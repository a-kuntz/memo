#include <memo/Memorizer.h>

#include <gtest/gtest.h>

#include <string>

int foo(int a, int b)
{
	return a + b;
}

auto bar(const std::string& arg)
{
	return arg;
}

TEST(memo, memorize_foo)
{
	{
		memo::Memorizer m(foo);
		EXPECT_EQ(m(1, 2), 3);
	}

	{
		memo::Memorizer m(bar);
		EXPECT_EQ(m("hallo"), "hallo");
	}
}

TEST(memo, memorize_lambda)
{
	{
		auto lambda = [](const std::string& arg){return arg;};
		memo::Memorizer m(lambda);
		EXPECT_EQ(m(std::string("hello")), "hello");
	}

	{
		memo::Memorizer m([](const std::string& arg){return arg;});
		EXPECT_EQ(m(std::string("hello")), "hello");
	}
}