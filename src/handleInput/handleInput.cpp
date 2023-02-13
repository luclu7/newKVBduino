#include "handleInput.hpp"
#include "Arduino.h"

#include "../messages/messages.hpp"
#include "../pins.hpp"

#include "../7segs/7segs.hpp"

#include "../7segs/definitions.hpp"

void handleInput(Message msg) {
  int varValue = msg.varValue;
  switch (msg.varName)
  {
  case 0x01: // first command sent at startup
    setLamp(varValue, LS_PANNE_SOL);
    break;
  
  case 0x02: 
    setLamp(varValue, LS_PANNE_ENGIN);
    break;  

  case 0x03: 
    setLamp(varValue, LS_V);
    break;
      
  case 0x04: 
    setLamp(varValue, LS_FU);
    break;

  case 0x05:
    setLamp(varValue, LS_BP_VAL);
    break;

  case 0x06:
    setLamp(varValue, LS_BP_MV);
    break;

  case 0x07:
    setLamp(varValue, LS_BP_FC);
    break;

  case 0x08:
    setLamp(varValue, LS_SF);
    break;

  case 0x09:
    switch (varValue)
		{
			case 0: // éteint
				setVisu(eteint);
				break;

			case 1: // contrôle de vitesse actif (la vitesse maximale autorisée ne dépasse pas 160 km/h)
				setVisu(tirets);
				break;

			case 2: // contrôle d'annonce d'un signal d'arrêt fermé avec vitesse d'approche 30 km/h
				setVisu(zeroZeroAux);
				break;

			case 3: // contrôle de vitesse à 30 km/h
				setVisu(zeroZeroPrincipal);
				break;

			case 4: // contrôle d'annonce d'un signal d'arrêt fermé avec vitesse d'approche 10 km/h
				setVisu(tripleZeroAux);
				break;

			case 5: // contrôle de vitesse à 160 km/h
				setVisu(preannonce);
				break;

			case 6: // contrôle de pré-annonce
				setVisu(preannonceAux);
				break;

			case 7: // contrôle de vitesse actif (la vitesse maximale autorisée est supérieure à 160 km/h si rien ne s'y oppose) "b" affiché
				setVisu(vitesseSup160);
				break;

			case 8: // autotest ou test en cours
				setVisu(autotest);
				break;

			case 9: // données incompatibles avec le tableau de cohérence
				setVisu(faute);
				break;

      case 10:
        setVisu(PA400);
        break;

      case 11:
        setVisu(UC512);
        break;

			case 16:
				setVisu(uwu); // ^_^
				break;

      case 17:
        setVisu(numbersOneToSix);
        break;

			default:
				break;
		}

    break;
  
  default:
    break;
  }
  
}


/// @brief Turn on or off a lamp
/// @param input 0 or 1
/// @param led the pin the lamp is connected to
void setLamp(const int input, const int led) {
  if (input == 0) {
    digitalWrite(led, LOW);
  } else {
    digitalWrite(led, HIGH);
  }
}
