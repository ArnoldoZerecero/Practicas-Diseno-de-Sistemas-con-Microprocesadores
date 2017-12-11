/*
 * LedDriver.c
 *
 *  Created on: Sep 22, 2017
 *   Author: Jesús Arnoldo Zerecero Núñez, Andrea Alejandra Mondragón Olivos

 */

#include "derivative.h" 
#include "LedDriver.h"

#define NUMERO_LEDS 3 /*Se realizará un arreglo de estrucutras de este tamaño para los leds*/

extern unsigned long kdwaPinValue[32]; /*Se utilizará el arreglo externo de potencias de dos*/

typedef struct /*Estructura de control para el led blink*/
{
	unsigned short wCycles; /*Número de ciclos que dió el usuario, los cuales se reducirán uno por uno hasta llegar a cero*/
	unsigned short wOnCycles; /*Aquí se almacenará el valor de reset para el tiempo de encendido*/
	unsigned short wOffCycles; /*Aquí se almacenará el valor de reset para el tiempo de apagado*/
	unsigned short wOnCount; /*Tiempo de encendido*/ 
	unsigned short wOffCount; /*Tiempo de apagado*/
}tLEDCtrl;

static tLEDCtrl _saLEDCtrl[NUMERO_LEDS]; /*Arreglo de estructuras de control para el led blink*/


typedef struct /*Estructura para el puerto donde se encuentra el led*/
{
	volatile unsigned long* dwpLEDPort; /*Puerto A,B,C,D o E*/
	unsigned char bLEDPos; /*Número de pin del puerto*/
}tLEDPort;


static const tLEDPort ktaLEDPort[NUMERO_LEDS] = /*Arreglo de estructuras para el puerto de cada led*/
{
	{
		(volatile unsigned long*) &GPIOD_PDOR, /*Led azul en Puerto D pin 1*/
		1
	},
	{
		(volatile unsigned long*) &GPIOB_PDOR, /*Led rojo en Puerto B pin 18*/
		18
	},
	{
		(volatile unsigned long*) &GPIOB_PDOR, /*Led verde en Puerto B pin 19*/
		19
	}
};

void vfnLedInit(void) /*Función de inicialización*/
{
	SIM_SCGC5 |= (SIM_SCGC5_PORTB_MASK | SIM_SCGC5_PORTD_MASK); /*Se activa el clk del puerto B y el puerto D*/
	
	PORTD_PCR1 |= PORT_PCR_MUX(1); /*Se realiza el mux para utilizar los pines como GPIO*/
	PORTB_PCR18 |= PORT_PCR_MUX(1);
	PORTB_PCR19 |= PORT_PCR_MUX(1);
	
	GPIOD_PDOR |= kdwaPinValue[1]; /*Se setea el PTD1 para que el led azul comienze apagado*/
	GPIOD_PDDR |= kdwaPinValue[1]; /*Se asigna el PTD1 como salida*/
	
	GPIOB_PDOR |= kdwaPinValue[18] | kdwaPinValue[19]; /*Se setean el PTB18 y PTB19 para que los leds rojo y verde comiencen apagados*/
	GPIOB_PDDR |= kdwaPinValue[18] | kdwaPinValue[19]; /*Se asignan PTB18 y PTB19 como salidas*/
}

void vfnLedOn(unsigned char bLED) /*Función para encender algún led*/
{
	tLEDPort *psLEDPort = (tLEDPort *)&ktaLEDPort[bLED]; /*Se crea un apuntador al arreglo de estructuras en la posición definida por bLED*/
	*(psLEDPort->dwpLEDPort) &= ~kdwaPinValue[psLEDPort->bLEDPos]; /*Se apaga el pin definido por el arreglo de potencias kdwPinValue en la posición bLEDPos del puerto definido por dwpLEDPort*/
}

void vfnLedOff(unsigned char bLED) /*Función para apagar algún led*/
{
	tLEDPort *psLEDPort = (tLEDPort *) &ktaLEDPort[bLED]; /*Se crea un apuntador al arreglo de estructuras en la posición definida por bLED*/
	*(psLEDPort->dwpLEDPort) |= kdwaPinValue[psLEDPort->bLEDPos];	/*Se setea el pin definido por el arreglo de potencias kdwPinValue en la posición bLEDPos del puerto definido por dwpLEDPort*/
}

