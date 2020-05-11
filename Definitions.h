#ifndef _Definitions_H_
#define _Definitions_H_

const byte buzzerPin = 3;
const byte footSwitchPin = 7;
const byte weldButtonPin = 7;
const byte downButtonPin = 10;
const byte upButtonPin = 9;
const byte selectButtonPin = 8;
const byte weldPin = A2;
const byte zeroCrossPin = 2;
const byte optionalOutput = 5;

//const byte TFT_CSpin = A1; // set in user.h, todo: do in TFT_ILI9341 constructor
//const byte TFT_RSTpin = A0; 
//const byte TFT_DCpin = A3;

const int step_ms = 50;
const int sinusMax_us = 4583; // average between 0.25/50Hz and 0.25/60Hz

const int buzzerHz = 2400;
#endif
