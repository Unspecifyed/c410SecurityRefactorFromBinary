// calculator.h
#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <functional>
#include <string>

int add(int a, int b);
int subtract(int a, int b);
int multiply(int a, int b);
int getInput(const std::string &prompt);
void processOperation(const std::function<int(int, int)> &operation);
void displayMenu();

#endif // CALCULATOR_H
