/*
 * FloatFunctions.c
 *
 *  Created on: Nov 19, 2017
 *      Author: Jesús Arnoldo Zerecero Núñez
 */

#include "FloatFunctions.h"
#include <math.h> /*Para utilizar la representación del infinito positivo y negativo*/

float ffnInt2Float (short iNum) /*Convierte de short int a notación de punto flotante IEEE 754*/
{
	static unsigned char _bSign = 0; /*Variable que almacena el signo*/
	static long _dwTemporal = 0; /*Variable temporal para almacenar el entero*/
	unsigned char bExponent = 0; /*Variable que almacena el exponente*/
	static long _dwMantisa = 0; /*Variable que almacena el entero para luego convertirlo en la mantisa*/
	long dwResultado = 0; /*Variable que almacena el resultado*/

	/*Signo*/
	if(iNum > 0) /*Primero se revisa si es un número negativo o positivo*/
	{
		_bSign = 0; /*Signo positivo*/
	}
	else if (iNum < 0)
	{
		_bSign = 1; /*Signo negativo*/
		iNum--; /*Debido a que el número se encuentra en complemento A2, primero debe se le debe restar uno y luego invertirlo*/
		iNum = ~iNum;
	}
	else
	{
		return 0; /*El número es igual a cero*/
	}
	
	/*Exponente*/
	_dwTemporal = iNum;
	while(_dwTemporal != 1 && _dwTemporal != 0xFFFFFFFF) /*Se recorre el entero hasta dejar solo "un uno a la izquierda del punto". El exponente representa las veces que se recorrió el punto*/
	{
		_dwTemporal = _dwTemporal >> 1;
		bExponent++;
	}
	bExponent = bExponent + 127; 
			
	/*Mantisa*/
	_dwMantisa = iNum;
	if((_dwMantisa & (1<<31)) || (_dwMantisa & (1<<30)) || (_dwMantisa & (1<<29)) || (_dwMantisa & (1<<28)) || (_dwMantisa & (1<<27)) || (_dwMantisa & (1<<26)) || (_dwMantisa & (1<<25)) || (_dwMantisa & (1<<24))) /*Si la mantisa tiene números superiores a sus 23 bits de tamaño*/
	{
		_dwMantisa = 0; /*La mantisa de 16 bits será 0*/
	}
	else if(_dwMantisa)
	{
		while(!(_dwMantisa & (1<<23))) /*Se recorre la mantisa para llenarla de ceros a su derecha, hasta que sea de 23 bits*/
		{
			_dwMantisa = _dwMantisa << 1;
		}
		_dwMantisa &= ~(1<<23); /*Se quita el bit 23 debido a que representa el uno a la izquierda del punto*/
	}
	
	dwResultado = (_bSign << 31) | (bExponent << 23) | _dwMantisa; /*Se acomodan las variables para concordar con el estandar*/
	return dwResultado;
}

