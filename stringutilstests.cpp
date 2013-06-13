#include <gtest/gtest.h>
#include "stringutils.h"
#include <functional>


TEST(StringUtils, empty_string_should_not_call_lambda)
{
	tottakai::split_map("", ' ', [] (const std::string& substr) {
		FAIL();
	});
}

TEST(StringUtils, one_part_string_should_be_split_single_lambda_call_post)
{
	std::string processedString;
	tottakai::split_map("Authentication:", ':', [&processedString] (const std::string& substr) {
		processedString.append("/" + substr + "/");
	});
	ASSERT_EQ("/Authentication/", processedString);
}

TEST(StringUtils, one_part_string_should_be_split_single_lambda_call_pre)
{
	std::string processedString;
	tottakai::split_map(":Authentication", ':', [&processedString] (const std::string& substr) {
		processedString.append("/" + substr + "/");
	});
	ASSERT_EQ("///Authentication/", processedString);
}

TEST(StringUtils, two_part_string_should_be_split_into_two_parts)
{
	std::string processedString;
	tottakai::split_map("Authentication:A7648AB7", ':', [&processedString] (const std::string& substr) {
		processedString.append("/" + substr + "/");
	});
	ASSERT_EQ("/Authentication//A7648AB7/", processedString);
}

TEST(StringUtils, three_part_string_should_be_split_into_three_parts)
{
	std::string processedString;
	tottakai::split_map("Little brown for", ' ', [&processedString] (const std::string& substr) {
		processedString.append("/" + substr + "/");
	});
	ASSERT_EQ("/Little//brown//for/", processedString);
}

TEST(StringUtils, three_part_with_empty_should_not_skip_empty_strings)
{
	std::string processedString;
	tottakai::split_map("Little??brown", '?', [&processedString] (const std::string& substr) {
		processedString.append("/" + substr + "/");
	});
	ASSERT_EQ("/Little////brown/", processedString);
}