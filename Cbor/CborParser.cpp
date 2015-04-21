#include "CborParser.h"
#include "Arduino.h"
#include <stdlib.h>



CborInput::CborInput(void *data, int size) {
	this->data = (unsigned char *)data;
	this->size = size;
	this->offset = 0;
}

CborInput::~CborInput() {

}

bool CborInput::hasBytes(int count) {
	return size - offset >= count;
}

unsigned char CborInput::getByte() {
	return data[offset++];
}

unsigned short CborInput::getShort() {
	unsigned short value = ((unsigned short)data[offset] << 8) | ((unsigned short)data[offset + 1]);
	offset += 2;
	return value;
}

unsigned int CborInput::getInt() {
	unsigned int value = ((unsigned int)data[offset] << 24) | ((unsigned int)data[offset + 1] << 16) | ((unsigned int)data[offset + 2] << 8) | ((unsigned int)data[offset + 3]);
	offset += 4;
	return value;
}

unsigned long long CborInput::getLong() {
	unsigned long long value = ((unsigned long long)data[offset] << 56) | ((unsigned long long)data[offset+1] << 48) | ((unsigned long long)data[offset+2] << 40) | ((unsigned long long)data[offset+3] << 32) | ((unsigned long long)data[offset+4] << 24) | ((unsigned long long)data[offset+5] << 16) | ((unsigned long long)data[offset+6] << 8) | ((unsigned long long)data[offset+7]); 
	offset += 8;
	return value;
}

void CborInput::getBytes(void *to, int count) {
	memcpy(to, data + offset, count);
	offset += count;
}


