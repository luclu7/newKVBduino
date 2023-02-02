#include <iostream>
#include "libserial/SerialStream.h"

#include <chrono>
#include <thread>

#include "messages/messages.hpp"

#include "tests/tests.hpp"

void configureSerialPort(LibSerial::SerialStream* serial_stream, std::string portName);
void testLamps(LibSerial::SerialStream* serial_stream);
void test7segments(LibSerial::SerialStream* serial_stream);


#define ID_PANNE_SOL 0x01
#define ID_PANNE_ENGIN 0x02
#define ID_V 0x03
#define ID_FU 0x04
#define ID_BP_VAL 0x05
#define ID_BP_MV 0x06
#define ID_BP_FC 0x07
#define ID_SF 0x08
#define ID_VISU 0x09


int main(int argc, char** argv)
{
  // Create a SerialStream object
  LibSerial::SerialStream serial_stream;

  configureSerialPort(&serial_stream, "/dev/ttyACM0");

  std::cout << "Serial port is open: " << serial_stream.IsOpen() << std::endl;

  std::cout << "Waiting for 2 seconds" << std::endl;

  // sleep for 2 seconds
  std::this_thread::sleep_for(std::chrono::milliseconds(2000));
  
  std::cout << "Writing to serial port" << std::endl;

  std::this_thread::sleep_for(std::chrono::milliseconds(1000));

  testLamps(&serial_stream);

  test7segments(&serial_stream);


  std::this_thread::sleep_for(std::chrono::milliseconds(1000));

  // for (size_t i = 0; i < 255; i++)
  // {

  //   varName = 2;
  //   int varValue = i;

  //   sendMessage(&serial_stream, varName, varValue);
    
  //   // sleep for 2 seconds
  //   std::this_thread::sleep_for(std::chrono::milliseconds(100));
  // }


  // Define the header, variable name, value and checksum
  std::cout << "Waiting for 2 seconds" << std::endl;

  // sleep for 2 seconds
  std::this_thread::sleep_for(std::chrono::milliseconds(1000));

//  std::cout << std::endl <<  "Number of bytes available: " << serial_stream.rdbuf()->in_avail() << std::endl;


  // write 132 to variable 1 and wait for response
  // sendMessage(&serial_stream, 0x01, 132);
  // std::this_thread::sleep_for(std::chrono::milliseconds(500));


  // sendMessage(&serial_stream, 0x01, 0);
  // sendMessage(&serial_stream, 0x02, 0);

  // sendMessage(&serial_stream, 0x09, 4);


  while (false)
  {
    readMessage(&serial_stream);
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
  }

  bool exit = false;

  std::string input = "";

  int varName = 9;

  while (!exit)
  {
    std::cout << "varName: ";
    std::cin >> input;
    varName = std::stoi(input);
    if(varName == 0) exit = true;
    input = "";
    std::cout << "varValue: ";
    std::cin >> input;
    int varValue = std::stoi(input);

    input = "";

    sendMessage(&serial_stream, varName, varValue);
  }

  
  std::cout << "Closing serial port" << std::endl;
  
  // Close the serial port
  serial_stream.Close();

  return 0;
}

void configureSerialPort(LibSerial::SerialStream* serial_stream, std::string portName) {
  // Open the serial port
  serial_stream->Open(portName);

  // Set the serial port parameters
  serial_stream->SetBaudRate(LibSerial::BaudRate::BAUD_9600);
  serial_stream->SetCharacterSize(LibSerial::CharacterSize::CHAR_SIZE_8);
  serial_stream->SetStopBits(LibSerial::StopBits::STOP_BITS_1);
  serial_stream->SetParity(LibSerial::Parity::PARITY_NONE);
  serial_stream->SetFlowControl(LibSerial::FlowControl::FLOW_CONTROL_NONE);
}

