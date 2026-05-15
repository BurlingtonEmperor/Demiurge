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
  FLAGX, // fx
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
  SET_ARR, // sa <-- set array to push to
  PUSH, // p <-- push values to preset array
  KEY_PROMPT, // kp
  SET_KEY, // se
  ENCRYPT, // e
  DECRYPT, // d
  TEXT_OCR, // to
  SET_MODEL, // sm
  SET_API_KEY, // sak
  LLM, // large language model, bytecode form is literally just llm!
  ILC, // iterative learning controller (sort of), bytecode form: ilc
  APM, // adaptive pattern matching, bytecode form: apm.
  WAIT, // w
  REPEAT, // r
  STOP, // !
  CLEAR, // _
  EXECUTE, // exe
  IF, // if
  ELSE,
  C, // <-- that's a comment indicator.
  PLAY_SOUND, // ps <-- native sound lib, not browser sound
  RUN_FUNC, // rf
  EDITOR_BG, // ebg, editor commands start here.
  EDITOR_FONT, // ef
  EDITOR_TEXT_COLOR, // etc
  EDITOR_BGIMG, // ebgi
  EDITOR_GLASS, // eg
  BLOCK_GLASS, // bg
  BLOCK_COLOR, // bc
  BLOCK_FONT, // bf
  BLOCK_TEXT_COLOR, // btc (Block text color, NOT BITCOIN!!)
  EDITOR_CSS, // ec, editor commands end here.
  DRAW_IMG, // di, canvas commands start here.
  CLEAR_CANVAS, // cc
  TEXT_X, 
  TEXT_Y, 
  WRITE_TEXT, // wt
  HTML_SOUND, // hs, canvas commands end here.
  UNDEFINED
};

enum class limited_tools {
  RANDOM_INT,
  RANDOM_FLOAT,
  ABSOLUTE_VALUE,
  FIND_LOWEST_IN_ARRAY,
  FIND_COMMON_IN_ARRAY
};

demiurge_commands_primary commandToEnum (const std::string& str) {
  static const std::unordered_map<std::string, demiurge_commands_primary> commandMap = {
    {"DISPLAY", demiurge_commands_primary::DISPLAY},
    {"FLAGX", demiurge_commands_primary::FLAGX},
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
    {"SET_ARR", demiurge_commands_primary::SET_ARR},
    {"PUSH", demiurge_commands_primary::PUSH},
    {"KEY_PROMPT", demiurge_commands_primary::KEY_PROMPT},
    {"SET_KEY", demiurge_commands_primary::SET_KEY},
    {"ENCRYPT", demiurge_commands_primary::ENCRYPT},
    {"DECRYPT", demiurge_commands_primary::DECRYPT},
    {"TEXT_OCR", demiurge_commands_primary::TEXT_OCR},
    {"SET_MODEL", demiurge_commands_primary::SET_MODEL},
    {"SET_API_KEY", demiurge_commands_primary::SET_API_KEY},
    {"LLM", demiurge_commands_primary::LLM},
    {"ILC", demiurge_commands_primary::ILC},
    {"APM", demiurge_commands_primary::APM},
    {"WAIT", demiurge_commands_primary::REPEAT},
    {"STOP", demiurge_commands_primary::STOP},
    {"CLEAR", demiurge_commands_primary::CLEAR},
    {"EXECUTE", demiurge_commands_primary::EXECUTE},
    {"C", demiurge_commands_primary::C},
    {"RUN_FUNC", demiurge_commands_primary::RUN_FUNC},
    {"PLAY_SOUND", demiurge_commands_primary::PLAY_SOUND},
    {"EDITOR_BG", demiurge_commands_primary::EDITOR_BG},
    {"EDITOR_BGIMG", demiurge_commands_primary::EDITOR_BGIMG},
    {"EDITOR_GLASS", demiurge_commands_primary::EDITOR_GLASS},
    {"EDITOR_FONT", demiurge_commands_primary::EDITOR_FONT},
    {"EDITOR_TEXT_COLOR", demiurge_commands_primary::EDITOR_TEXT_COLOR},
    {"EDITOR_CSS", demiurge_commands_primary::EDITOR_CSS},
    {"BLOCK_GLASS", demiurge_commands_primary::BLOCK_GLASS},
    {"BLOCK_COLOR", demiurge_commands_primary::BLOCK_COLOR},
    {"BLOCK_FONT", demiurge_commands_primary::BLOCK_FONT},
    {"BLOCK_TEXT_COLOR", demiurge_commands_primary::BLOCK_TEXT_COLOR},
    {"DRAW_IMG", demiurge_commands_primary::DRAW_IMG},
    {"CLEAR_CANVAS", demiurge_commands_primary::CLEAR_CANVAS},
    {"TEXT_X", demiurge_commands_primary::TEXT_X},
    {"TEXT_Y", demiurge_commands_primary::TEXT_Y},
    {"WRITE_TEXT", demiurge_commands_primary::WRITE_TEXT},
    {"HTML_SOUND", demiurge_commands_primary::HTML_SOUND},
  };

  auto it = commandMap.find(str);
  return (it != commandMap.end()) ? it->second : demiurge_commands_primary::UNDEFINED;
}

