/*
 * TimerDriver.c

 *
 *  Created on: Oct 10, 2017
 *      Author: Jes�s Arnoldo Zerecero N��ez
 */
#include "TimerDriver.h"
#include "derivative.h"
#include "LedDriver.h"


volatile unsigned long gadwCounters[NUMERO_CONTADORES]; /*Arreglo global para cada cuenta de cada contador*/

volatile unsigned char gflgTimerOverflow = 0; /*Bandera global que se setea cada que se da una interrupci�n */

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
		if(!gadwCounters[bCounter]) /*Si el contador especificado ya lleg� a cero*/
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
	if(gflgTimerOverflow) /*Si esta prendida la bandera de interrupci�n*/
	{
		unsigned char bCounterIndex = NUMERO_CONTADORES; /*�ndice para el n�mero de contadores*/
		
		while(bCounterIndex--)
		{
			if(gadwCounters[bCounterIndex]); /*Si el contador en esa posici�n aun no llega a cero*/
			{
				if(bfnTimeTargetReached(bCounterIndex)) /*Si el contador en esa posici�n aun no llega a cero*/
				{
					gadwCounters[bCounterIndex]--; /*Se decrementa ese contador*/
				}
			}
		}
	gflgTimerOverflow = 0; /*Se apaga la bandera de la interrupci�n*/
	}
}

void vfnPitCallback(void) /*Funci�n de Callback a la que se entra cada que el PIT manda una interrupci�n*/
{
	gflgTimerOverflow = 1;
	if(!gadwCounters[DIVISOR_CNT] && bfnTimeTargetReached(DURACION_CNT)) /*Si la cuenta del divisor se acab� pero aun queda duraci�n para el tono*/
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
