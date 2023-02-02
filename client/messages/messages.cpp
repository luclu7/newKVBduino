#include "libserial/SerialStream.h"
#include "messages.hpp"

#include "iostream"

int header = 0x23;
int ack = 0x24;
int varName, varValue, checksum;


bool sendMessage(LibSerial::SerialStream* serial_stream, uint8_t varName, uint8_t varValue) {
  int checksum = header + varName + varValue;

  // on prie que ça marche
  serial_stream->write((char*)&header, 1);
  serial_stream->write((char*)&varName, 1);
  serial_stream->write((char*)&varValue, 1);
  serial_stream->write((char*)&checksum, 1);

  std::cout << "Sent: " << (unsigned int) header << " " << (unsigned int) varName << " " << (unsigned int) varValue << " " << (unsigned int) checksum << std::endl;

  // read ack
  char received_ack;
  serial_stream->read(&received_ack, 1);
  if(received_ack == ack) {
    std::cout << "Acknowledgement received" << std::endl;
    return true;
  } else {
    std::cout << "Acknowledgement not received" << std::endl;
    return false;
  }
}

bool sendMessage(LibSerial::SerialStream* serialPort, Message msg) {
  return sendMessage(serialPort, msg.varName, msg.varValue);
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