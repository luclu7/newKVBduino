#include "helper.hpp"
#include "pins.hpp"

#include "Arduino.h"

String lastReadThumbSwitch = "";
unsigned long lastCheckedThumbSwitches = millis();


/*
  * configuration des pins en entrée/sortie
*/
void configurePins(void) {

  for (int i = 0; i < 10; i++ ) {
    pinMode(pins[i], OUTPUT);
  }

  pinMode(BEEP_V, OUTPUT);

  for (int i = 0; i < 6; i++ ) {
    pinMode(digits[i], INPUT_PULLUP);
  }

  for (int i = 0; i < 8; i++ ) {
    pinMode(lightPins[i], OUTPUT);
  }

  //lightTestPattern();

}

void lightTestPattern(void) {
  for (int i = 0; i < 8; i++ ) {
    digitalWrite(lightPins[i], HIGH);
    delay(500);
  }
  delay(1000);
  for (int i = 0; i < 8; i++ ) {
    digitalWrite(lightPins[i], LOW);
    delay(500);
  }
}

// TODO: faire un truc qui marche correctement
/*
  * lecture de des roues codeuses un peu comme
  * une matrice de 10x6
  * on allume une colonne, et on lit les lignes
  * on allume la colonne suivante, etc
*/

void blinkVAL(void) {
  digitalWrite(LS_BP_VAL, HIGH);
  
  delay(200);
  digitalWrite(LS_BP_VAL, LOW);
  delay(200);
}
