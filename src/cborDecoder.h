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
    uint8_t getByte();
    uint16_t getShort();
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
    virtual void OnInteger(const int32_t value) = 0;
    virtual void OnBoolean(const bool value) = 0;
    virtual void OnByteString(unsigned char *data, const size_t size) = 0;
    virtual void OnTextString(char *data, const size_t size) = 0;
    virtual void OnArray(const size_t size) = 0;
    virtual void OnMap(const size_t size) = 0;
    virtual void OnHalf(const uint16_t /*value*/) {};
    virtual void OnFloat(const float value) = 0;
    virtual void OnDouble(const double value) = 0;
    virtual void OnTag(const uint32_t /*tag*/) {};
    virtual void OnExtraTag(const uint64_t /*tag*/) {}
    virtual void OnNull() {};
    virtual void OnUndefined() {};
    virtual void OnExtraInteger(const uint64_t /*value*/, const int8_t /*sign*/) {}
    virtual void OnError(const char *error) = 0;
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
    uint8_t currentLength;
};
#endif    // CBORDECODER_H

