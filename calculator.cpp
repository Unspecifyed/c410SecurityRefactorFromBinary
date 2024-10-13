// calculator.cpp
#include "calculator.h"
#include <iostream>
#include <limits>
#include <sstream>
#include <stdexcept>

// Function definitions
int add(int a, int b) { return a + b; }
int subtract(int a, int b) { return a - b; }
int multiply(int a, int b) { return a * b; }

void displayMenu() {
  std::cout << "Select an operation:\n";
  std::cout << "1) Add\n";
  std::cout << "2) Subtract\n";
  std::cout << "3) Multiply\n";
  std::cout << "4) Exit\n";
  std::cout << "Enter your choice: ";
}

std::optional<int> getInput(const std::string &prompt) {
  std::string inputStr;
  int input;

  std::cout << prompt;
  std::getline(std::cin, inputStr); // Get entire line as a string
  std::istringstream inputStream(
      inputStr); // Create a string stream for parsing

  // Try to extract an integer from the stream
  if (inputStream >> input) {
    // If valid integer is extracted, return the input
    return input;
  } else {
    // Handle invalid input by returning null equivalent (std::nullopt)
    std::cout << "Invalid input. Returning null." << std::endl;
    return std::nullopt;
  }
}

void processOperation(const std::function<int(int, int)> &operation) {
  int a = getInput("Enter the first number: ");
  int b = getInput("Enter the second number: ");
  std::cout << "Result: " << operation(a, b) << "\n";
}