std::vector<std::string> variable_checking_array; // storing variables and check to see if a variable exists.
bool checkIfVariableExists (std::string variable_name) {
  for (int i = 0; i < variable_checking_array.size(); i++) {
    std::string var_data = variable_checking_array[i];
    std::vector<std::string> var_data_vector = splitByString(var_data, ":");
    std::string var_name = var_data_vector[2];

    if (variable_name == var_name) {
      return true;
    }
  }
  return false;
}

int getVariablePosition (std::string variable_name) {
  for (int i = 0; i < variable_checking_array.size(); i++) {
    std::string var_data = variable_checking_array[i];
    std::vector<std::string> var_data_vector = splitByString(var_data, ":");
    std::string var_name = var_data_vector[2];

    if (variable_name == var_name) {
      return i;
    }
  }
}

void addArrayToArray (std::string array_name, int array_type, std::string array_item) {
  if (checkIfVariableExists(array_name)) {
    std::string array_data = variable_checking_array[getVariablePosition(array_name)];
    std::vector<std::string> array_vector = splitByString(array_data, ":");

    std::string array_final_data = array_vector[3];
    // std::vector<std::string> array_final_vector = splitByString(array_data, ";");
    array_final_data = array_final_data + ";" + array_item;
  } else {
    std::string array_type_to_string = std::to_string(array_type);
    variable_checking_array.push_back("v:" + array_type_to_string + ":" + array_name + ":" + array_item);
  }
}

