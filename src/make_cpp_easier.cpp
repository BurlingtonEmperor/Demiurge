/*
Make C++ Easier!

This is a library I made for another project (EatCrow2) to make C++ less complicated 
and easier to use. Turns out it comes in real handy for a lot of other projects too.
Even if you don't end up using Demiurge, you can at least use the libraries I've made to
make it for your own C++ projects.
*/

#include <string>
#include <sstream>
#include <vector>
#include <iostream>
#include <fstream>
#include <chrono>
#include <ranges>
#include <numeric>

#include "make_cpp_easier.h"

void console_log(std::string str) { // this function mimics the JavaScript console.log() function
  std::cout << str;
}

// this function is basically the JavaScript .replaceAll function
/*
Usage: replaceAll(myString, substringToReplace, newSubstring);
*/
void replaceAll(std::string& str, const std::string& from, const std::string& to) {
  size_t start_pos = 0;
  while((start_pos = str.find(from, start_pos)) != std::string::npos) {
    str.replace(start_pos, from.length(), to);
    start_pos += to.length(); 
  }
}

void shiftFloatArray(float (&array_to_shift)[20], float new_value) {
  for (int i = 19; i > 0; i--) {
    array_to_shift[i] = array_to_shift[i - 1];
  }
  array_to_shift[0] = new_value;
}

bool checkIncludes(std::string text, const std::string substring) { // this function checks to see if a string contains a substring.
  return text.find(substring) != std::string::npos;
}

bool is_number(const std::string& s) {
  std::istringstream iss(s);
  double d;
  return iss >> std::noskipws >> d && iss.eof();
}

int findLowestInArray(float (&array_to_check)[20]) { // finds lowest value in a float array and returns its position.
  float lowest_value = array_to_check[0];
  int lowest_position = 0;

  for (int i = 1; i < 20; i++) {
    if (array_to_check[i] < lowest_value) {
      lowest_value = array_to_check[i];
      lowest_position = i;
    }
  }
  return lowest_position;
}

// float absoluteValue(float value_to_check) {
//   if (value_to_check < 0.0f) {
//     return (value_to_check * (-1.0f));
//   } else {
//     return value_to_check;
//   }
// }

std::vector<std::string> splitByString(const std::string& str, const std::string& delimiter) { // this function splits a string using a delimiter and returns a vector
  std::vector<std::string> tokens;
  size_t start = 0;
  size_t end = str.find(delimiter);

  while (end != std::string::npos) {
    tokens.push_back(str.substr(start, end - start));
    start = end + delimiter.length(); // Move start past the delimiter
    end = str.find(delimiter, start);
  }

  tokens.push_back(str.substr(start));
  return tokens;
}

std::vector<std::string> splitBySpaces(const std::string& str) { // this function splits a string using spaces, but ignores extra whitespace!
  std::stringstream ss(str);
  std::string word;
  std::vector<std::string> words;

  while (ss >> word) {
    words.push_back(word);
  }

  return words;
}

std::string joinVectorItems_string(std::vector<std::string>& str_vector) { // joins by spaces
  std::string joined = "";
  for (size_t i = 0; i < str_vector.size(); ++i) {
    joined += str_vector[i];
    if (i < str_vector.size() - 1) {
        joined += " "; 
    }
  }
  return joined;
}

std::string joinVectorItems_string_substring(const std::vector<std::string>& vec, const std::string& delimiter) {
  if (vec.empty()) return "";
    
  std::string res = vec[0];
  for (size_t i = 1; i < vec.size(); ++i) {
    res += delimiter + vec[i]; 
  }
  return res;
}

std::string toUpperCase(std::string& str) { // this function converts a string to all uppercase and returns it.
  for (char &c : str) {
    c = std::toupper(static_cast<unsigned char>(c));
  }
  return str;
}

std::string get_file_contents(const std::string& filename) { // gets file contents and puts it all into one string, then returns it.
  std::ifstream file(filename);
  if (!file.is_open()) return ""; 

  std::stringstream buffer;
  buffer << file.rdbuf();
  return buffer.str();
}