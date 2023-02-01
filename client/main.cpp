#include <iostream>
#include "/usr/include/libserial/SerialStream.h"
#include "/usr/include/libserial/SerialPort.h"

#include <chrono>
#include <thread>


void sendMessage(LibSerial::SerialStream* serialPort, int varName, int varValue);
void readMessage(LibSerial::SerialStream* serial_stream);
void configureSerialPort(LibSerial::SerialStream* serial_stream, std::string portName);

#define VOLTMETER 0x02


int main()
{
  // Create a SerialStream object
  LibSerial::SerialStream serial_stream;

  configureSerialPort(&serial_stream, "/dev/ttyACM1");


  std::cout << "Serial port is open: " << serial_stream.IsOpen() << std::endl;

  std::cout << "Waiting for 2 seconds" << std::endl;

  // sleep for 2 seconds
  std::this_thread::sleep_for(std::chrono::milliseconds(2000));
  
  std::cout << "Writing to serial port" << std::endl;

  int varName;

  // for (size_t i = 0; i < 255; i++)
  // {

  //   varName = 2;
  //   int varValue = i;

  //   sendMessage(&serial_stream, varName, varValue);
    
  //   // sleep for 2 seconds
  //   std::this_thread::sleep_for(std::chrono::milliseconds(100));
  // }



  sendMessage(&serial_stream, VOLTMETER, 160);
  std::this_thread::sleep_for(std::chrono::milliseconds(300));
  sendMessage(&serial_stream, VOLTMETER, 155);
  


  // Define the header, variable name, value and checksum
  std::cout << "Waiting for 2 seconds" << std::endl;

  // sleep for 2 seconds
  std::this_thread::sleep_for(std::chrono::milliseconds(1000));

  std::cout << std::endl <<  "Number of bytes available: " << serial_stream.rdbuf()->in_avail() << std::endl;


  // write 132 to variable 1 and wait for response
  sendMessage(&serial_stream, 0x01, 132);
  std::this_thread::sleep_for(std::chrono::milliseconds(300));

  std::cout << "Number of bytes available: " << serial_stream.rdbuf()->in_avail() << std::endl;

  while (false)
  {
    readMessage(&serial_stream);
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
  }

  bool exit = false;

  std::string input;

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

void sendMessage(LibSerial::SerialStream* serial_stream, int varName, int varValue) {
  int header = 0x23;
  int checksum = header + varName + varValue;

  // on prie que ça marche
  serial_stream->write((char*)&header, 1);
  serial_stream->write((char*)&varName, 1);
  serial_stream->write((char*)&varValue, 1);
  serial_stream->write((char*)&checksum, 1);

  std::cout << "Sent: " << header << " " << varName << " " << varValue << " " << checksum << std::endl;

  // read ack
  char ack;
  serial_stream->read(&ack, 1);
  if(ack == header+1) {
    std::cout << "Acknowledgement received" << std::endl;
  } else {
    std::cout << "Acknowledgement not received" << std::endl;
  }
}

void readMessage(LibSerial::SerialStream* serial_stream) {
    if (serial_stream->rdbuf()->in_avail() >= 4) {
      //std::cout << "2 Number of bytes available: " << serial_stream->rdbuf()->in_avail() << std::endl;


      uint8_t header, varName, varValue, checksum;

      const int BUFFER_SIZE = serial_stream->rdbuf()->in_avail()+1;
      char input_buffer[BUFFER_SIZE];

      serial_stream->read( input_buffer, BUFFER_SIZE );

      std::cout << std::endl;

      header = (unsigned int) input_buffer[1];
      varName = (unsigned int) input_buffer[2];
      varValue = (unsigned int) input_buffer[3];
      checksum = (unsigned int) input_buffer[4];
      
      //std::cout << "3 Number of bytes available: " << serial_stream->rdbuf()->in_avail() << std::endl;
      std::cout << "Received: " << (unsigned int) header << " " << (unsigned int) varName << " " << (unsigned int) varValue << " " << (unsigned int) checksum << std::endl;
      std::cout << "Variable name: " << (unsigned int) varName << " Variable value: " << (unsigned int) varValue << std::endl;

      // Verify the checksum
      if (header + varName + varValue == checksum) {
        std::cout << "Correct checksum !" << std::endl;

        // send acknowledgement
        //serial_stream->write((char*)&header, 1);

        std::cout << "Acknowledgement sent" << std::endl;

        switch (varName)
        {
        case 0x01:
          std::cout << "BP VAL: " << (unsigned int) varValue << std::endl;
          break;
        
        case 0x02:
          std::cout << "BP MV: " << (unsigned int) varValue << std::endl;
          break;          

        case 0x03:
          std::cout << "BP FC: " << (unsigned int) varValue << std::endl;
          break;

        case 0x04:
          std::cout << "BP TEST: " << (unsigned int) varValue << std::endl;
          break;

        case 0x05:
          std::cout << "BP SF: " << (unsigned int) varValue << std::endl;
          break;

        default:
          break;
        }
      } else {
        // send error
        // TODO: *serial_stream << 0x25;
        std::cout << "Incorrect checksum !" << std::endl;
        //std::cout << "Error sent" << std::endl;
      }
    }
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

