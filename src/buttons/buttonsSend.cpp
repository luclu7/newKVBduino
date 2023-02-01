#include "buttonsSend.hpp"

/*
    * constructeur qui prend en entrée les valeurs des boutons, déjà lues préalablement
    * @param VAL : bouton VAL
    * @param MV : bouton MV
    * @param FC : bouton FC
    * @param TEST : bouton TEST
    * @param SF : bouton SF
    * @return ButtonsSend
*/
ButtonsSend::ButtonsSend(bool VAL, bool MV, bool FC, bool TEST, bool SF) {
    this->VAL = VAL;
    this->MV = MV;
    this->FC = FC;
    this->TEST = TEST;
    this->SF = SF;
}

ButtonsSend::~ButtonsSend(void) {

}

/* conversion de l'état des différents boutons en un seul char à envoyer */
unsigned char ButtonsSend::toBytes(void) {
    unsigned char toSend = 0;

    if (this->VAL) {
        toSend |= 0b00000001;
    }

    if (this->MV) {
        toSend |= 0b00000010;
    }

    if (this->FC) {
        toSend |= 0b00000100;
    }

    if (this->TEST) {
        toSend |= 0b00001000;
    }

    if (this->SF) {
        toSend |= 0b00010000;
    }

    return toSend;
}