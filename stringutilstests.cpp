#include <gtest/gtest.h>
#include <functional>
#include "stringutils.h"


TEST(split_map, empty_string_should_not_call_lambda)
{
	tottakai::split_map("", ' ', [] (const std::string&) {
		FAIL();
	});
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

TEST(partition, partition_should_split_string)
{
	EXPECT_EQ("", std::get<0>(tottakai::partition("", ' ')));
	EXPECT_EQ(' ', std::get<1>(tottakai::partition("", ' ')));
	EXPECT_EQ("", std::get<2>(tottakai::partition("", ' ')));

	EXPECT_EQ("foo", std::get<0>(tottakai::partition("foo:bar", ':')));
	EXPECT_EQ(':', std::get<1>(tottakai::partition("foo:bar", ':')));
	EXPECT_EQ("bar", std::get<2>(tottakai::partition("foo:bar", ':')));

	EXPECT_EQ("foo", std::get<0>(tottakai::partition("foo:bar:bar", ':')));
	EXPECT_EQ(':', std::get<1>(tottakai::partition("foo:bar:bar", ':')));
	EXPECT_EQ("bar:bar", std::get<2>(tottakai::partition("foo:bar:bar", ':')));
}

TEST(rpartition, partition_should_split_string_from_the_end)
{
	EXPECT_EQ("", std::get<0>(tottakai::rpartition("", ' ')));
	EXPECT_EQ(' ', std::get<1>(tottakai::rpartition("", ' ')));
	EXPECT_EQ("", std::get<2>(tottakai::rpartition("", ' ')));

	EXPECT_EQ("foo", std::get<0>(tottakai::rpartition("foo:bar", ':')));
	EXPECT_EQ(':', std::get<1>(tottakai::rpartition("foo:bar", ':')));
	EXPECT_EQ("bar", std::get<2>(tottakai::rpartition("foo:bar", ':')));

	EXPECT_EQ("foo:bar", std::get<0>(tottakai::rpartition("foo:bar:bar", ':')));
	EXPECT_EQ(':', std::get<1>(tottakai::rpartition("foo:bar:bar", ':')));
	EXPECT_EQ("bar", std::get<2>(tottakai::rpartition("foo:bar:bar", ':')));
}

TEST(each_line, empty_string_should_not_call_lambda)
{
	tottakai::each_line("", [] (const std::string&) {
		FAIL();
	});
}

TEST(each_line, single_line_should_call_lambda_once)
{
	std::string lines;
	tottakai::each_line("f", [&lines] (const std::string& line) {
		lines.append("/" + line + "/");
	});
	ASSERT_EQ("/f/", lines);

	lines.clear();
	tottakai::each_line("f\n", [&lines] (const std::string& line) {
		lines.append("/" + line + "/");
	});
	ASSERT_EQ("/f/", lines);
}

TEST(each_line, string_with_new_line_should_be_read_as_two_lines)
{
	std::string lines;
	tottakai::each_line("f\nb", [&lines] (const std::string& line) {
		lines.append("/" + line + "/");
	});
	ASSERT_EQ("/f//b/", lines);
}
