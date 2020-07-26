#include "cborEncoder.h"
#include "Arduino.h"


CborStaticOutput::CborStaticOutput(unsigned char* _buffer, const unsigned int _size, const unsigned int _offset): buffer(_buffer), capacity(_size), offset(_offset), cursor(_offset) {}


void CborStaticOutput::putByte(const unsigned char value) {
  if (this->cursor < this->capacity) {
    buffer[this->cursor++] = value;
  } else {
//    Serial.print("buffer overflow error");
  }
}

void CborStaticOutput::putBytes(const unsigned char *data, const unsigned int size) {
  if (cursor + size <= capacity) {
    memcpy(buffer + this->cursor, data, size);
    this->cursor += size;
  } else {
//    Serial.print("buffer overflow error");
  }
}


CborWriter::CborWriter(CborOutput &output) {
  this->output = &output;
}

CborWriter::~CborWriter() {

}


unsigned char *CborStaticOutput::getData() {
  return buffer;
}

unsigned int CborStaticOutput::getSize() {
  return this->cursor;
}

void CborStaticOutput::resetBuffer() {
  this->cursor = this->offset;
}


CborDynamicOutput::CborDynamicOutput(const uint32_t initalCapacity) {
  init(initalCapacity);
}

CborDynamicOutput::~CborDynamicOutput() {
  delete[] buffer;
}

void CborDynamicOutput::init(unsigned int initalCapacity) {
  this->capacity = initalCapacity;
  this->buffer = new unsigned char[initalCapacity];
  this->offset = 0;
}


unsigned char *CborDynamicOutput::getData() {
  return buffer;
}

unsigned int CborDynamicOutput::getSize() {
  return offset;
}

void CborDynamicOutput::putByte(const unsigned char value) {
  if (offset < capacity) {
    buffer[offset++] = value;
  } else {
    capacity *= 2;
    buffer = (unsigned char *) realloc(buffer, capacity);
    buffer[offset++] = value;
  }
}

void CborDynamicOutput::putBytes(const unsigned char *data, const unsigned int size) {
  while(offset + size > capacity) {
    capacity *= 2;
    buffer = (unsigned char *) realloc(buffer, capacity);
  }

  memcpy(buffer + offset, data, size);
  offset += size;
}

void CborWriter::writeTypeAndValue(uint8_t majorType, const uint32_t value) {
  majorType <<= 5;  // Make size for the length filed (5 bytes, additional type value)
  if (value < 24) {
    output->putByte(majorType | value);
  } else if (value < 256) {
    output->putByte(majorType | 24);  // 24 = next byte is uint8_t
    output->putByte(value);
  } else if (value < 65536) {
    output->putByte(majorType | 25);
    output->putByte(value >> 8);
    output->putByte(value);
  } else {
    output->putByte(majorType | 26);
    output->putByte(value >> 24);
    output->putByte(value >> 16);
    output->putByte(value >> 8);
    output->putByte(value);
  }
}

void CborWriter::writeTypeAndValue(uint8_t majorType, const uint64_t value) {
  majorType <<= 5;
  if (value < 24ULL) {
    output->putByte(majorType | value);
  } else if (value < 256ULL) {
    output->putByte(majorType | 24);
    output->putByte(value);
  } else if (value < 65536ULL) {
    output->putByte(majorType | 25);
    output->putByte(value >> 8);
    output->putByte(value);
  } else if (value < 4294967296ULL) {
    output->putByte(majorType | 26);
    output->putByte(value >> 24);
    output->putByte(value >> 16);
    output->putByte(value >> 8);
    output->putByte(value);
  } else {
    output->putByte(majorType | 27);
    output->putByte(value >> 56);
    output->putByte(value >> 48);
    output->putByte(value >> 40);
    output->putByte(value >> 32);
    output->putByte(value >> 24);
    output->putByte(value >> 16);
    output->putByte(value >> 8);
    output->putByte(value);
  }
}

void CborWriter::writeTypeAndIndefiniteValue(const uint8_t majorType) {
  output->putByte((majorType << 5) | 31);
}

void CborWriter::writeBreakCode() {
  output->putByte((7 << 5) | 31);
}

void CborWriter::writeInt(const uint8_t value) {
  writeTypeAndValue(0, (uint32_t)value);
}

void CborWriter::writeInt(const uint16_t value) {
  writeTypeAndValue(0, (uint32_t)value);
}

void CborWriter::writeInt(const uint32_t value) {
  writeTypeAndValue(0, value);
}

void CborWriter::writeInt(const uint64_t value) {
  writeTypeAndValue(0, value);
}

void CborWriter::writeInt(const int64_t value) {
  if (value < 0) {
    writeTypeAndValue(1, (uint64_t) -(value+1));
  } else {
    writeTypeAndValue(0, (uint64_t) value);
  }
}

void CborWriter::writeInt(const int32_t value) {
  if (value < 0) {
    writeTypeAndValue(1, (uint32_t) -(value+1));
  } else {
    writeTypeAndValue(0, (uint32_t) value);
  }
}

void CborWriter::writeInt(const int16_t value) {
  writeInt((int32_t)value);
}

void CborWriter::writeInt(const int8_t value) {
  writeInt((int32_t)value);
}

void CborWriter::writeBytes(const unsigned char *data, const unsigned int size) {
  writeTypeAndValue(2, (uint32_t)size);
  output->putBytes(data, size);
}

void CborWriter::writeString(const char *data, const unsigned int size) {
  writeTypeAndValue(3, (uint32_t)size);
  output->putBytes((const unsigned char *)data, size);
}

void CborWriter::writeArray(const unsigned int size) {
  writeTypeAndValue(4, (uint32_t)size);
}

void CborWriter::writeMap(const unsigned int size) {
  writeTypeAndValue(5, (uint32_t)size);
}

void CborWriter::writeMap() {
  this->writeTypeAndIndefiniteValue(5);
}
void CborWriter::endMap() {
  this->writeBreakCode();
}

void CborWriter::writeTag(const uint32_t tag) {
  writeTypeAndValue(6, tag);
}

void CborWriter::writeSpecial(const uint32_t special) {
  writeTypeAndValue(7, special);
}

void CborWriter::writeBoolean(const bool value) {
  writeTypeAndValue(7, value ? (uint32_t)21 : (uint32_t)20);
}

void CborWriter::writeNull() {
  writeTypeAndValue(7, (uint32_t)22);
}
