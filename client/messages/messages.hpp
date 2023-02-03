#pragma once

#include "serial/serial.h"

struct Message {
  uint8_t varName;
  uint8_t varValue;
};

bool sendMessage(serial::Serial* serialPort, uint8_t varName, uint8_t varValue);
bool sendMessage(serial::Serial* serialPort, Message msg);
void readMessage(serial::Serial* serial_stream);