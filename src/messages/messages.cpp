#include "Arduino.h"
#include "../pins.hpp"
#include "messages.hpp"


int header = 0x23;
int ack = 0x24;
int varName, varValue, checksum;


Message receiveMessage(void) {
  if (Serial.available() >= 4) {
    header = Serial.read();
    varName = Serial.read();
    varValue = Serial.read();
    checksum = Serial.read();

    // Verify the checksum
    if (header + varName + varValue == checksum) {
      // send acknowledgement
      Serial.write(ack);
      //tm1637.showNumberDec(varValue);
      
      return {varName, varValue};
      
    } else {
      return {-1, -1};
    }
  } else {
    return {-1, -1};
  }
}

void sendMessage(int varName, int varValue) {
  int header = 0x23;
  int checksum = header + varName + varValue;

  if(checksum > 255)
    checksum = checksum - 255; // overflow manuel


  //tm1637.showNumberDec(checksum); // debug
  Serial.flush(); // on sais jamais

  if (Serial.availableForWrite() >= 4) {
    // on prie que ça marche mdr
    Serial.write((char*)&header, 1);
    Serial.write((char*)&varName, 1);
    Serial.write((char*)&varValue, 1);
    Serial.write((char*)&checksum, 1);
  }
  


  // read ack
  char ack;

//    tm1637.showNumberHex(ack); // debug

  //tm1637.showNumberDec(Serial.available()); // debug

  
  //delay(100);
  
  if(Serial.available() >= 1) {
    //Serial.readBytes(&ack, 1);
    
    if(ack == 0x24) {
      //std::cout << "Acknowledgement received" << std::endl;

      digitalWrite(LS_PANNE_SOL, LOW);
      delay(100);
      digitalWrite(LS_PANNE_SOL, HIGH);
      delay(100);
      digitalWrite(LS_PANNE_SOL, LOW);
      delay(100);   
      digitalWrite(LS_PANNE_ENGIN, HIGH);
    } else {
      // not received
      digitalWrite(LS_PANNE_SOL, HIGH);
      delay(100);
      digitalWrite(LS_PANNE_SOL, LOW);
      delay(100);
      digitalWrite(LS_PANNE_SOL, HIGH);
      delay(100);   
      digitalWrite(LS_PANNE_ENGIN, LOW);
    }
  }
  //sendMessage(0x10, ack);

  
}