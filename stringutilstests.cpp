#include <gtest/gtest.h>
#include <functional>
#include "stringutils.h"


TEST(split_map, empty_string_should_not_call_lambda)
{
	auto func = [] (const std::string& substr) {
		FAIL();
	};
	tottakai::split_map("", ' ', func);
}

TEST(split_map, one_part_string_should_be_split_single_lambda_call_post)
{
	std::string processedString;
	tottakai::split_map("Authentication:", ':', [&processedString] (const std::string& substr) {
		processedString.append("/" + substr + "/");
	});
	ASSERT_EQ("/Authentication/", processedString);
}

TEST(split_map, one_part_string_should_be_split_single_lambda_call_pre)
{
	std::string processedString;
	tottakai::split_map(":Authentication", ':', [&processedString] (const std::string& substr) {
		processedString.append("/" + substr + "/");
	});
	ASSERT_EQ("///Authentication/", processedString);
}

TEST(split_map, two_part_string_should_be_split_into_two_parts)
{
	std::string processedString;
	tottakai::split_map("Authentication:A7648AB7", ':', [&processedString] (const std::string& substr) {
		processedString.append("/" + substr + "/");
	});
	ASSERT_EQ("/Authentication//A7648AB7/", processedString);
}

TEST(split_map, three_part_string_should_be_split_into_three_parts)
{
	std::string processedString;
	tottakai::split_map("Little brown for", ' ', [&processedString] (const std::string& substr) {
		processedString.append("/" + substr + "/");
	});
	ASSERT_EQ("/Little//brown//for/", processedString);
}

TEST(split_map, three_part_with_empty_should_not_skip_empty_strings)
{
	std::string processedString;
	tottakai::split_map("Little??brown", '?', [&processedString] (const std::string& substr) {
		processedString.append("/" + substr + "/");
	});
	ASSERT_EQ("/Little////brown/", processedString);
}

TEST(strip, strip_should_remove_leading_and_trailing_whitespace)
{
	EXPECT_EQ("", tottakai::strip(""));
	EXPECT_EQ("foo", tottakai::strip(" foo"));
	EXPECT_EQ("", tottakai::strip(" "));
	EXPECT_EQ("foo", tottakai::strip("foo "));
	EXPECT_EQ("foo", tottakai::strip(" foo "));
	EXPECT_EQ("foo", tottakai::strip("  foo "));
	EXPECT_EQ("foo", tottakai::strip(" foo  "));

	EXPECT_EQ("foo foo", tottakai::strip("foo foo"));
	EXPECT_EQ("foo foo", tottakai::strip(" foo foo"));
	EXPECT_EQ("foo foo", tottakai::strip("foo foo "));
	EXPECT_EQ("foo foo", tottakai::strip(" foo foo "));
	EXPECT_EQ("foo foo", tottakai::strip(" foo foo "));

	EXPECT_EQ("foo  foo", tottakai::strip(" foo  foo "));

	EXPECT_EQ("foo  foo  foo", tottakai::strip(" foo  foo  foo "));

	EXPECT_EQ("foo", tottakai::strip("\v\t\n\t\v\f\rfoo\t\n\v\f\r"));
}

TEST(lstrip, whitespace_should_be_stripped_from_the_front)
{
	EXPECT_EQ("", tottakai::lstrip(""));
	EXPECT_EQ("", tottakai::lstrip(" "));
	EXPECT_EQ("foo", tottakai::lstrip(" foo"));
	EXPECT_EQ("foo ", tottakai::lstrip("foo "));
	EXPECT_EQ("foo", tottakai::lstrip("  foo"));
	EXPECT_EQ("foo foo", tottakai::lstrip(" foo foo"));
}

TEST(rstrip, whitespace_should_be_stripped_from_the_back)
{
	EXPECT_EQ("", tottakai::rstrip(""));
	EXPECT_EQ("", tottakai::rstrip(" "));
	EXPECT_EQ(" foo", tottakai::rstrip(" foo"));
	EXPECT_EQ("foo", tottakai::rstrip("foo "));
	EXPECT_EQ("foo", tottakai::rstrip("foo  "));
	EXPECT_EQ("foo foo", tottakai::rstrip("foo foo "));
}