float ffnLong2Float (long iNum) /*Convierte de long int a notación de punto flotante IEEE 754*/
{
	static unsigned char _bSign = 0; /*Variable que almacena el signo*/
	static long _dwTemporal = 0; /*Variable temporal para almacenar el entero*/
	unsigned char bExponent = 0; /*Variable que almacena el exponente*/
	static long _dwMantisa = 0; /*Variable que almacena el entero para luego convertirlo en la mantisa*/
	long dwResultado = 0; /*Variable que almacena el resultado*/

	/*Signo*/
	if(iNum > 0) /*Primero se revisa si es un número negativo o positivo*/
	{
		_bSign = 0; /*Signo positivo*/
	}
	else if (iNum < 0)
	{
		_bSign = 1; /*Signo negativo*/
		iNum--; /*Debido a que el número se encuentra en complemento A2, primero debe se le debe restar uno y luego invertirlo*/
		iNum = ~iNum;
	}
	else
	{
		return 0; /*El número es igual a cero*/
	}
	
	/*Exponente*/
	_dwTemporal = iNum;
	while(_dwTemporal != 1  && _dwTemporal != 0xFFFFFFFF) /*Se recorre el entero hasta dejar solo "un uno a la izquierda del punto. El exponente representa las veces que se recorrió el punto*/
	{
		_dwTemporal = _dwTemporal >> 1;
		bExponent++;
	}
	bExponent = bExponent + 127; 
			
	/*Mantisa*/
	_dwMantisa = iNum;
	/*Si la mantisa es mayor a 23 bits, se debe recorrer hasta que su MSB se encuentre en el bit 23*/
	if(_dwMantisa & (1<<31))
	{
		_dwMantisa = _dwMantisa >> 8; 
	}
	else if(_dwMantisa & (1<<30))
	{
		_dwMantisa = _dwMantisa >> 7; 
	}
	else if(_dwMantisa & (1<<29))
	{
		_dwMantisa = _dwMantisa >> 6; 
	}
	else if(_dwMantisa & (1<<28))
	{
		_dwMantisa = _dwMantisa >> 5; 
	}
	else if(_dwMantisa & (1<<27))
	{
		_dwMantisa = _dwMantisa >> 4; 
	}
	else if(_dwMantisa & (1<<26))
	{
		_dwMantisa = _dwMantisa >> 3; 
	}
	else if(_dwMantisa & (1<<25))
	{
		_dwMantisa = _dwMantisa >> 2; 
	}
	else if(_dwMantisa & (1<<24))
	{
		_dwMantisa = _dwMantisa >> 1; 
	}
	else if(_dwMantisa)
	{
		while(!(_dwMantisa & (1<<23))) /*Se recorre la mantisa para llenarla de ceros a su derecha, hasta que sea de 23 bits*/
		{
			_dwMantisa = _dwMantisa << 1;
		}
	}
	_dwMantisa &= ~(1<<23); /*Se quita el bit 23 debido a que representa el uno a la izquierda del punto*/
	dwResultado = (_bSign << 31) | (bExponent << 23) | _dwMantisa; /*Se acomodan las variables para concordar con el estandar*/
	return dwResultado;
}

short ifnFloat2Int (float fNum) /*Convierte de punto flotante IEEE 754 a un entero*/
{
	if(fNum == 0) /*Si el número es cero*/
	{
		return 0;
	}
	
	long dwNum = fNum; /*Variable de 32 bits que almacena al valor flotante para trabajar con corrimientos con él*/
	static unsigned char _bSign = 0; /*Variable para leer el signo*/
	long dwTemporal = fNum; /*Variable para almacenar el flotante temporalmente*/
	static signed char _bExponente = 0; /*Variable para leer el exponente*/
	
	if(dwNum & (1<<31)) /*Si el bit 32 es uno*/
	{
		_bSign = 1; /*Es un número negativo*/
	}
	else
	{
		_bSign = 0; /*Es un número positivo*/
	}
	
	dwTemporal = dwTemporal >> 23; /*Se recorre la variable hasta dejar solo el exponente y el signo*/
	dwTemporal &= ~(1<<8); /*Se quita el bit de signo*/
	_bExponente = dwTemporal - 127; /*Se quita 127 para saber el exponente del número*/
	
	dwNum &= CLEAR_UPPER_9_BITS; /*Se limpian el signo y el exponente*/
	dwNum |= (1<<23); /*Se agrega el bit 23 que se quitó debido a que representa el uno a la izquierda del punto*/ 
	dwNum = dwNum >> (23 - _bExponente); /*Se recorre el número para quitar los ceros que tenía a su derecha*/
	
	if(_bSign) /*Si se trata de un número negativo*/
	{
		dwNum = ~dwNum; /*Se aplica complemento A2 al invertir y agregar 1*/
		dwNum++;
	}
	
	if(_bExponente > 23) /*Si el número se sale del rango de 16 bits*/
	{
		return INFINITY;
	}
	else if(_bExponente < 0)
	{
		return -INFINITY;
	}
	
	return dwNum;
}

