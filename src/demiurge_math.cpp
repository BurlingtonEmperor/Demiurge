#include "demiurge_math.h"

// floats
float absoluteValue (float value_to_check) {
  if (value_to_check < 0.0f) {
    return (value_to_check * (-1.0f));
  } else {
    return value_to_check;
  }
}

float convertIntToFloat (int int_to_convert) {
  float converted_int = static_cast<float>(int_to_convert);
  return converted_int;
}
// end floats

// ints
int convertFloatToInt (float float_to_convert) {
  int converted_float = static_cast<int>(float_to_convert);
  return converted_float;
}
// end ints

// non-number to number conversions
int convertBoolToInt(bool bool_value) { // this function converts a boolean to an integer (for switch statements); 1 = true and 0 = false
  if (bool_value) {
    return 1;
  } else {
    return 0;
  }
}
// end