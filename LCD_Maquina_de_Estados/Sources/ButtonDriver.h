/*
 * ButtonDriver.h
 *
 *  Created on: Sep 22, 2017
 *      Author: Jes�s Arnoldo Zerecero N��ez, Andrea Alejandra Mondrag�n Olivos
 */

#ifndef BUTTONDRIVER_H_
#define BUTTONDRIVER_H_

void vfnButtonInit(void);

unsigned char bfnButtonState(unsigned char bBoton);

unsigned char bfnButtonClick(unsigned char bBoton);

void vfnButtonDriver(void);


#endif /* BUTTONDRIVER_H_ */
