/*
 * MISCELANEO.c
 *
 *  Created on: Aug 2, 2017
 *      Author: Alumnos
 */

#include <stdint.h>
#include "derivative.h"
#include "MISCELANEO.h"

const uint32_t kdwaPinValue[32] = {(1<<0),(1<<1),(1<<2),(1<<3),(1<<4),(1<<5),(1<<6),(1<<7),(1<<8),(1<<9),(1<<10),(1<<11),(1<<12),(1<<13),(1<<14),(1<<15),(1<<16),(1<<17),(1<<18),(1<<19),(1<<20),(1<<21),(1<<22),(1<<23),(1<<24),(1<<25),(1<<26),(1<<27),(1<<28),(1<<29),(1<<30),(1<<31)}; /*Arreglo de potencias de dos*/ 


uint16_t wfnBCD(uint16_t wResultado) /*Se obtiene una variable de 16 bits con cada valor (C D U) en paquetes de 4 bits*/
{
	uint16_t wMillares = wResultado/1000;
	uint16_t wCentenas = (wResultado%1000)/100;
	uint16_t wDecenas = ((wResultado%1000)%100)/10;
	uint16_t wUnidades = ((wResultado%1000)%100)%10;

	uint16_t wBCD = ((wMillares << 12) | (wCentenas << 8) | (wDecenas << 4) | (wUnidades));
	return wBCD;
}

uint16_t wfnHexCharAHex (uint8_t bUnidades, uint8_t bDecenas, uint8_t bCentenas, uint8_t bMillares)
{
	uint16_t wHex = ((bMillares << 12) | (bCentenas << 8) | (bDecenas << 4) | (bUnidades));
	return wHex;
}

uint8_t bfnDecimalAHexChar (uint8_t bDecimal)
{
	if(bDecimal > 9)
	{
		return bDecimal + 7;
	}
	return bDecimal;
}

uint16_t wfnHexCharADecimal (uint8_t bUnidades, uint8_t bDecenas, uint8_t bCentenas, uint8_t bMillares)
{
	if(bUnidades == 'A')
	{
		bUnidades = 10;
	}
	else if(bUnidades == 'B')
	{
		bUnidades = 11;
	}
	else if(bUnidades == 'C')
	{
		bUnidades = 12;
	}
	else if(bUnidades == 'D')
	{
		bUnidades = 13;
	}
	else if(bUnidades == 'E')
	{
		bUnidades = 14;
	}
	else if(bUnidades == 'F')
	{
		bUnidades = 15;
	}
	else
	{
		bUnidades = bUnidades - 48;
	}
	
	if(bDecenas == 'A')
	{
		bDecenas = 10;
	}
	else if(bDecenas == 'B')
	{
		bDecenas = 11;
	}
	else if(bDecenas == 'C')
	{
		bDecenas = 12;
	}
	else if(bDecenas == 'D')
	{
		bDecenas = 13;
	}
	else if(bDecenas == 'E')
	{
		bDecenas = 14;
	}
	else if(bDecenas == 'F')
	{
		bDecenas = 15;
	}
	else
	{
		bDecenas = bDecenas - 48;
	}
	
	if(bCentenas == 'A')
	{
		bCentenas = 10;
	}
	else if(bCentenas == 'B')
	{
		bCentenas = 11;
	}
	else if(bCentenas == 'C')
	{
		bCentenas = 12;
	}
	else if(bCentenas == 'D')
	{
		bCentenas = 13;
	}
	else if(bCentenas == 'E')
	{
		bCentenas = 14;
	}
	else if(bCentenas == 'F')
	{
		bCentenas = 15;
	}
	else
	{
		bCentenas = bCentenas - 48;
	}
	
	if(bMillares == 'A')
	{
		bMillares = 10;
	}
	else if(bMillares == 'B')
	{
		bMillares = 11;
	}
	else if(bMillares == 'C')
	{
		bMillares = 12;
	}
	else if(bMillares == 'D')
	{
		bMillares = 13;
	}
	else if(bMillares == 'E')
	{
		bMillares = 14;
	}
	else if(bMillares == 'F')
	{
		bMillares = 15;
	}
	else
	{
		bMillares = bMillares - 48;
	}
	
	return (bMillares*4096 + bCentenas*256 + bDecenas*16 + bUnidades);
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
