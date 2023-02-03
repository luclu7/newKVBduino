#include "serial/serial.h"
#include "messages.hpp"

#include "iostream"

int header = 0x23;
#define ack 0x24

int varName, varValue, checksum;

/// @brief Envoie un message sur le port série et vérifie l'acknowledgement
/// @param serial_stream port série sur lequel envoyer le message
/// @param varName id de la variable à modifier
/// @param varValue valeur à envoyer
/// @return bool true si l'acknowledgement a été reçu, false sinon
bool sendMessage(serial::Serial* serial_stream, uint8_t varName, uint8_t varValue) {
  int checksum = header + varName + varValue;

  // on prie que ça marche
  serial_stream->write((const uint8_t*)&header, 1);
  serial_stream->write((const uint8_t*)&varName, 1);
  serial_stream->write((const uint8_t*)&varValue, 1);
  serial_stream->write((const uint8_t*)&checksum, 1);

  std::cout << "Sent: " << (unsigned int) header << " " << (unsigned int) varName << " " << (unsigned int) varValue << " " << (unsigned int) checksum << std::endl;

  // read ack
  uint8_t received_ack;
  serial_stream->read(&received_ack, 1);
  if(received_ack == ack) {
    std::cout << "Acknowledgement received" << std::endl;
    return true;
  } else {
    std::cout << "Acknowledgement not received" << std::endl;
    return false;
  }
}

bool sendMessage(serial::Serial* serialPort, Message msg) {
  return sendMessage(serialPort, msg.varName, msg.varValue);
}

void readMessage(serial::Serial* serial_stream) {
    if (serial_stream->available() >= 4) {
      //std::cout << "2 Number of bytes available: " << serial_stream->rdbuf()->in_avail() << std::endl;


      int header, varName, varValue, checksum;

      //serial::Serial::ScopedReadLock (serial_stream);
      const int BUFFER_SIZE = serial_stream->available();
      uint8_t input_buffer[BUFFER_SIZE];

      // read to vector of uint8_t
      std::vector<uint8_t> input_buffer_vector;
      serial_stream->read(input_buffer_vector, BUFFER_SIZE);

      // print vector content
    /*   std::cout << "Vector content: ";
      for (int i = 0; i < BUFFER_SIZE; i++) {
        std::cout << (unsigned int) input_buffer_vector[i] << " ";
      }
 */

      header = (unsigned int) input_buffer_vector[0];
      varName = (unsigned int) input_buffer_vector[1];
      varValue = (unsigned int) input_buffer_vector[2];
      checksum = (unsigned int) input_buffer_vector[3];

      std::cout << "Number of bytes available now: " << serial_stream->available() << std::endl;
      
      //std::cout << "3 Number of bytes available: " << serial_stream->rdbuf()->in_avail() << std::endl;
      std::cout << "Received: " << (unsigned int) header << " " << (unsigned int) varName << " " << (unsigned int) varValue << " " << (unsigned int) checksum << std::endl;
      std::cout << "Variable name: " << (unsigned int) varName << " Variable value: " << (unsigned int) varValue << std::endl;

      // Verify the checksum
      if (header + varName + varValue == checksum) {
        std::cout << "Correct checksum !" << std::endl;

        // send acknowledgement
        serial_stream->write((const uint8_t*)&header, 1);

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