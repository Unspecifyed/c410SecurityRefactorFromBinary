// main.cpp
#include "calculator.h"
#include <iostream>
#include <limits>
#include <sstream>
#include <stdexcept>
#include <unordered_map>

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

int getInput(const std::string &prompt) {
  std::string inputStr;
  int input;

  while (true) {
    try {
      std::cout << prompt;
      std::getline(std::cin, inputStr); // Get entire line as a string
      std::istringstream inputStream(
          inputStr); // Create a string stream for parsing

      // Try to extract an integer from the stream
      if (!(inputStream >> input)) {
        throw std::invalid_argument("Invalid input. Please enter a number.");
      }

      return input;
    } catch (const std::exception &e) {
      std::cout << e.what() << std::endl;
    }
  }
}

void processOperation(const std::function<int(int, int)> &operation) {
  int a = getInput("Enter the first number: ");
  int b = getInput("Enter the second number: ");
  std::cout << "Result: " << operation(a, b) << "\n";
}

int main(int argc, char **argv) { 
  std::unordered_map<int, std::function<int(int, int)>> operations = {
      {1, add}, {2, subtract}, {3, multiply}};

  while (true) {
    displayMenu();
    int choice = getInput("");

    if (choice == 4) {
      std::cout << "Exiting...\n";
      break;
    }

    if (operations.find(choice) != operations.end()) {
      processOperation(operations[choice]);
    } else {
      std::cout << "Invalid choice. Try again.\n";
    }
  }

  return 0;
}
