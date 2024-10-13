// calculator.h
#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <functional>
#include <optional> // Include optional for std::optional
#include <string>

int add(int a, int b);
int subtract(int a, int b);
int multiply(int a, int b);
std::optional<int>
getInput(const std::string &prompt); // Updated to std::optional
void processOperation(const std::function<int(int, int)> &operation);
void displayMenu();

#endif // CALCULATOR_H
