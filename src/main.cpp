#include <Arduino.h>

#include "helper.hpp"
//#include "pins.hpp"

#include "buttons/buttons.hpp"

#include "messages/messages.hpp"

#include "handleInput/handleInput.hpp"

#include "7segs/7segs.hpp"

#define CLK 25
#define DIO 23


#define LS_PANNE_SOL    34
#define LS_PANNE_ENGIN	36



int variable1 = 0;
int variable2 = 0;

void sendMessage(int varName, int varValue);

void setup() {
  Serial.begin(9600);



  configurePins();

  digitalWrite(LS_PANNE_SOL, HIGH);
  digitalWrite(LS_PANNE_ENGIN, HIGH);

  initSevenSegments();



  Serial.flush();

  while(Serial.available() == 0) {}
  
  digitalWrite(LS_PANNE_SOL, LOW);
  digitalWrite(LS_PANNE_ENGIN, LOW);
}

void loop() {
  updateButtons();

  
  Message msg = receiveMessage();
  if(msg.varName != -1) {
    handleInput(msg);
  }


  if (haveButtonsChanged()) {
    uint8_t buttonsValues = getButtons().toBytes();

    int changedButtonNumber = whichButtonChanged();
    if (changedButtonNumber != -1) {
      int buttonValue = (buttonsValues >> changedButtonNumber) & 0x01;

      sendMessage(changedButtonNumber+1, buttonValue);
      //sendMessage(0x02, changedButtonNumber);
    }

    //tm1637.showNumberDec(buttonsValues); // debug

  }
}