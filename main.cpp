#include "calculator.h"
#include <functional>
#include <iostream>
#include <optional> // Required for std::optional
#include <unordered_map>

int main() {
  std::unordered_map<int, std::function<int(int, int)>> operations = {
      {1, add}, {2, subtract}, {3, multiply}};

  while (true) {
    displayMenu();

    // Use the refactored getInput function which returns std::optional<int>
    std::optional<int> choice = getInput("");

    // Check if the input is valid
    if (!choice) {
      std::cout << "Invalid input. Please try again.\n";
      continue; // Skip this loop iteration if input is invalid
    }

    // If valid and the user chooses to exit
    if (choice == 4) {
      std::cout << "Exiting...\n";
      break;
    }

    // Check if the choice is in the available operations
    if (operations.find(choice.value()) != operations.end()) {
      processOperation(operations[choice.value()]);
    } else {
      std::cout << "Invalid choice. Try again.\n";
    }
  }

  return 0;
}
