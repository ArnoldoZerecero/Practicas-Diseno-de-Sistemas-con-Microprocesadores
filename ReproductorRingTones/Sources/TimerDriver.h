/*
 * TimerDriver.h
 *
 *  Created on: Oct 10, 2017
 *      Author: Jes�s Arnoldo Zerecero N��ez
 */

#ifndef TIMERDRIVER_H_
#define TIMERDRIVER_H_

enum /*Lista de contadores que se utilizar�n*/
{
	DURACION_CNT, /*Contador para la duraci�n de cada tono*/
	DIVISOR_CNT, /*Contador para dividir la frecuencia de cada tono*/
	
	TOTAL_CNT
};

#define NUMERO_CONTADORES TOTAL_CNT

void vfnCntLoadAssign (unsigned long dwCntLoad, unsigned char bCounter);

unsigned char bfnTimeTargetReached (unsigned char bCounter);

void vfnTimerDriver(void);

void vfnPitCallback(void);

#endif /* TIMERDRIVER_H_ */
