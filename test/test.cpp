#include "../calculator.h"
#include "gtest/gtest.h"
#include <functional>
#include <limits>
#include <sstream>
#include <stdexcept>

// Basic functionality tests
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

// Mocking user input for getInput
TEST(InputTest, GetInputTest) {
  std::istringstream input("10\n");
  std::cin.rdbuf(input.rdbuf()); // Redirect std::cin

  int result = getInput("Enter a number: ");
  EXPECT_EQ(result, 10);
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

// Security-related tests
// Test for integer overflow in the add function
TEST(SecurityTest, AddIntegerOverflowTest) {
  int maxInt = std::numeric_limits<int>::max();
  EXPECT_THROW(
      {
        int result = add(maxInt, 1); // This should overflow
      },
      std::overflow_error);
}

// Test for input sanitization: large numbers or non-numeric input
TEST(SecurityTest, InputValidationTest) {
  std::istringstream input(
      "999999999999999999999999999999999\n"); // Extremely large number
  std::cin.rdbuf(input.rdbuf());              // Redirect std::cin

  EXPECT_THROW(
      {
        getInput("Enter a number: "); // Expect failure due to invalid input
      },
      std::invalid_argument);
}

// Test for null function pointer in processOperation
TEST(SecurityTest, NullFunctionPointerTest) {
  EXPECT_THROW(
      {
        processOperation(
            nullptr); // Passing nullptr should trigger an exception
      },
      std::runtime_error);
}

// Test for buffer overflow with large string input
TEST(SecurityTest, LargeInputBufferTest) {
  std::string largeInput(10000, '9'); // Create an excessively large input
  std::istringstream input(largeInput);
  std::cin.rdbuf(input.rdbuf()); // Redirect std::cin

  EXPECT_THROW(
      {
        getInput("Enter a number: "); // Should fail due to buffer size
      },
      std::overflow_error);
}

// Mocking user input for testing invalid and dangerous inputs
TEST(SecurityTest, MaliciousInputTest) {
  std::istringstream input(
      "DROP TABLE USERS;\n");    // Simulating SQL injection-like input
  std::cin.rdbuf(input.rdbuf()); // Redirect std::cin

  EXPECT_THROW(
      {
        getInput("Enter a number: "); // Should throw an invalid input exception
      },
      std::invalid_argument);
}

// Main function to run all tests
int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
