#ifndef MAIN_H
#define MAIN_H

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <ranges>
#include <unordered_map>
#include <numeric>

#include "make_cpp_easier.h"

extern std::string string_to_decipher;
extern std::vector<std::string> variable_checking_array;

bool checkIfVariableExists (std::string variable_name);

#endif