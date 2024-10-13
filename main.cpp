// main.cpp
#include "calculator.h"
#include <functional>
#include <iostream>
#include <unordered_map>

int main() {
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
