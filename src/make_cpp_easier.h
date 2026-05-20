#ifndef MAKE_CPP_EASIER_H
#define MAKE_CPP_EASIER_H

#include <string>
#include <sstream>
#include <vector>
#include <iostream>
#include <fstream>
#include <chrono>
#include <ranges>
#include <numeric>

void replaceAll(std::string& str, const std::string& from, const std::string& to);
void console_log(std::string& str);
void shiftFloatArray(float (&array_to_shift)[20], float new_value); 

bool checkIncludes(std::string& text, const std::string& substring);
bool is_number(const std::string& s);

// int convertBoolToInt(bool& bool_value);
int findLowestInArray(float (&array_to_check)[20]);

std::vector<std::string> splitByString(const std::string& str, const std::string& delimiter);
std::vector<std::string> splitBySpaces(const std::string& str);

std::string joinVectorItems_string(std::vector<std::string>& str_vector);
std::string joinVectorItems_string_substring(const std::vector<std::string>& vec, const std::string& delimiter);
std::string toUpperCase(std::string& str);
std::string get_file_contents(const std::string& filename);

#endif