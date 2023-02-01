#ifndef BUTTONSSEND_H
#define BUTTONSSEND_H

#include <Arduino.h>


/*
    Classe utilisée pour contenir les informations sur les différents bouton
    avant de les envoyer au PC. Elle permet de les convertir en JSON ou en
    byte pour l'envoi.
*/
class ButtonsSend
{
private:
    bool VAL;
    bool MV;
    bool FC;
    bool TEST;
    bool SF;
public:
    ButtonsSend(bool VAL, bool MV, bool FC, bool TEST, bool SF);
    ~ButtonsSend();
    unsigned char toBytes(void);
    String toJSON(void);
};

#endif