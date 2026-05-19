#include <string>
#include <sstream>
#include <vector>
#include <iostream>
#include <fstream>
#include <chrono>
#include <ranges>
#include <numeric>
#include <variant>
#include <unordered_map>

#include "make_cpp_easier.h"
#include "demiurge_vm.h"

using VariableValue = std::variant<int, double, std::string, bool>; 
struct VariableSymbol {
    std::string dataType; // "integer", "float", "string", "boolean"
    VariableValue value;  // val
    bool isConstant;      // const or let, essentially
};
std::unordered_map<std::string, VariableSymbol> symbolTable; // declare new variable storage

int main () {
  return 0;
}