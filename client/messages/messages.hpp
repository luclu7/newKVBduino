#pragma once

#include "libserial/SerialStream.h"


struct Message {
  uint8_t varName;
  uint8_t varValue;
};

bool sendMessage(LibSerial::SerialStream* serialPort, uint8_t varName, uint8_t varValue);
bool sendMessage(LibSerial::SerialStream* serialPort, Message msg);
void readMessage(LibSerial::SerialStream* serial_stream);