void vfnLedToggle(unsigned char bLED) /*Función para togglear algún led*/
{
	tLEDPort *psLEDPort = (tLEDPort *) &ktaLEDPort[bLED]; /*Se crea un apuntador al arreglo de estructuras en la posición definida por bLED*/
	*(psLEDPort->dwpLEDPort) ^= kdwaPinValue[psLEDPort->bLEDPos];	/*Se togglea (xor) el pin definido por el arreglo de potencias kdwPinValue en la posición bLEDPos del puerto definido por dwpLEDPort*/
}

unsigned char bfnLedBusy (unsigned char bLED) /*Función para saber si aún le quedan ciclos restantes al blink de algún led*/
{
	tLEDCtrl *psLEDCtrl = &_saLEDCtrl[bLED]; /*Se crea un apuntador al arreglo de estructuras de control de blink en la posición definida por bLED*/
	return (psLEDCtrl->wCycles ? 1 : 0 ); /*Si aún quedan ciclos, se regresa un 1, de lo contrario, se regresa un cero*/
}


unsigned char bfnLedBlink (unsigned char bLED, unsigned short wTimeOn, unsigned short wTimeOff, unsigned short wCycles) /*Función para realizar un patrón determinado con un led*/
{
	if (bfnLedBusy(bLED)) /*Si el led está ocupado*/
	{
		return 0; /*La función termina, se regresa un cero*/
	}
	else
	{
		tLEDCtrl *psLEDCtrl = &_saLEDCtrl[bLED]; /*Se crea un apuntador al arreglo de estructuras de control de blink en la posición definida por bLED*/
		if (wCycles && wTimeOn && wTimeOff) /*Si se definieron ciclos, tiempo de encendido y tiempo de apagado*/
		{
			psLEDCtrl->wCycles = wCycles; /*Se guardan los valores respectivos en la estructura*/
			psLEDCtrl->wOffCount = wTimeOff;
			psLEDCtrl->wOffCycles = wTimeOff;
			psLEDCtrl->wOnCount = wTimeOn;
			psLEDCtrl->wOnCycles = wTimeOn;
			vfnLedOn(bLED); /*El led comienza encendido*/
		}
		return 1; /*Regresa un uno si la función realizó algo*/
	}
} 


void vfnLedDriver(void) /*Driver que actualiza los valores de los leds en cada ciclo del big main loop*/
{
	unsigned char bLEDCnt = 0; /*Índice para el arreglo de estrucutras*/
	tLEDCtrl *psLEDCtrl = &_saLEDCtrl[0]; /*Se crea un apuntador al arreglo de estructuras de control de blink en la primera posición*/
	do
	{
		if(psLEDCtrl->wCycles) /*Si aún quedan ciclos para ese led*/
		{
			if (!psLEDCtrl->wOnCount) /*Si ya no queda tiempo de encendido*/
			{
				if (!psLEDCtrl->wOffCount) /*Si tampoco queda tiempo de apagado*/
				{
					psLEDCtrl->wCycles--; /*Se reduce el número de ciclos*/
					psLEDCtrl->wOnCount = psLEDCtrl->wOnCycles; /*Se recargan los valores iniciales de las cuentas*/
					psLEDCtrl->wOffCount = psLEDCtrl->wOffCycles;
				}
				else 
				{
					psLEDCtrl->wOffCount--; /*Se reduce en uno el tiempo de apagado*/
					vfnLedOff(bLEDCnt); /*Se apaga el led*/
				}
			}
			else
			{
				psLEDCtrl->wOnCount--; /*Se reduce en uno el tiempo de encendido*/
				vfnLedOn(bLEDCnt); /*Se enciende el led*/
			}
		}
		psLEDCtrl++; /*Se leerá la siguiente estructura del arreglo (los valores del siguiente led)*/
	}while (++bLEDCnt < NUMERO_LEDS); /*Hasta que se hayan leido las estructuras de cada led*/
}
