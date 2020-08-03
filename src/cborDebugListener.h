/*
  Copyright 2020 Patrick Baus

  Licensed under the Apache License, Version 2.0 (the "License");
  you may not use this file except in compliance with the License.
  You may obtain a copy of the License at

  http://www.apache.org/licenses/LICENSE-2.0

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License.
*/
#ifndef CBOR_DEBUG_LISTENER_H
#define CBOR_DEBUG_LISTENER_H


#include "cborDecoder.h"

class CborDebugListener: public CborListener {
  public:
    void OnInteger(int32_t value) override;
    void OnBoolean(const bool value) override;
    void OnBytes(unsigned char *data, const size_t size) override {};
    void OnString(const char *data, const size_t size) override {};
    void OnArray(unsigned int size) override {};
    void OnMap(unsigned int size) override {};
    void OnError(const char *error) override {};
    void OnFloat(const float value) override;
    void OnDouble(const double value) override;    void OnNull() override;
    void OnTag(uint32_t tag) override {};
    void OnSpecial(uint32_t code) override {};
    void OnUndefined() override;
    void OnExtraInteger(uint64_t value, int8_t sign) override;
    void OnExtraTag(uint64_t /*tag*/) override {}
    void OnExtraSpecial(uint64_t /*tag*/) override {}
};

#endif  // CBOR_DEBUG_LISTENER_H
