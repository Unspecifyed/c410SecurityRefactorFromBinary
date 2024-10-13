#include "calculator.h"
#include <iostream>
#include <limits>
#include <optional>
#include <sstream>
#include <stdexcept>

// Function definitions
int add(int a, int b) { return a + b; }

int subtract(int a, int b) { return a - b; }

int multiply(int a, int b) { return a * b; }

// Function to display the menu
void displayMenu() {
  std::cout << "Select an operation:\n";
  std::cout << "1) Add\n";
  std::cout << "2) Subtract\n";
  std::cout << "3) Multiply\n";
  std::cout << "4) Exit\n";
  std::cout << "Enter your choice: ";
}

// Refactored getInput function that returns std::optional<int>
std::optional<int> getInput(const std::string &prompt) {
  std::string inputStr;
  int input;

  std::cout << prompt;
  std::getline(std::cin, inputStr); // Get the entire line as a string
  std::istringstream inputStream(
      inputStr); // Create a string stream for parsing

  // Try to extract an integer from the stream
  if (inputStream >> input) {
    return input; // Return valid input
  } else {
    std::cout << "Invalid input. Returning null." << std::endl;
    return std::nullopt; // Return null equivalent (std::nullopt)
  }
}

// Process the selected operation by the user
void processOperation(const std::function<int(int, int)> &operation) {
  std::optional<int> a = getInput("Enter the first number: ");
  std::optional<int> b = getInput("Enter the second number: ");

  // Check if both inputs are valid before proceeding
  if (a && b) {
    std::cout << "Result: " << operation(a.value(), b.value()) << "\n";
  } else {
    std::cout << "One or both inputs were invalid. Operation aborted.\n";
  }
}
