/*
 * LedDriver.h
 *
 *  Created on: Sep 22, 2017
 *      Author: Jesús Arnoldo Zerecero Núñez, Andrea Alejandra Mondragón Olivos
 */

#ifndef LEDDRIVER_H_
#define LEDDRIVER_H_

void vfnLedInit(void);

void vfnLedOn(unsigned char bLED);

void vfnLedOff(unsigned char bLED);

void vfnLedToggle(unsigned char bLED);

unsigned char bfnLedBusy(unsigned char bLED);

unsigned char bfnLedBlink(unsigned char bLED, unsigned short wTimeOn, unsigned short wTimeOff, unsigned short wCycles);

void vfnLedDriver(void);


#endif /* LEDDRIVER_H_ */
