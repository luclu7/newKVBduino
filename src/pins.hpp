#pragma once

// définition pins rétroéclairage des boutons et lampes
#define LS_SF			22

#define LS_BP_VAL		24
#define LS_BP_MV		26
#define LS_BP_FC        28

#define LS_V            30
#define LS_FU           32
#define LS_PANNE_SOL    34
#define LS_PANNE_ENGIN	36

// définition pins boutons
#define BP_VAL  29
#define BP_MV   31
#define BP_FC   33
#define BP_TEST 35
#define BP_SF   37

// pins roue codeuse
// rows (les différentes positions)
#define P0 52
#define P1 50
#define P2 48
#define P3 53
#define P4 51
#define P5 49
#define P6 43
#define P7 45
#define P8 47
#define P9 46

// columns (les différentes roues codeuses)
#define V_1 2
#define V_2 3

#define L_1   4

#define D_1 5
#define D_2 6
#define D_3 7

/*    pins 3 positions    */
#define SW_COM 8
#define SW_VO P1
//#define SW_ME P4
#define SW_MA P3

// TS: bip_V_control
#define BEEP_V 11


/*
    * tableau des pins, pour les boucles
*/
const int pins[] = {P0, P1, P2, P3, P4, P5, P6, P7, P8, P9};

const int digits[] = {V_1, V_2, L_1, D_1, D_2, D_3};

const int switchPins[] = {SW_VO, SW_MA};

const int BPPins[] = {BP_VAL, BP_MV, BP_FC, BP_TEST};

const int lightPins[] = {LS_BP_VAL, LS_BP_MV, LS_BP_FC, LS_V, LS_FU, LS_PANNE_SOL, LS_PANNE_ENGIN, LS_SF};
