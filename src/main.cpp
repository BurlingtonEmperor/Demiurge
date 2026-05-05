#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <ranges>

#include "make_cpp_easier.h"
#include "demiurge_math.h"

enum class variable_types {
  INT, 
  FLOAT,
  LONG,
  BOOL,
  STRING,
  INT_ARR,
  FLOAT_ARR,
  STRING_ARR,
  LONG_ARR,
  BOOL_ARR
};

enum class demiurge_commands_primary {
  DISPLAY,
  ACCEPT,
  INT,
  FLOAT,
  LONG,
  BOOL,
  STRING,
  INT_ARR,
  FLOAT_ARR,
  STRING_ARR,
  LONG_ARR,
  BOOL_ARR,
  KEY_PROMPT,
  ENCRYPT,
  DECRYPT,
  TEXT_OCR,
  WAIT,
  REPEAT,
  STOP,
  CLEAR,
  EXECUTE,
  EDITOR_BG, // the editor commands start here.
  EDITOR_FONT,
  EDITOR_TEXT_COLOR,
  EDITOR_BGIMG,
  EDITOR_GLASS,
};

enum class limited_tools {
  RANDOM_INT,
  RANDOM_FLOAT,
  ABSOLUTE_VALUE
};

std::string string_to_decipher;

int main (int argc, char *argv[]) {
  if (argc != 2) {
    std::cout << "Demiurge can only accept 1 file path as an argument.";
    std::cin.get();
  } else {
    const std::string demiurge_filepath = argv[1];
    
    std::ifstream file(demiurge_filepath);
    std::string line;

    if (file.is_open()) {
      while (std::getline(file, line)) {
        string_to_decipher += line;
      }
      file.close();

      replaceAll(string_to_decipher, ";\"", "<semi>\""); // make sure that statement terminators aren't just strings.
      replaceAll(string_to_decipher, ";\'", "<semi>\'");

      std::vector<std::string> seglist = splitByString(string_to_decipher, ";");
      std::vector<std::string> bytecode_vector;

      for (int i = 0; i < seglist.size(); i++) {
        std::string individual_line = seglist[i];
        if (individual_line.empty()) continue;

        
      }
    } else {
      std::cout << "Unable to open file. It may not exist." << std::endl;
      std::cin.get();
    }
  }

  return 0;
}