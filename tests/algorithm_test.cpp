#include "../src/utils/Utils.hpp" // Include your header!

#include <gtest/gtest.h>
#include <string>

// 1. Test the "Happy Path" (Normal functionality)
TEST(AlgorithmTest, CalculatesCorrectDistance)
{
    auto result = Utils::calculate_edit_distance("kitten", "sitting");

    EXPECT_EQ(result.actions_num, 3);
    EXPECT_EQ(result.actions.size(), 3);
    EXPECT_EQ(result.actions[0], "Replace 'k' with 's'");
}

// 2. Test an Edge Case (Identical strings)
TEST(AlgorithmTest, HandlesIdenticalStrings)
{
    auto result = Utils::calculate_edit_distance("hello", "hello");

    EXPECT_EQ(result.actions_num, 0);
    EXPECT_TRUE(result.actions.empty());
}

// 3. Test the Exception (Protection against huge strings)
TEST(AlgorithmTest, ThrowsOnOversizedStrings)
{
    // Create a string that is exactly 1001 characters long
    std::string huge_string(1001, 'a');

    // GTest will actually verify that your function throws the correct error!
    EXPECT_THROW({ Utils::calculate_edit_distance(huge_string, "test"); }, std::invalid_argument);
}