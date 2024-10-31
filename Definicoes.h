// Definições.h (ou definicoes.ino)
#ifndef DEFINICOES_H
#define DEFINICOES_H

#include <loopTimer.h>
#include <millisDelay.h>

const int sdHead        = 25 ; //saída digital motor cabeça
const int sdArmUp       = 27 ;//saída digital motor sobe braço
const int sdArmDown     = 14 ;//saída digital motor desce braço
const int sdLegsUp      = 26 ;//saída digital motor sobe pernas (elevação)
const int sdLegsDown    = 27 ;//saída digital motor desce pernas (elevação)
const int sdWaistLeft   = 32 ;//saída digital motor esquerda cintura
const int sdWaistRight  = 4 ;//saída digital motor direita cintura
const int saHand        = 33 ;//saída analógica motor aceno (0-255 = 0-100%)
const int eaHand        = 14 ;//entrada analógica corrente do motor aceno
const int edArmUp       = 21 ;//entrada digital motor braço em cima
const int edArmDown     = 19 ;//entrada digital motor braço em embaixo
const int edLegsUp      = 1  ;//entrada digital motor sobe pernas (elevação)
const int edLegsDown    = 3  ;//entrada digital motor desce pernas (elevação)
const int edWaistLeft   = 23 ;//entrada digital motor esquerda cintura
const int edWaistRight  = 22 ;//entrada digital motor direita cintura

//////////////////////ESPELHOS PARA MANIPULAÇÃO/////////////////////////////////

 bool axsdHead       ;//saída digital motor cabeça
 bool axsdArmUp      ;//saída digital motor sobe braço
 bool axsdArmDown    ;//saída digital motor desce braço
 bool axsdLegsUp     ;//saída digital motor sobe pernas (elevação)
 bool axsdLegsDown   ;//saída digital motor desce pernas (elevação)
 bool axsdWaistLeft  ;//saída digital motor esquerda cintura
 bool axsdWaistRight ;//saída digital motor direita cintura
 bool axsaHand       ;//saída analógica motor aceno (0-255 = 0-100%)
 
 bool axeaHand        = digitalRead(eaHand) ;		//leitura leitura entrada analógica corrente do motor aceno
 bool axedArmUp       = digitalRead(edArmUp) ;		//leitura entrada digital motor braço em cima
 bool axedArmDown     = digitalRead(edArmDown) ;	//leitura entrada digital motor braço em embaixo
 bool axedLegsUp      = digitalRead(edLegsUp) ;		//leitura entrada digital motor sobe pernas (elevação)
 bool axedLegsDown    = digitalRead(edLegsDown) ;	//leitura entrada digital motor desce pernas (elevação)
 bool axedWaistLeft   = digitalRead(edWaistLeft) ;	//leitura entrada digital motor esquerda cintura
 bool axedWaistRight  = digitalRead(edWaistRight) ;	//leitura entrada digital motor direita cintura

////////////////////////////////////////////////////////////////////////////////
millisDelay mtHead    ;//motion timeout CABEÇA
millisDelay mtArm     ;//motion timeout BRAÇO DIREITO
millisDelay mtLegs    ;//motion timeout PERNAS (elevação)
millisDelay mtWaist   ;//motion timeout CINTURA
millisDelay mtHand    ;//motion timeout ACENO (mão)




#define BLUE_LED 2
int ledOut = LOW;

#endif // DEFINICOES_H