float ffnFloatAdd (float fA, float fB) /*Suma de dos flotantes*/
{
	short intA = ifnFloat2Int (fA); /*Se convierten los flotantes a enteros*/
	short intB = ifnFloat2Int (fB);
	long dwSumaResultante = 0;
	
	if((intA == 0 && fA != 0) || (intA == -1 && fA != -1) || (intB == 0 && fB != 0) || (intB == -1 && fB != -1)) /*Si se regresa un 0 o un -1 como entero, y el flotante de entrada no es 0 o -1, quiere decir que el número de entrada es mayor a 16 bits*/
	{
		return INFINITY;
	}

	dwSumaResultante =  intA + intB;
		
	return ffnLong2Float(dwSumaResultante);
}

float ffnFloatSub (float fA, float fB) /*Resta de dos flotantes*/
{
	short intA = ifnFloat2Int (fA); /*Se convierten los flotantes a enteros*/
	short intB = ifnFloat2Int (fB);
	long dwRestaResultante = 0;

	if((intA == 0 && fA != 0) || (intA == -1 && fA != -1) || (intB == 0 && fB != 0) || (intB == -1 && fB != -1)) /*Si se regresa un 0 o un -1 como entero, y el flotante de entrada no es 0 o -1, quiere decir que el número de entrada es mayor a 16 bits*/
	{
		return INFINITY;
	}
	
	dwRestaResultante =  intA - intB;
	
	return ffnLong2Float(dwRestaResultante);
}

char bfnFloatCmp (float fA, float fB) /*Compara 2 flotantes*/
{
	short intA = ifnFloat2Int (fA); /*Se convierten los flotantes a enteros*/
	short intB = ifnFloat2Int (fB);
	
	if((intA == 0 && fA != 0) || (intA == -1 && fA != -1) || (intB == 0 && fB != 0) || (intB == -1 && fB != -1)) /*Si se regresa un 0 o un -1 como entero, y el flotante de entrada no es 0 o -1, quiere decir que el número de entrada es mayor a 16 bits*/
	{
		return INFINITY;
	}
	
	if(intA > intB) 
	{
		return 1;
	}
	else if(intA < intB)
	{
		return -1;
	}
	else
	{
		return 0;
	}
}

float ffnFloatMpy (float fA, float fB) /*Multiplicación de dos flotantes*/
{
	short intA = ifnFloat2Int (fA); /*Se convierten los flotantes a enteros*/
	short intB = ifnFloat2Int (fB);
	long dwMultiplicacionResultante = 0;
	
	if((intA == 0 && fA != 0) || (intA == -1 && fA != -1) || (intB == 0 && fB != 0) || (intB == -1 && fB != -1)) /*Si se regresa un 0 o un -1 como entero, y el flotante de entrada no es 0 o -1, quiere decir que el número de entrada es mayor a 16 bits*/
	{
		return INFINITY;
	}
	
	dwMultiplicacionResultante = intA*intB;
	
	return ffnLong2Float(dwMultiplicacionResultante);
}

float ffnFloatDiv (float fA, float fB)
{
	short intA = ifnFloat2Int (fA); /*Se convierten los flotantes a enteros*/
	short intB = ifnFloat2Int (fB);
	long dwDivisionResultante = 0;
	
	if((intA == 0 && fA != 0) || (intA == -1 && fA != -1) || (intB == 0 && fB != 0) || (intB == -1 && fB != -1)) /*Si se regresa un 0 o un -1 como entero, y el flotante de entrada no es 0 o -1, quiere decir que el número de entrada es mayor a 16 bits*/
	{
		return INFINITY;
	}
	
	dwDivisionResultante = intA/intB;
	
	return ffnLong2Float(dwDivisionResultante);
}

float ffnFloatMod (float fA, float fB)
{
	short intA = ifnFloat2Int (fA); /*Se convierten los flotantes a enteros*/
	short intB = ifnFloat2Int (fB);
	long dwModuloResultante = 0;
	
	if((intA == 0 && fA != 0) || (intA == -1 && fA != -1) || (intB == 0 && fB != 0) || (intB == -1 && fB != -1)) /*Si se regresa un 0 o un -1 como entero, y el flotante de entrada no es 0 o -1, quiere decir que el número de entrada es mayor a 16 bits*/
	{
		return INFINITY;
	}
	
	dwModuloResultante = intA%intB;
	
	return ffnLong2Float(dwModuloResultante);
}
