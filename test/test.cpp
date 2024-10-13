#include "../calculator.h"
#include "gtest/gtest.h"
#include <functional>
#include <optional>
#include <sstream>

// Test the add function
TEST(CalculatorTest, AddTest) {
  EXPECT_EQ(add(2, 3), 5);
  EXPECT_EQ(add(-1, 1), 0);
  EXPECT_EQ(add(0, 0), 0);
}

// Test the subtract function
TEST(CalculatorTest, SubtractTest) {
  EXPECT_EQ(subtract(5, 3), 2);
  EXPECT_EQ(subtract(0, 0), 0);
  EXPECT_EQ(subtract(1, 1), 0);
}

// Test the multiply function
TEST(CalculatorTest, MultiplyTest) {
  EXPECT_EQ(multiply(2, 3), 6);
  EXPECT_EQ(multiply(0, 1), 0);
  EXPECT_EQ(multiply(5, 5), 25);
}

// Mocking user input for getInput (valid input case)
TEST(InputTest, GetInputTestValid) {
  std::istringstream input("10\n");
  std::cin.rdbuf(input.rdbuf()); // Redirect std::cin

  std::optional<int> result = getInput("Enter a number: ");
  ASSERT_TRUE(result.has_value());
  EXPECT_EQ(result.value(), 10);
}

// Mocking user input for getInput (invalid input case)
TEST(InputTest, GetInputTestInvalid) {
  std::istringstream input("invalid\n");
  std::cin.rdbuf(input.rdbuf()); // Redirect std::cin

  std::optional<int> result = getInput("Enter a number: ");
  ASSERT_FALSE(result.has_value()); // Expect no valid input
}

// Test menu selection by simulating user choices
TEST(MenuTest, ProcessOperationTest) {
  std::unordered_map<int, std::function<int(int, int)>> operations = {
      {1, add}, {2, subtract}, {3, multiply}};

  std::istringstream input("5\n3\n");
  std::cin.rdbuf(input.rdbuf()); // Redirect std::cin

  testing::internal::CaptureStdout();
  processOperation(operations[1]); // Simulate add operation
  std::string output = testing::internal::GetCapturedStdout();

  EXPECT_EQ(output,
            "Enter the first number: Enter the second number: Result: 8\n");
}

// Main function to run all tests
int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
