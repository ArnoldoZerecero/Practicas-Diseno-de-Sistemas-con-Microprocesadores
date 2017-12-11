/*
 * ButtonDriver.c
 *
 *  Created on: Sep 22, 2017
 *      Author: Jesús Arnoldo Zerecero Núñez
 */

#include "derivative.h" 
#include "ButtonDriver.h"

#define NUMERO_BOTONES 2

const unsigned short kwaButtonArray[NUMERO_BOTONES] = {(1<<0), (1<<1)}; /*Arreglo de pines donde se encuentran los botones*/

static unsigned char gbEstadoBotones = 0; /*Cada bit de esta variable representa el estado de un botón*/

void vfnButtonInit(void)
{
	SIM_SCGC5 |= SIM_SCGC5_PORTB_MASK; /*Se activa el clk del puerto B*/
	
	PORTB_PCR0 |= PORT_PCR_MUX(1) | PORT_PCR_PE_MASK | PORT_PCR_PS_MASK; /*Se realiza el mux para utilizar los como GPIO en configuración pullup*/  /*Botón 1*/
	PORTB_PCR1 |= PORT_PCR_MUX(1) | PORT_PCR_PE_MASK | PORT_PCR_PS_MASK; /*Botón 2*/
	
	GPIOB_PDIR |= kwaButtonArray[0] | kwaButtonArray[1]; /*Se asegura que los botones comiencen apagados*/
}

unsigned char bfnButtonState(unsigned char bBoton) /*Revisa el estado actual del botón elegido. Recibe el pin donde se encuentra el botón (entre 0 y 3)*/
{	
	if (bBoton >= 0 && bBoton <= 1) /*Por protección, si el usuario introduce un pin que no tiene botón*/
	{
		unsigned char bBotonIn = !(GPIOB_PDIR & kwaButtonArray[bBoton]); /*Se regresa el valor leido del puerto desde el pin definido por el argumento bBoton*/
		return bBotonIn; 
	}
	return 0;
}

unsigned char bfnButtonClick(unsigned char bBoton) /*Revisa si el botón elegido se presionó y se soltó. Recibe el pin donde se encuentra el botón (entre 0 y 3)*/
{
	static unsigned char bFlags = 0; /*Variable que se setea uno de sus bits mientras un botón siga presionado, para conocer el momento de la transición de 1 a 0*/
	
	if (bBoton >= 0 && bBoton <= 1) /*Por protección, si el usuario introduce un pin que no tiene botón*/
	{
		if((gbEstadoBotones & kwaButtonArray[bBoton]) ==  1 << bBoton) /*Si el botón se encuentra presionado*/
		{
			bFlags |= kwaButtonArray[bBoton];
		}

		if(!((gbEstadoBotones & kwaButtonArray[bBoton]) == 1  << bBoton) && (bFlags & kwaButtonArray[bBoton]) == 1 << bBoton) /*Cuando el botón se suelte*/
		{
			bFlags &= ~kwaButtonArray[bBoton];
			return 1; /*Se confirma que se hizo un click*/
		}
	}
	return 0; /*No se ha hecho un click*/
}

void vfnButtonDriver(void) /*Driver que revisa los valores de los botones y realiza el debouncing en cada ciclo del big main loop*/
{
	unsigned char bBotonCnt = 0; /*Índice para realizar el barrido de botones*/
	static unsigned char baButtonRead[4]; /*Arreglo para guardar y comparar los estados anteriores del botón*/

	do /*Debouncing*/
	{
		baButtonRead[0] = bfnButtonState(bBotonCnt); /*Se lee el valor actual desde el arreglo en el botón definido por bBotonCnt*/ 
		baButtonRead[1] = bfnButtonState(bBotonCnt); /*Se lee el siguiente estado*/
		baButtonRead[2] = bfnButtonState(bBotonCnt); /*Se lee el siguiente estado*/
		baButtonRead[3] = bfnButtonState(bBotonCnt); /*Se lee el siguiente estado*/

		if(baButtonRead[0] && baButtonRead[1] && baButtonRead[2] && baButtonRead[3]) /*Si los últimos 4 estados guardados son iguales*/
		{
			gbEstadoBotones |= (1 << bBotonCnt); /*Se escribe un uno en cierto bit de la variable, debido a que se confirma que el botón fue presionado*/
		}
		else
		{
			gbEstadoBotones &= ~(1 << bBotonCnt); /*Se confirma que el botón NO ha sido presionado*/
		}
	}while (++bBotonCnt < NUMERO_BOTONES); /*El ciclo termina cuando se han revisado todos los botones*/
}
