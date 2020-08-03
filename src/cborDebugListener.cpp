#include <Arduino.h>

#include "cborDebugListener.h"

void CborDebugListener::OnInteger(int32_t value) {
  Serial.print("Integer: ");
  Serial.println(value);
}

void CborDebugListener::OnFloat(float value) {
  Serial.print("Float: ");
  Serial.println(value);
}

void CborDebugListener::OnDouble(double value) {
  Serial.print("Double: ");
  Serial.println(value);
}

void CborDebugListener::OnBoolean(const bool value) {
  Serial.print("Boolean: ");
  Serial.println(value);
}

void CborDebugListener::OnNull() {
  Serial.println("Null");
}

void CborDebugListener::OnUndefined() {
  Serial.println("Undefined");
}

void CborDebugListener::OnExtraInteger(uint64_t value, int8_t sign) {
  Serial.print("Extra integer: ");
  #ifndef CORE_TEENSY
  sign == -1 ? Serial.println(-(int64_t)value): Serial.println(value);
  #endif
}
