#include "cborEncoder.h"
#include "cborDecoder.h"
#include "cborDebugListener.h"

void setup() {
  Serial.begin(9600);
  uint32_t countdownBegin = millis();
  while (!Serial && ((millis() - countdownBegin) < 1000)) {};

  test();
}

void loop() {
  while(Serial.available()) {
   Serial.read();
  }
}

void test() {
	// Create buffer,  object and writer
  uint8_t outputBuffer[32];
  CborStaticOutput output(outputBuffer, 32);
  CborWriter writer(output);

  // Create CBOR packet
  // Chose which one by uncommenting
//  writer.writeInt((uint64_t)65535); // uint32_t, uint16_t and uint8_t are also possible
//  writer.writeBoolean(false);
//  writer.writeNull();
//  writer.writeUndefined();
  writer.writeFloat((double)2.0);   // float is also possible
  Serial.print("Size of CBOR packet: ");
  Serial.println(output.getSize());
  for (size_t i = 0; i < output.getSize()-1; i++) {
    if (outputBuffer[i] < 10) {
      Serial.print(0);
    }
    Serial.print(outputBuffer[i], HEX);
  }
  if (outputBuffer[output.getSize()-1] < 10) {
    Serial.print(0);
  }
  Serial.println(outputBuffer[output.getSize()-1], HEX);
	delay(1000);

  // Decode the packet
  CborInput input(output.getData(), output.getSize());
  CborReader reader(input);
  // Create a listener object.
  CborDebugListener listener;
  // Initalize the listener.
  reader.SetListener(listener);
  reader.Run();
}
