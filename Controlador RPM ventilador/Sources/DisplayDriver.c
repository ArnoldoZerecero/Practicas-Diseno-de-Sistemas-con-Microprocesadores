/*
 * DisplayDriver.c
 *
 *  Created on: Sep 23, 2017
 *      Author: Jes�s Arnoldo Zerecero N��ez, Andrea Alejandra Mondrag�n Olivos
 */

#include "derivative.h" 
#include "DisplayDriver.h"
#include "MISCELANEO.h"

#define NUMERO_DISPLAYS 4

extern unsigned short gwPromedio; /*Valor leido de la velocidad del ventilador*/

const unsigned long kdwaSegmentArray[7] = {(1<<0), (1<<1), (1<<2), (1<<3), (1<<4), (1<<5), (1<<6)}; /*Arreglo de pines de salida de cada segmento*/
const unsigned long kdwaDisplayArray[NUMERO_DISPLAYS] = {(1<<8), (1<<9), (1<<10), (1<<11)}; /*Arreglo de enables de salida para cada display*/

void vfnDisplayInit(void)
{
	SIM_SCGC5 |= SIM_SCGC5_PORTE_MASK | SIM_SCGC5_PORTC_MASK; /*Se activa el clk del puerto E y del puerto B*/

	PORTC_PCR0 |= PORT_PCR_MUX(1); /*Se realiza el mux para utilizar los como GPIO*//*Segmento A*/
	PORTC_PCR1 |= PORT_PCR_MUX(1); /*Segmento B*/
	PORTC_PCR2 |= PORT_PCR_MUX(1); /*Segmento C*/
	PORTC_PCR3 |= PORT_PCR_MUX(1); /*Segmento D*/
	PORTC_PCR4 |= PORT_PCR_MUX(1); /*Segmento E*/
	PORTC_PCR5 |= PORT_PCR_MUX(1); /*Segmento F*/
	PORTC_PCR6 |= PORT_PCR_MUX(1); /*Segmento G*/

	PORTB_PCR8 |= PORT_PCR_MUX(1); /*Enable del primer display*/
	PORTB_PCR9 |= PORT_PCR_MUX(1); /*Enable del segundo display*/
	PORTB_PCR10 |= PORT_PCR_MUX(1); /*Enable del tercer display*/
	PORTB_PCR11 |= PORT_PCR_MUX(1); /*Enable del cuarto display*/

	GPIOC_PDDR |= kdwaSegmentArray[0] | kdwaSegmentArray[1] | kdwaSegmentArray[2] | kdwaSegmentArray[3] | kdwaSegmentArray[4] | kdwaSegmentArray[5] | kdwaSegmentArray[6]; /*Se utilizar�n estos pines como salidas*/
	GPIOB_PDDR |= kdwaDisplayArray[0] | kdwaDisplayArray[1] | kdwaDisplayArray[2] | kdwaDisplayArray[3];
}

