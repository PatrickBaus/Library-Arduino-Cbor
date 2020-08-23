#include <Arduino.h>

#include "cborDebugListener.h"

void CborDebugListener::OnInteger(const int32_t value) {
  Serial.print("Integer: ");
  Serial.println(value);
}

void CborDebugListener::OnFloat(const float value) {
  Serial.print("Float: ");
  Serial.println(value);
}

void CborDebugListener::OnDouble(const double value) {
  Serial.print("Double: ");
  Serial.println(value);
}

void CborDebugListener::OnBoolean(const bool value) {
  Serial.print("Boolean: ");
  Serial.println(value);
}

void OnByteString(unsigned char *, const size_t size) {
  Serial.print("Byte string of size: ");
  Serial.println(size);
};

void OnTextString(char *, const size_t size) {
  Serial.print("UTF-8 string of size: ");
  Serial.println(size);
};

void OnArray(const size_t size) {
  Serial.print("Begin of array of size: ");
  Serial.println(size);
};

void OnMap(const size_t size) {
  Serial.print("Begin of map of size: ");
  Serial.println(size);
};

void CborDebugListener::OnNull() {
  Serial.println("Null");
}

void CborDebugListener::OnUndefined() {
  Serial.println("Undefined");
}

void CborDebugListener::OnExtraInteger(const uint64_t value, const int8_t sign) {
  Serial.print("Extra integer: ");
  #ifndef CORE_TEENSY
  sign == -1 ? Serial.println(-(int64_t)value): Serial.println(value);
  #endif
}
