#include <iostream>
#include <thread>
#include <chrono>

#include "libserial/SerialStream.h"

#include "../messages/messages.hpp"

void testLamps(LibSerial::SerialStream* serial_stream) {
  std::cout << "-- Lamps test --" << std::endl;

  for (uint8_t i = 1; i <= 8; i++)
  {
    sendMessage(serial_stream, {i, 0});
  }

  std::this_thread::sleep_for(std::chrono::milliseconds(700));

  for (uint8_t i = 1; i <= 8; i++)
  {
    sendMessage(serial_stream, {i, 1});
    std::this_thread::sleep_for(std::chrono::milliseconds(400));
  }

  for (uint8_t i = 8; i >= 1; i--)
  {
    sendMessage(serial_stream, {i, 0});
    std::this_thread::sleep_for(std::chrono::milliseconds(400));
  }
}

void test7segments(LibSerial::SerialStream* serial_stream) {
  std::cout << "-- 7 segments test --" << std::endl;


  for (uint8_t i = 0; i <= 9; i++)
  {
    sendMessage(serial_stream, {0x09, i});
    std::this_thread::sleep_for(std::chrono::milliseconds(400));
  }

  // ^_^
  sendMessage(serial_stream, {0x09, 16});
  std::this_thread::sleep_for(std::chrono::milliseconds(1000));

  // ---
  sendMessage(serial_stream, {0x09, 1});
}