void vfnDisplayDriver(void)
{
	static unsigned char bDigito; /*Variable para almacenar el d�gito a escribir en el display*/
	static unsigned char bBarridoIndex = 0; /*�ndice para realizar el barrido de los 4 displays, uno por instanciamiento*/

	if(bBarridoIndex == 0) /*Seg�n el display que se est� escribiendo actualmente, se toma el valor del nibble correspondiente de wBCD*/
	{
		bDigito = CLEAR_ALL_BUT_THOUSANDS(wfnBCD(gwPromedio));
	}
	else if(bBarridoIndex == 1)
	{
		bDigito = CLEAR_ALL_BUT_HUNDREDS(wfnBCD(gwPromedio));
	}
	else if(bBarridoIndex == 2)
	{
		bDigito = CLEAR_ALL_BUT_TENS(wfnBCD(gwPromedio));
	}
	else if(bBarridoIndex == 3)
	{
		bDigito = CLEAR_ALL_BUT_UNITS(wfnBCD(gwPromedio));
	}

	GPIOB_PDOR &= ~kdwaDisplayArray[0]; /*Se asegura que solo se vaya a escribir en un display (c�todo com�n)*/
	GPIOB_PDOR &= ~kdwaDisplayArray[1];
	GPIOB_PDOR &= ~kdwaDisplayArray[2];
	GPIOB_PDOR &= ~kdwaDisplayArray[3];

	GPIOB_PDOR |= kdwaDisplayArray[bBarridoIndex]; /*Se enciende el enable del display que se est� escribiendo actualmente*/

	if(bDigito == 0) /*Conversi�n BCD a 7 segmentos (c�todo com�n)*/
	{
		GPIOC_PDOR |= kdwaSegmentArray[0];
		GPIOC_PDOR |= kdwaSegmentArray[1];
		GPIOC_PDOR |= kdwaSegmentArray[2];
		GPIOC_PDOR |= kdwaSegmentArray[3];
		GPIOC_PDOR |= kdwaSegmentArray[4];
		GPIOC_PDOR |= kdwaSegmentArray[5];
		GPIOC_PDOR &= ~kdwaSegmentArray[6];
	}
	else if (bDigito == 1)
	{
		GPIOC_PDOR &= ~kdwaSegmentArray[0];
		GPIOC_PDOR |= kdwaSegmentArray[1];
		GPIOC_PDOR |= kdwaSegmentArray[2];
		GPIOC_PDOR &= ~kdwaSegmentArray[3];
		GPIOC_PDOR &= ~kdwaSegmentArray[4];
		GPIOC_PDOR &= ~kdwaSegmentArray[5];
		GPIOC_PDOR &= ~kdwaSegmentArray[6];
	}
	else if (bDigito == 2)
	{
		GPIOC_PDOR |= kdwaSegmentArray[0];
		GPIOC_PDOR |= kdwaSegmentArray[1];
		GPIOC_PDOR &= ~kdwaSegmentArray[2];
		GPIOC_PDOR |= kdwaSegmentArray[3];
		GPIOC_PDOR |= kdwaSegmentArray[4];
		GPIOC_PDOR &= ~kdwaSegmentArray[5];
		GPIOC_PDOR |= kdwaSegmentArray[6];
	}
	else if (bDigito == 3)
	{
		GPIOC_PDOR |= kdwaSegmentArray[0];
		GPIOC_PDOR |= kdwaSegmentArray[1];
		GPIOC_PDOR |= kdwaSegmentArray[2];
		GPIOC_PDOR |= kdwaSegmentArray[3];
		GPIOC_PDOR &= ~kdwaSegmentArray[4];
		GPIOC_PDOR &= ~kdwaSegmentArray[5];
		GPIOC_PDOR |= kdwaSegmentArray[6];
	}
	else if (bDigito == 4)
	{
		GPIOC_PDOR &= ~kdwaSegmentArray[0];
		GPIOC_PDOR |= kdwaSegmentArray[1];
		GPIOC_PDOR |= kdwaSegmentArray[2];
		GPIOC_PDOR &= ~kdwaSegmentArray[3];
		GPIOC_PDOR &= ~kdwaSegmentArray[4];
		GPIOC_PDOR |= kdwaSegmentArray[5];
		GPIOC_PDOR |= kdwaSegmentArray[6];
	}
	else if (bDigito == 5)
	{
		GPIOC_PDOR |= kdwaSegmentArray[0];
		GPIOC_PDOR &= ~kdwaSegmentArray[1];
		GPIOC_PDOR |= kdwaSegmentArray[2];
		GPIOC_PDOR |= kdwaSegmentArray[3];
		GPIOC_PDOR &= ~kdwaSegmentArray[4];
		GPIOC_PDOR |= kdwaSegmentArray[5];
		GPIOC_PDOR |= kdwaSegmentArray[6];
	}
	else if (bDigito == 6)
	{
		GPIOC_PDOR |= kdwaSegmentArray[0];
		GPIOC_PDOR &= ~kdwaSegmentArray[1];
		GPIOC_PDOR |= kdwaSegmentArray[2];
		GPIOC_PDOR |= kdwaSegmentArray[3];
		GPIOC_PDOR |= kdwaSegmentArray[4];
		GPIOC_PDOR |= kdwaSegmentArray[5];
		GPIOC_PDOR |= kdwaSegmentArray[6];
	}
	else if (bDigito == 7)
	{
		GPIOC_PDOR |= kdwaSegmentArray[0];
		GPIOC_PDOR |= kdwaSegmentArray[1];
		GPIOC_PDOR |= kdwaSegmentArray[2];
		GPIOC_PDOR &= ~kdwaSegmentArray[3];
		GPIOC_PDOR &= ~kdwaSegmentArray[4];
		GPIOC_PDOR &= ~kdwaSegmentArray[5];
		GPIOC_PDOR &= ~kdwaSegmentArray[6];
	}
	else if (bDigito == 8)
	{
		GPIOC_PDOR |= kdwaSegmentArray[0];
		GPIOC_PDOR |= kdwaSegmentArray[1];
		GPIOC_PDOR |= kdwaSegmentArray[2];
		GPIOC_PDOR |= kdwaSegmentArray[3];
		GPIOC_PDOR |= kdwaSegmentArray[4];
		GPIOC_PDOR |= kdwaSegmentArray[5];
		GPIOC_PDOR |= kdwaSegmentArray[6];
	}
	else if (bDigito == 9)
	{
		GPIOC_PDOR |= kdwaSegmentArray[0];
		GPIOC_PDOR |= kdwaSegmentArray[1];
		GPIOC_PDOR |= kdwaSegmentArray[2];
		GPIOC_PDOR |= kdwaSegmentArray[3];
		GPIOC_PDOR &= ~kdwaSegmentArray[4];
		GPIOC_PDOR |= kdwaSegmentArray[5];
		GPIOC_PDOR |= kdwaSegmentArray[6];
	}
	else /*En caso de no recibir nung�n caracter disponible, el display mostrar� un s�mbolo "-"*/
	{
		GPIOC_PDOR &= ~kdwaSegmentArray[0];
		GPIOC_PDOR &= ~kdwaSegmentArray[1];
		GPIOC_PDOR &= ~kdwaSegmentArray[2];
		GPIOC_PDOR &= ~kdwaSegmentArray[3];
		GPIOC_PDOR &= ~kdwaSegmentArray[4];
		GPIOC_PDOR &= ~kdwaSegmentArray[5];
		GPIOC_PDOR |= kdwaSegmentArray[6];
	}                   
	bBarridoIndex++; /*Se incrementa el �ndice del barrido para escribir en el siguiente display la pr�xima vez que se llame el driver*/
	if(bBarridoIndex == NUMERO_DISPLAYS) /*Si ya se barrieron todos los displays*/
	{
		bBarridoIndex = 0; /*Se reinicia el �ndice*/
	}
}
