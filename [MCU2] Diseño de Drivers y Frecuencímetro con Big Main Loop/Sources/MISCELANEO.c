/*
 * MISCELANEO.c
 *
 *  Created on: Aug 2, 2017
 *      Author: Jesús Arnoldo Zerecero Núñez, Andrea Alejandra Mondragón Olivos
 */

#include <stdint.h>
#include <string.h>
#include "derivative.h"
#include "MISCELANEO.h"

const uint32_t kdwaPinValue[32] = {(1<<0),(1<<1),(1<<2),(1<<3),(1<<4),(1<<5),(1<<6),(1<<7),(1<<8),(1<<9),(1<<10),(1<<11),(1<<12),(1<<13),(1<<14),(1<<15),(1<<16),(1<<17),(1<<18),(1<<19),(1<<20),(1<<21),(1<<22),(1<<23),(1<<24),(1<<25),(1<<26),(1<<27),(1<<28),(1<<29),(1<<30),(1<<31)}; /*Arreglo de potencias de dos*/ 

uint16_t wfnBCD(uint16_t wResultado) /*Se obtiene una variable de 16 bits con cada valor (M C D U) en paquetes de 4 bits*/
{
	uint16_t wMillares = wResultado/1000;
	uint16_t wCentenas = (wResultado%1000)/100;
	uint16_t wDecenas = ((wResultado%1000)%100)/10;
	uint16_t wUnidades = ((wResultado%1000)%100)%10;

	uint16_t wBCD = ((wMillares << 12) | (wCentenas << 8) | (wDecenas << 4) | (wUnidades));
	return wBCD;
}

uint32_t dwfnBCDADecimal(uint8_t bUnidades, uint8_t bDecenas, uint8_t bCentenas, uint8_t bMillares) /*Operación inversa a BCD*/
{
	uint32_t dwResultado = ((bMillares*1000) + (bCentenas*100) + (bDecenas*100) + bUnidades);

	return dwResultado;
}


void vfnDelay (uint32_t dwDelay)
{
	uint32_t dwIndex = 0;
	do
	{
		dwIndex++;
	}while (dwIndex != dwDelay);
	dwIndex = 0;
}
