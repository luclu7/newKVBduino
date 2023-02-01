// pour les deux afficheurs
#include <AceTMI.h> // SimpleTmi1637Interface
#include <AceSegment.h> // Tm1637Module
using ace_tmi::SimpleTmi1637Interface;
using ace_segment::Tm1637Module;

#include "definitions.hpp"

// pins du TM1637
const uint8_t CLK_PIN = 25;
const uint8_t DIO_PIN = 23;
const uint8_t NUM_DIGITS = 6;
const uint8_t DELAY_MICROS = 100;

/* déclaration de l'object *visu* */
using TmiInterface = SimpleTmi1637Interface;
TmiInterface tmiInterface(DIO_PIN, CLK_PIN, DELAY_MICROS);
Tm1637Module<TmiInterface, NUM_DIGITS> visu(tmiInterface);

/*
	Allume les segments de l'afficheur selon
	le tableau de uint8_t passé en paramètre
*/
void setVisu(const uint8_t pattern[]) {
	visu.setPatternAt(0, pattern[0]);
	visu.setPatternAt(1, pattern[1]);
	visu.setPatternAt(2, pattern[2]);
	visu.setPatternAt(3, pattern[3]);
	visu.setPatternAt(4, pattern[4]);
	visu.setPatternAt(5, pattern[5]);

	visu.flush();
}

/*
	Initialisation de l'afficheur
*/
void initSevenSegments(void) {
	tmiInterface.begin();
	visu.begin();
	visu.setBrightness(7);

	setVisu(tirets);
}

/*
	Test du visualiseur
*/
void testVisu(void)
{
	const int delayTime = 100;

	setVisu(autotest);
	delay(delayTime);
	setVisu(eteint);

	setVisu(PA400);
	delay(delayTime * 2);
	setVisu(UC512);
	delay(delayTime * 2);


	// long autotest
#if DEBUG && !SKIPTEST
	delay(delayTime);
	// autotest, tirets, zerozeroAux, zerozeroPrincipal, triplezeroAux, preannonce, preannonceAux, vitesseover160, faute
	setVisu(tirets);
	delay(delayTime);
	setVisu(zerozeroAux);
	delay(delayTime);
	setVisu(triplezeroAux);
	delay(delayTime);
	setVisu(zerozeroPrincipal);
	delay(delayTime);
	setVisu(preannonce);
	delay(delayTime);
	setVisu(preannonceAux);
	delay(delayTime);
	setVisu(vitesseover160);
	delay(delayTime);
	setVisu(faute);
	delay(delayTime);

#endif

	// :wink:
	delay(1500);
	setVisu(uwu);
	delay(1500);
	setVisu(eteint);
	delay(500);

	setVisu(tirets);
	delay(1500);
}


