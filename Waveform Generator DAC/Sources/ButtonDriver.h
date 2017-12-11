/*
 * ButtonDriver.h
 *
 *  Created on: Sep 22, 2017
 *      Author: Jesús Arnoldo Zerecero Núñez, Andrea Alejandra Mondragón Olivos
 */

#ifndef BUTTONDRIVER_H_
#define BUTTONDRIVER_H_

void vfnButtonInit(void);

unsigned char bfnButtonState(unsigned char bBoton);

unsigned char bfnButtonClick(unsigned char bBoton);

void vfnButtonDriver(void);


#endif /* BUTTONDRIVER_H_ */
