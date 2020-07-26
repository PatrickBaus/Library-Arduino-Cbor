/*
  Copyright 2014-2015 Stanislav Ovsyannikov
  Copyright 2018 Patrick Baus

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



#ifndef CBORDECODER_H
#define CBORDECODER_H

#include <stdint.h>    // uint8_t, etc.
#include <stdlib.h>    // size_t

typedef enum {
  STATE_TYPE,
  STATE_PINT,
  STATE_NINT,
  STATE_BYTES_SIZE,
  STATE_BYTES_DATA,
  STATE_STRING_SIZE,
  STATE_STRING_DATA,
  STATE_ARRAY,
  STATE_MAP,
  STATE_TAG,
  STATE_FLOAT,
  STATE_ERROR
} CborReaderState;

class CborInput {
  public:
    CborInput(void *data, const size_t size);

    bool hasBytes(const size_t count);
    unsigned char getByte();
    unsigned short getShort();
    uint32_t getInt();
    uint64_t getLong();
    void getBytes(void *to, const size_t count);
  private:
    unsigned char *data;
    size_t size;
    size_t offset;
};

class CborListener {
  public:
    virtual void OnInteger(int32_t value) = 0;
    virtual void OnBoolean(const bool value) = 0;
    virtual void OnBytes(unsigned char *data, const size_t size) = 0;
    virtual void OnString(const char *data, const size_t size) = 0;
    virtual void OnArray(unsigned int size) = 0;
    virtual void OnMap(unsigned int size) = 0;
    virtual void OnTag(uint32_t tag) = 0;
    virtual void OnSpecial(uint32_t code) = 0;
    virtual void OnError(const char *error) = 0;
    virtual void onNull() = 0;
    virtual void onFloat(const float value) = 0;
    virtual void onDouble(const double value) = 0;
    virtual void OnExtraInteger(uint64_t /*value*/, int8_t /*sign*/) {}
    virtual void OnExtraTag(uint64_t /*tag*/) {}
    virtual void OnExtraSpecial(uint64_t /*tag*/) {}
};

class CborDebugListener: public CborListener {
  public:
    void OnInteger(int32_t value) override;
    void OnBoolean(const bool value) override;
    void OnBytes(unsigned char *data, const size_t size) override {};
    void OnString(const char *data, const size_t size) override {};
    void OnArray(unsigned int size) override {};
    void OnMap(unsigned int size) override {};
    void OnTag(uint32_t tag) override {};
    void OnSpecial(uint32_t code) override {};
    void OnError(const char *error) override {};
    void onNull() override {};
    void onFloat(const float value) override {};
    void onDouble(const double value) override {};
    void OnExtraInteger(uint64_t value, int8_t sign) override;
    void OnExtraTag(uint64_t /*tag*/) override {}
    void OnExtraSpecial(uint64_t /*tag*/) override {}
};


class CborReader {
  public:
    CborReader(CborInput &input);
    CborReader(CborInput &input, CborListener &listener);
    void Run();
    void SetListener(CborListener &listener);
  private:
    CborListener *listener;
    CborInput *input;
    CborReaderState state;
    unsigned int currentLength;
};
#endif

