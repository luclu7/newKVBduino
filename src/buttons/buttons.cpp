#include "buttons.hpp"
#include "pins.hpp"

KVBButtons Buttons(BP_VAL, BP_MV, BP_FC, BP_TEST, BP_SF);

/*
    * Cette fonction doit être appelée régulièrement pour que les boutons
    * soient lus correctement.
*/
void updateButtons(void) {
  Buttons.updateAllButtons();
}

int whichButtonChanged(void) {
  return Buttons.whichChanged();
}

/*
    * renvoie true si les boutons ont changé depuis la dernière lecture
    * @return bool: true si les boutons ont changé
*/
bool haveButtonsChanged(void) {
  return Buttons.hasChanged();
}

/*
    * lis les boutons et renvoie un objet ButtonsSend contenant les informations
    * sur l'état des boutons
    * @return ButtonsSend: état des boutons
*/
ButtonsSend getButtons(void) {
    return Buttons.readButtons();
}


/* implémentation des méthodes de la classe KVBButtons */
KVBButtons::KVBButtons(int VAL, int MV, int FC, int TEST, int SF)
{

    this->VALbtn.attach(VAL, INPUT_PULLUP);
    this->MVbtn.attach(MV, INPUT_PULLUP);
    this->FCbtn.attach(FC, INPUT_PULLUP);
    this->TESTbtn.attach(TEST, INPUT_PULLUP);
    this->SFbtn.attach(SF, INPUT_PULLUP);
}

KVBButtons::~KVBButtons()
{
}

/*
    * Cette fonction doit être appelée régulièrement pour que les boutons
    * soient lus correctement.
*/
void KVBButtons::updateAllButtons(void) {
    this->VALbtn.update();
    this->MVbtn.update();
    this->FCbtn.update();
    this->TESTbtn.update();
    this->SFbtn.update();
}

bool KVBButtons::hasChanged(void) {
    return this->VALbtn.changed() || this->MVbtn.changed() || this->FCbtn.changed() || this->TESTbtn.changed() || this->SFbtn.changed();
}


int KVBButtons::whichChanged(void) {
    if (this->VALbtn.changed()) {
        return 0;
    } else if (this->MVbtn.changed()) {
        return 1;
    } else if (this->FCbtn.changed()) {
        return 2;
    } else if (this->TESTbtn.changed()) {
        return 3;
    } else if (this->SFbtn.changed()) {
        return 4;
    } else {
        return -1;
    }
}



/* renvoie un objet ButtonsSend contenant l'état de tous les boutons */
ButtonsSend KVBButtons::readButtons(void) {
    ButtonsSend toSend(!this->VALbtn.read(), !this->MVbtn.read(), !this->FCbtn.read(), !this->TESTbtn.read(), !this->SFbtn.read());
    return toSend;
}