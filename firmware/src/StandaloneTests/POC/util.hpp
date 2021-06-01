#ifndef UTIL_H__
#define UTIL_H__

#include <Arduino.h>

#ifndef NODEBUG
    #define PRINT(x) Serial.println(x)
#endif

template <typename T>
static inline int8_t sgn(T val) {
  if (val < 0)
    return -1;
  if (val == 0)
    return 0;
  return 1;
}

#endif