int main (int argc, char *argv[]) {
  if (argc != 2) {
    std::cout << "Demiurge can only accept 1 file path as an argument.";
    std::cin.get();
  } else {
    const std::string demiurge_filepath = argv[1];

    // std::string string_to_decipher;
    std::vector<std::string> seglist;
    std::vector<std::string> bytecode_vector;
    
    std::ifstream file(demiurge_filepath);
    std::string line;

    if (file.is_open()) {
      while (std::getline(file, line)) {
        seglist.push_back(line);
      }
      file.close();

      int compileMode = 0; // produces an exe (default)

      int compilerError = 0; // checks for an error
      int compilerErrorType = 0; 
      int compilerErrorLine = 0; // what line is it on?
      /* 
      0 - syntax error
      1 - undefined error
      2 - type error
      3 - reference error
      */
      std::string compilerErrorMsg = "";

      std::string target_array_name = "";
      int target_array_type = 0; // 0 = int arr, 1 = float arr, 2 = long arr, 3 = bool arr, 4 = string arr

      int target_text_x = 0;
      int target_text_y = 0;

      for (int i = 0; i < seglist.size(); i++) {
        if (compilerError == 1) {
          compilerErrorLine = i;
          break;
        }

        std::string individual_line = seglist[i];
        if (individual_line.empty()) continue;

        auto it = std::unique(individual_line.begin(), individual_line.end(), [](char a, char b) {
          return (a == ' ' && b == ' ');
        });
        individual_line.erase(it, individual_line.end()); // remove extra whitespace
        replaceAll(individual_line, ":", "<colon>"); // remove reserved chars
        std::vector<std::string> space_limiter = splitBySpaces(individual_line);

        demiurge_commands_primary convertedCommand = commandToEnum(toUpperCase(space_limiter[0]));

        std::vector<std::string> space_clone = space_limiter;
        space_clone.erase(space_clone.begin());
        
        std::string space_clone_final = joinVectorItems_string(space_clone);

        std::string secondary_argument = (space_limiter.size() > 1) ? space_limiter[1] : "0";
        std::string third_argument = (space_limiter.size() > 2) ? space_limiter[2] : "0";

        int only_taking_one_arg = 0; // checks to see if the command only takes one argument, default (0) means no

        switch (convertedCommand) {
          case (demiurge_commands_primary::FLAGX):
            // yes this is kind of a bad way to do this, but I want to get this done fast
            if (secondary_argument == "E") compileMode = 1; // produce exe
            if (secondary_argument == "H") compileMode = 2; // produce standalone html file 
            if (secondary_argument == "B") compileMode = 3; // produce binary file (bytecode)
            if (secondary_argument == "T") compileMode = 4; // produce editor theme (also bytecode)

            only_taking_one_arg = 1;
            break;
          case (demiurge_commands_primary::DISPLAY):
            bytecode_vector.push_back("d:" + space_clone_final); 
            break;
          case (demiurge_commands_primary::ACCEPT):
            bytecode_vector.push_back(">:" + space_clone_final);
            break;
          case (demiurge_commands_primary::INT): { // check if it's actually an int!
            only_taking_one_arg = 2;
            if (checkIfVariableExists(secondary_argument)) {
              compilerError = 1;
              compilerErrorType = 3;
              compilerErrorMsg = "Attempted to redeclare a pre-existing variable: " + secondary_argument;
            } else {
              if (is_number(third_argument)) {
                variable_checking_array.push_back("v:i:" + secondary_argument + ":" + third_argument);
              }  else {
                compilerError = 1;
                compilerErrorType = 2;
                compilerErrorMsg = "The value passed to the <int> variable is not a number";
              }
            }
            break;
          }
          case (demiurge_commands_primary::FLOAT): {
            only_taking_one_arg = 2;
            if (checkIfVariableExists(secondary_argument)) {
              compilerError = 1;
              compilerErrorType = 3;
              compilerErrorMsg = "Attempted to redeclare a pre-existing variable: " + secondary_argument;
            } else {
              if (is_number(third_argument)) {
                variable_checking_array.push_back("v:f:" + secondary_argument + ":" + third_argument);
              } else {
                compilerError = 1;
                compilerErrorType = 2;
                compilerErrorMsg = "The value passed to the <float> variable is not a number";
              } 
            }
            break;
          }
          case (demiurge_commands_primary::LONG): {
            only_taking_one_arg = 2;
            if (checkIfVariableExists(secondary_argument)) {
              compilerError = 1;
              compilerErrorType = 3;
              compilerErrorMsg = "Attempted to redeclare a pre-existing variable";
            } else {
              if (is_number(third_argument)) {
                variable_checking_array.push_back("v:l:" + secondary_argument + ":" + third_argument);
              } else {
                compilerError = 1;
                compilerErrorType = 2;
                compilerErrorMsg = "The value passed to the <long> variable is not a number";
              } 
            }
            break;
          }
          case (demiurge_commands_primary::BOOL): 
            if (third_argument == "TRUE") bytecode_vector.push_back("_v_b" + secondary_argument + ":t");
            if (third_argument == "FALSE") bytecode_vector.push_back("_v_b" + secondary_argument + ":f");

            only_taking_one_arg = 1;
            break;
          case (demiurge_commands_primary::STRING):
            if (checkIfVariableExists(secondary_argument)) {
              compilerError = 1;
              compilerErrorType = 3;
              compilerErrorMsg = "Attempted to redeclare a pre-existing variable: " + secondary_argument;
            } else {
              variable_checking_array.push_back("v:s:" + space_clone_final);
            }
            break;
          case (demiurge_commands_primary::INT_ARR):
            if (checkIfVariableExists(secondary_argument)) {
              compilerError = 1;
              compilerErrorType = 3;
              compilerErrorMsg = "Attempted to redeclare a pre-existing variable: " + secondary_argument;
            }
            target_array_name = secondary_argument;
            target_array_type = 0;
            break;
          case (demiurge_commands_primary::FLOAT_ARR):
            if (checkIfVariableExists(secondary_argument)) {
              compilerError = 1;
              compilerErrorType = 3;
              compilerErrorMsg = "Attempted to redeclare a pre-existing variable: " + secondary_argument;
            }
            target_array_name = secondary_argument;
            target_array_type = 1;
            break;
          case (demiurge_commands_primary::LONG_ARR):
            if (checkIfVariableExists(secondary_argument)) {
              compilerError = 1;
              compilerErrorType = 3;
              compilerErrorMsg = "Attempted to redeclare a pre-existing variable: " + secondary_argument;
            }
            target_array_name = secondary_argument;
            target_array_type = 2;
            break;
          case (demiurge_commands_primary::BOOL_ARR):
            if (checkIfVariableExists(secondary_argument)) {
              compilerError = 1;
              compilerErrorType = 3;
              compilerErrorMsg = "Attempted to redeclare a pre-existing variable: " + secondary_argument;
            }
            target_array_name = secondary_argument;
            target_array_type = 3;
            break;
          case (demiurge_commands_primary::STRING_ARR):
            if (checkIfVariableExists(secondary_argument)) {
              compilerError = 1;
              compilerErrorType = 3;
              compilerErrorMsg = "Attempted to redeclare a pre-existing variable: " + secondary_argument;
            }
            target_array_name = secondary_argument;
            target_array_type = 4;
            break;
          case (demiurge_commands_primary::SET_ARR):
            if (checkIfVariableExists(secondary_argument)) {
              target_array_name = secondary_argument;
            } else {
              compilerError = 1;
              compilerErrorType = 1;
              compilerErrorMsg = "Array \"" + secondary_argument + "\" not found";
            }
            break;
          case (demiurge_commands_primary::PUSH): { // wip
            only_taking_one_arg = 1;

            if (target_array_name == "") {
              compilerError = 1;
              compilerErrorType = 3;
              compilerErrorMsg = "Target array hasn't been set";
            } else {
              switch (target_array_type) {
                case 0:
                case 1:
                case 2:
                  if (is_number(secondary_argument)) {
                    addArrayToArray(target_array_name, target_array_type, secondary_argument);
                  } else {
                    compilerError = 1;
                    compilerErrorType = 2;
                    compilerErrorMsg = "Attempted to pass a non-number into a number array (int, float, bool)";
                  }
                  break;
                case 3:
                  if ((secondary_argument == "TRUE") || (secondary_argument == "FALSE")) {
                    addArrayToArray(target_array_name, target_array_type, secondary_argument);
                  } else {
                    compilerError = 1;
                    compilerErrorType = 2;
                    compilerErrorMsg = "Attempted to pass a non-boolean into a boolean array";
                  }
                  break;
              }
              // if (!checkIfVariableExists(target_array_name)) {
              //   switch (target_array_type) {
              //     case 0:
              //     case 1:
              //     case 2:
              //       if (is_number(secondary_argument)) {
                      
              //       } else {
              //         compilerError = 1;
              //         compilerErrorType = 2;
              //         compilerErrorMsg = "Attempted to pass a non-number into a number array (int, float, bool)";
              //       }
              //       break;
              //     case 3:
              //       if ((secondary_argument == "TRUE") || (secondary_argument == "FALSE")) {
                      
              //       } else {
                      
              //       }
              //       break;
              //   }
              // } else {
                
              // }
            }
            break; 
          }
          case (demiurge_commands_primary::SET_KEY):
            bytecode_vector.push_back("se:" + secondary_argument);
            only_taking_one_arg = 1;
            break;
          case (demiurge_commands_primary::ENCRYPT): {
            bytecode_vector.push_back("e:" + space_clone_final);
            break;
          }
          case (demiurge_commands_primary::DECRYPT): 
            bytecode_vector.push_back("d:" + space_clone_final);
            break;
          case (demiurge_commands_primary::TEXT_OCR):
            bytecode_vector.push_back("to:" + space_clone_final);
            break;
          case (demiurge_commands_primary::SET_MODEL):
            bytecode_vector.push_back("sm:" + secondary_argument);
            only_taking_one_arg = 1;
            break;
          case (demiurge_commands_primary::SET_API_KEY):
            bytecode_vector.push_back("sak:" + secondary_argument);
            only_taking_one_arg = 1;
            break;
          case (demiurge_commands_primary::KEY_PROMPT):
            bytecode_vector.push_back("kp");
            break;
          case (demiurge_commands_primary::LLM):
            bytecode_vector.push_back("llm:" + space_clone_final);
            break;
          case (demiurge_commands_primary::ILC): {
            if (secondary_argument == "0" || third_argument == "0") {
              compilerError = 1;
              compilerErrorType = 0;

              if (secondary_argument == "0") compilerErrorMsg = "Missing argument for data storage array length";
              if (third_argument == "0") compilerErrorMsg = "Missing argument for desired error percentage";
            } else {
              
            }
            break;
          }
          case (demiurge_commands_primary::STOP): 
            bytecode_vector.push_back("!");
            break;
          case (demiurge_commands_primary::CLEAR):
            bytecode_vector.push_back("_");
            break;
          case (demiurge_commands_primary::RUN_FUNC):
            only_taking_one_arg = 1;
            bytecode_vector.push_back("rf:" + secondary_argument);
            break;
          case (demiurge_commands_primary::PLAY_SOUND):
            only_taking_one_arg = 1;
            bytecode_vector.push_back("ps:" + secondary_argument);
            break;
          case (demiurge_commands_primary::EDITOR_BG):
            only_taking_one_arg = 1;
            bytecode_vector.push_back("ebg:" + secondary_argument);
            break;
          case (demiurge_commands_primary::EDITOR_FONT):
            only_taking_one_arg = 1;
            bytecode_vector.push_back("ef:" + secondary_argument);
            break;
          case (demiurge_commands_primary::EDITOR_TEXT_COLOR):
            only_taking_one_arg = 1;
            bytecode_vector.push_back("etc:" + secondary_argument);
            break;
          case (demiurge_commands_primary::EDITOR_BGIMG):
            only_taking_one_arg = 1;
            bytecode_vector.push_back("ebgi:" + secondary_argument);
            break;
          case (demiurge_commands_primary::EDITOR_GLASS):
            only_taking_one_arg = 1;
            bytecode_vector.push_back("eg:" + secondary_argument);
            break;
          case (demiurge_commands_primary::BLOCK_GLASS):
            only_taking_one_arg = 1;
            bytecode_vector.push_back("bg:" + secondary_argument);
            break;
          case (demiurge_commands_primary::BLOCK_COLOR):
            only_taking_one_arg = 1;
            bytecode_vector.push_back("bc:" + secondary_argument);
            break;
          case (demiurge_commands_primary::BLOCK_FONT):
            only_taking_one_arg = 1;
            bytecode_vector.push_back("bf:" + secondary_argument);
            break;
          case (demiurge_commands_primary::BLOCK_TEXT_COLOR):
            only_taking_one_arg = 1;
            bytecode_vector.push_back("btc:" + secondary_argument);
            break;
          case (demiurge_commands_primary::EDITOR_CSS):
            bytecode_vector.push_back("ec:" + space_clone_final);
            break;
          case (demiurge_commands_primary::DRAW_IMG):
            only_taking_one_arg = 1;
            bytecode_vector.push_back("di:" + secondary_argument);
            break;
          case (demiurge_commands_primary::CLEAR_CANVAS):
            bytecode_vector.push_back("cc");
            break;
          case (demiurge_commands_primary::TEXT_X): {
            only_taking_one_arg = 1;
            target_text_x = std::stoi(secondary_argument);
            break;
          }
          case (demiurge_commands_primary::TEXT_Y): {
            only_taking_one_arg = 1;
            target_text_y = std::stoi(secondary_argument);
          }
          case (demiurge_commands_primary::WRITE_TEXT): {
            std::string text_x = std::to_string(target_text_x);
            std::string text_y = std::to_string(target_text_y);
            bytecode_vector.push_back("wt:" + text_x + ":" + text_y + ":" + space_clone_final);
            break;
          }
          case (demiurge_commands_primary::HTML_SOUND): {
            only_taking_one_arg = 1;
            bytecode_vector.push_back("hs:" + secondary_argument);
            break;
          }
          case (demiurge_commands_primary::UNDEFINED):
            compilerError = 1;
            compilerErrorType = 1;
            compilerErrorMsg = "Primary command is undefined";
            break;
        }

        switch (only_taking_one_arg) {
          case 1:
            break;
          case 2:
            break;
        }
      }
    } else {
      std::cout << "Unable to open file. It may not exist." << std::endl;
      std::cin.get();
    }
  }

  return 0;
}