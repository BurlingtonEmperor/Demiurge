#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <ranges>
#include <unordered_map>

#include "make_cpp_easier.h"
#include "demiurge_math.h"

enum class variable_types {
  INT, // bytecode form: i
  FLOAT, // f
  LONG, // l
  BOOL, // b
  STRING, // s
  INT_ARR, // ia
  FLOAT_ARR, // fa
  STRING_ARR, // sa
  LONG_ARR, // la
  BOOL_ARR // ba
};

enum class demiurge_commands_primary {
  DISPLAY, // bytecode form: d
  ACCEPT, // >
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
  KEY_PROMPT, // kp
  ENCRYPT, // e
  DECRYPT, // d
  TEXT_OCR, // to
  LLM, // large language model,
  ILC, // iterative learning controller (sort of)
  APM, // adaptive pattern matching
  WAIT, // w
  REPEAT, // r
  STOP, // !
  CLEAR, // _
  EXECUTE, 
  C, // <-- that's a comment indicator.
  PLAY_SOUND,
  EDITOR_BG, // the editor commands start here.
  EDITOR_FONT,
  EDITOR_TEXT_COLOR,
  EDITOR_BGIMG,
  EDITOR_GLASS,
  BLOCK_GLASS,
  BLOCK_COLOR,
  BLOCK_FONT,
  BLOCK_TEXT_COLOR,
  EDITOR_CSS, // editor commands end here.
  DRAW_IMG, // canvas commands start here.
  CLEAR_CANVAS,
  WRITE_TEXT,
  HTML_SOUND,
  UNDEFINED
};

enum class limited_tools {
  RANDOM_INT,
  RANDOM_FLOAT,
  ABSOLUTE_VALUE,
  FIND_LOWEST_IN_ARRAY,
  FIND_COMMON_IN_ARRAY
};

demiurge_commands_primary stringToEnum(const std::string& str) {
  static const std::unordered_map<std::string, demiurge_commands_primary> commandMap = {
    {"DISPLAY", demiurge_commands_primary::DISPLAY},
    {"ACCEPT", demiurge_commands_primary::ACCEPT},
    {"INT", demiurge_commands_primary::INT},
    {"FLOAT", demiurge_commands_primary::FLOAT},
    {"LONG", demiurge_commands_primary::LONG},
    {"BOOL", demiurge_commands_primary::BOOL},
    {"STRING", demiurge_commands_primary::STRING},
    {"INT_ARR", demiurge_commands_primary::INT_ARR},
    {"FLOAT_ARR", demiurge_commands_primary::FLOAT_ARR},
    {"STRING_ARR", demiurge_commands_primary::STRING_ARR},
    {"LONG_ARR", demiurge_commands_primary::LONG_ARR},
    {"BOOL_ARR", demiurge_commands_primary::BOOL_ARR},
    {"KEY_PROMPT", demiurge_commands_primary::KEY_PROMPT},
    {"ENCRYPT", demiurge_commands_primary::ENCRYPT},
    {"DECRYPT", demiurge_commands_primary::DECRYPT},
    {"TEXT_OCR", demiurge_commands_primary::TEXT_OCR},
    {"LLM", demiurge_commands_primary::LLM},
    {"ILC", demiurge_commands_primary::ILC},
    {"APM", demiurge_commands_primary::APM},
    {"WAIT", demiurge_commands_primary::REPEAT},
    {"STOP", demiurge_commands_primary::STOP},
    {"CLEAR", demiurge_commands_primary::CLEAR},
    {"EXECUTE", demiurge_commands_primary::EXECUTE},
    {"C", demiurge_commands_primary::C},
    {"PLAY_SOUND", demiurge_commands_primary::PLAY_SOUND},
    {"EDITOR_BG", demiurge_commands_primary::EDITOR_BG},
    {"EDITOR_FONT", demiurge_commands_primary::EDITOR_FONT},
    {"EDITOR_TEXT_COLOR", demiurge_commands_primary::EDITOR_TEXT_COLOR},
    {"EDITOR_CSS", demiurge_commands_primary::EDITOR_CSS},
    {"DRAW_IMG", demiurge_commands_primary::DRAW_IMG}
  };

  auto it = commandMap.find(str);
  return (it != commandMap.end()) ? it->second : demiurge_commands_primary::UNDEFINED;
}

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

        std::vector<std::string> space_limiter = splitBySpaces(individual_line);
      }
    } else {
      std::cout << "Unable to open file. It may not exist." << std::endl;
      std::cin.get();
    }
  }

  return 0;
}