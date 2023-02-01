#ifndef BUTTONS_H
#define BUTTONS_H
// pour le debouncing
#include <Bounce2.h>
#include "buttonsSend.hpp"

/*
    Cette classe tient tous les boutons du KVB. Elle permet de les lire
    et de les convertir en un objet ButtonsSend, utilisé pour l'envoi.

    Il est nécessaire de régulièrement appeler la fonction updateAllButtons()
    pour que les boutons soient lus correctement. La fonction hasChanged()
    permet de savoir si les boutons ont changé depuis la dernière lecture.
    On peut ensuite utiliser la fonction readButtons() pour obtenir un
    objet ButtonsSend contenant les informations sur les boutons.
*/
class KVBButtons
{
private:
public:
    Bounce VALbtn, MVbtn, FCbtn, TESTbtn, SFbtn;
    KVBButtons(int BP_VAL, int BP_MV, int BP_FC, int BP_TEST, int BP_SF);
    ~KVBButtons();
    void updateAllButtons(void);
    bool hasChanged(void);
    ButtonsSend readButtons(void);
    int whichChanged(void);
};

void updateButtons(void);
ButtonsSend getButtons(void);
bool haveButtonsChanged(void);
int whichButtonChanged(void);

#endif