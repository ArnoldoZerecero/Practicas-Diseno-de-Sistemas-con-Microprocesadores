/*
 * TimerDriver.h
 *
 *  Created on: Oct 10, 2017
 *      Author: Jesús Arnoldo Zerecero Núñez
 */

#ifndef TIMERDRIVER_H_
#define TIMERDRIVER_H_

enum /*Lista de contadores que se utilizarán*/
{
	DURACION_CNT, /*Contador para la duración de cada tono*/
	DIVISOR_CNT, /*Contador para dividir la frecuencia de cada tono*/
	
	TOTAL_CNT
};

#define NUMERO_CONTADORES TOTAL_CNT

void vfnCntLoadAssign (unsigned long dwCntLoad, unsigned char bCounter);

unsigned char bfnTimeTargetReached (unsigned char bCounter);

void vfnTimerDriver(void);

void vfnPitCallback(void);

#endif /* TIMERDRIVER_H_ */
