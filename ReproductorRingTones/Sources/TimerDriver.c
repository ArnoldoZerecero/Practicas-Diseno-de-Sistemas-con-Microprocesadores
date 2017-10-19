/*
 * TimerDriver.c

 *
 *  Created on: Oct 10, 2017
 *      Author: Jesús Arnoldo Zerecero Núñez
 */
#include "TimerDriver.h"
#include "derivative.h"
#include "LedDriver.h"


volatile unsigned long gadwCounters[NUMERO_CONTADORES]; /*Arreglo global para cada cuenta de cada contador*/

volatile unsigned char gflgTimerOverflow = 0; /*Bandera global que se setea cada que se da una interrupción */

void vfnCntLoadAssign (unsigned long dwCntLoad, unsigned char bCounter)
{
	if(bCounter < NUMERO_CONTADORES) /*Si el contador existe*/
	{
	gadwCounters[bCounter] = dwCntLoad; /*Se asigna el valor desde donde se quiere empezar a contar al contador especificado*/
	}
}

unsigned char bfnTimeTargetReached (unsigned char bCounter)
{
	if(bCounter < NUMERO_CONTADORES) /*Si el contador existe*/
	{
		if(!gadwCounters[bCounter]) /*Si el contador especificado ya llegó a cero*/
		{
			return 0;
		}
		else
		{
			return 1;
		}
	}
	return 1;
}

void vfnTimerDriver(void)
{
	if(gflgTimerOverflow) /*Si esta prendida la bandera de interrupción*/
	{
		unsigned char bCounterIndex = NUMERO_CONTADORES; /*Índice para el número de contadores*/
		
		while(bCounterIndex--)
		{
			if(gadwCounters[bCounterIndex]); /*Si el contador en esa posición aun no llega a cero*/
			{
				if(bfnTimeTargetReached(bCounterIndex)) /*Si el contador en esa posición aun no llega a cero*/
				{
					gadwCounters[bCounterIndex]--; /*Se decrementa ese contador*/
				}
			}
		}
	gflgTimerOverflow = 0; /*Se apaga la bandera de la interrupción*/
	}
}

void vfnPitCallback(void) /*Función de Callback a la que se entra cada que el PIT manda una interrupción*/
{
	gflgTimerOverflow = 1;
	if(!gadwCounters[DIVISOR_CNT] && bfnTimeTargetReached(DURACION_CNT)) /*Si la cuenta del divisor se acabó pero aun queda duración para el tono*/
	{
		GPIOE_PDOR |= 1; /*Se encienden led y buzzer*/
		vfnLedOn(1);
	}
	else
	{
		GPIOE_PDOR &= ~1; /*Se apagan led y buzzer*/
		vfnLedOff(1);
	}
}
