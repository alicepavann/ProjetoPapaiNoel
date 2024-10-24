
#include <loopTimer.h>
#include <millisDelay.h>

const int sdHead        = 25 ; //saída digital motor cabeça
const int sdArmUp       = 27 ;//saída digital motor sobe braço
const int sdArmDown     = 14 ;//saída digital motor desce braço
const int sdLegsUp      = 34 ;//saída digital motor sobe pernas (elevação)
const int sdLegsDown    = 35 ;//saída digital motor desce pernas (elevação)
const int sdWaistLeft   = 36 ;//saída digital motor esquerda cintura
const int sdWaistRight  = 39 ;//saída digital motor direita cintura
const int saHand        = 33 ;//saída analógica motor aceno (0-255 = 0-100%)
const int eaHand        = 14 ;//entrada analógica corrente do motor aceno
const int edArmUp       = 21 ;//entrada digital motor braço em cima
const int edArmDown     = 19 ;//entrada digital motor braço em embaixo
const int edLegsUp      = 01 ;//saída digital motor sobe pernas (elevação)
const int edLegsDown    = 03 ;//saída digital motor desce pernas (elevação)
const int edWaistLeft   = 23 ;//saída digital motor esquerda cintura
const int edWaistRight  = 22 ;//saída digital motor direita cintura

millisDelay mtHead    ;//motion timeout CABEÇA
millisDelay mtArm     ;//motion timeout BRAÇO DIREITO
millisDelay mtLegs    ;//motion timeout PERNAS (elevação)
millisDelay mtWaist   ;//motion timeout CINTURA
millisDelay mtHand    ;//motion timeout ACENO (mão)




#define BLUE_LED 2
int ledOut = LOW;



