/*
 * Funciones.c
 * 
 *
 *  Created on: Sep 10, 2017
 *      Author: Jesús Arnoldo Zerecero Núñez
 */
#include "Funciones.h"


void vfnMemCpy (unsigned char * bpSource, unsigned char * bpDest, unsigned short wSize)
{
	while (wSize--) /*El ciclo continuará hasta que se hayan recorrido todos los elementos de ambos arreglos, es decir, hasta que el valor del número de elementos especificado sea 0*/
	{
		*bpDest++ = *bpSource++; /*El valor a donde apunta el apuntador destino es reemplazado por el valor al cual apunta el apuntador fuente*/
	}
}

void vfnMemSet(unsigned char * bpDest, unsigned char bByteToFill, unsigned short wSize)
{
	while (wSize--) /*El ciclo continuará hasta que se hayan recorrido todos los elementos del arreglo, es decir, hasta que el valor del número de elementos especificado sea 0*/
	{
		*bpDest++ = bByteToFill; /*La posición actual del arreglo adquiere el caracter especificado*/
	}
}

unsigned char bfnFindMax(unsigned char * bpDest, unsigned short wSize)
{
	unsigned char bMax = 0; /*Variable de retorno, en donde terminará el caracter de mayor valor*/
	while (wSize--) /*El ciclo continuará hasta que se hayan recorrido todos los elementos del arreglo, es decir, hasta que el valor del número de elementos especificado sea 0*/
	{
		if (*bpDest > bMax)/*Si la posición actual es mayor al valor máximo encontrado hasta el momento*/
		{
			bMax = *bpDest; /*bMax adquiere ese nuevo valor, debido a que será el nuevo valor mayor*/
		}
		bpDest++; /*El apuntador se incrementa a la siguiente posición del arreglo*/
	}
	return bMax; /*Se regresa el mayor valor encontrado*/
}

unsigned char bfnFindMin(unsigned char * bpDest, unsigned short wSize)
{
	unsigned char bMin = 255; /*Variable de retorno, en donde terminará el caracter de menor valor*/
	while (wSize--) /*El ciclo continuará hasta que se hayan recorrido todos los elementos del arreglo, es decir, hasta que el valor del número de elementos especificado sea 0*/
	{
		if (*bpDest < bMin)/*Si la posición actual es menor al valor mínimo encontrado hasta el momento*/
		{
			bMin = *bpDest; /*bMin adquiere ese nuevo valor, debido a que será el nuevo valor menor*/
		}
		bpDest++; /*El apuntador se incrementa a la siguiente posición del arreglo*/
	}
	return bMin; /*Se regresa el menor valor encontrado*/
}

unsigned char bfnStrCmp(unsigned char * bpSource, unsigned char * bpDest, unsigned short wSize)
{
	while (wSize--) /*El ciclo continuará hasta que se hayan recorrido todos los elementos de ambos arreglos, es decir, hasta que el valor del número de elementos especificado sea 0*/
	{
		if (*bpSource++ != *bpDest++) /*En caso de que el contenido de los apuntadores sea diferente, la función regresa un 0*/
		{
			return 0;
		}
	}
	return 1; /*Si se recorrieron todos los elementos y la función salió del ciclo, quiere decir que los arreglos son iguales*/
}

unsigned char * bpfnByteAddress(unsigned char * bpString, unsigned char bCharToFind, unsigned short wSize)
{
	while (wSize--) /*El ciclo continuará hasta que se hayan recorrido todos los elementos del arreglo, es decir, hasta que el valor del número de elementos especificado sea 0*/
	{
		if (*bpString == bCharToFind) /*Si se encuentra una posición del arreglo que contenga el valor de bCharToFind*/
		{
			return bpString; /*Se retorna esa posición*/
		}
		bpString++;/*El apuntador se incrementa a la siguiente posición del arreglo*/
	}
	return '\0'; /*Si no se encontró un valor igual a bCharToFind, se regresa un apuntador a NULL*/
}

void vfnSort (unsigned char * bpString, unsigned short wStringSize)
{
	unsigned short wIndice = 0; /*Se crea una variable para el índice y se inicia en cero*/
	unsigned char *bpApuntadorSiguienteElemento; /*Se declara un nuevo apuntador que comparará los siguientes elementos con el apuntador base actual (bpString)*/
	unsigned char bTemporal; /*Se crea una variable temporal para evitar pérdida de datos*/
	unsigned char bOffset = 1; /*Esta variable determina cuántas veces le falta por recorrerse el *bApuntadorSiguienteElemento para llegar al final del arreglo. Se inicializa en uno debido a que el *bApuntadorSiguienteElemento comienza en la posición [1] del arreglo*/

	do /*Comienza el primer ciclo*/
	{
		bpApuntadorSiguienteElemento = bpString + 1; /*El apuntador para el siguiente elemento siempre comienza uno por delante del apuntador base*/
		do /*Comienza el segundo ciclo*/
		{
			if (*bpString > *bpApuntadorSiguienteElemento) /*En caso de que sea mayor el valor base (de la izquierda), se intercambia con el de la derecha*/
			{
				bTemporal = *bpApuntadorSiguienteElemento; /*Se guarda el elemento al que apunta el *bApuntadorSiguienteElemento en bTemporal para no perderlo*/
				*bpApuntadorSiguienteElemento = *bpString; /**bApuntadorSiguienteElemento adquiere el valor del elemento al que apunta *bApuntadorArreglo*/
				*bpString = bTemporal; /*El apuntador base adquiere el valor en el que estaba el *bApuntadorSiguienteElemento, el cual se guardó en bTemporal*/
			}
			else /*En caso de que el elemento de la izquierda sea menor, quiere decir que se encuentra en orden, y ninguna acción ocurre*/
			{
			}
			bpApuntadorSiguienteElemento++; /*Se incrementa en uno el bApuntadorSiguienteElemento para apuntar a la siguiente posición de la cadena*/
			wIndice++; /*Se incrementa en uno el índice*/
		}
		while ((wIndice != (wStringSize - bOffset)) && wStringSize != 1); /*El ciclo interno continuará hasta que se haya recorrido bApuntadorSiguienteElemento hasta el último elemento. En caso de que el arreglo contenga un único elemento, el ciclo también finalizará*/
		wIndice = 0; /*El índice se reinicia a 0 antes de volver a comenzar el ciclo*/
		bpString++; /*El apuntador base se recorre al siguiente elemento, lo que significa que el elemento en el que estaba ya quedó ordenado*/
		bOffset++; /*El bOffset se incrementa en uno, lo cual indica que en el próximo ciclo, el bApuntadorSiguienteElemento tedrá que recorrerse una vez menos para llegar al final del arreglo*/
	}while(bOffset != wStringSize && wStringSize != 1); /*El ciclo principal termina cuando el bOffset se incrementa hasta ser igual al número de elementos, lo cual significa que el apuntador base (bpString) ya ha pasado por todos los elementos.  En caso de que el arreglo contenga un único elemento, el ciclo también finalizará*/
}

unsigned short wfnStrLen (unsigned char * bpString)
{
	unsigned short wAcumulador = 0; /*Se declara una variable para llevar el conteo del número de caracteres*/
	while (*bpString++ != 0) /*El ciclo termina cuando el apuntador llegue al nulo*/
	{
		wAcumulador++; /*Se incrementa en uno el acumulador*/
	}
	return wAcumulador; /*Se regresa el valor de bAcumulador a main*/
}

unsigned short wfnSprintf (char * bpString, const char * bpFormat, void * vpaExtraArguments[])
{
	unsigned short wSize = 0; /*Variable para medir el tamaño de caracteres de la cadena destino*/
	unsigned char bIndiceApuntador = 0; /*Variable para recorrer los apuntadores (argumentos) almacenados en el arreglo*/
	unsigned char bIndiceArregloContenido = 0; /*Variable para recorrer los arreglos a los cuales apuntan los apuntadores del arreglo*/
	unsigned char bTemporal; /*Variable para almacenar temporalmente valores para cualquier conversión*/
	unsigned char bNumeroDigitos = 0; /*Variable para conocer el tamaño de los dígitos a escribir en la cadena fuente para cualquier conversión*/
	unsigned char bEspaciosDiferencia = 0; /*Variable para saber cuántos espacios hay que saltar para volver al siguiente espacio vacío de la cadena destino en cualquier conversión*/
	unsigned char bResiduoHex; /*Variable para el residuo de las divisiones sobre 16 en el cálculo dec - hex*/
	unsigned char bLecturaBin; /*Variable que lee el valor de la actual posición del arreglo de parámetros en el cálculo dec - bin*/
	unsigned char bResiduoBin; /*Variable para el residuo de las divisiones sobre 2 en el cálculo dec - bin*/
	unsigned long dwPotenciaBin = 1; /*Variable para recorrerse por las potencias de 2 (multiplicación por 10)*/
	unsigned long dwTemporalBin; /*Variable para almacenar temporalmente el resultado del cálculo dec - bin*/
	unsigned long dwResultadoBin = 0; /*Variable para almacenar el resultado del cálculo dec - bin*/

	do /*Comienza el ciclo*/
	{
		if (*bpFormat == '%' && *(bpFormat + 1) == 'c') /*Si bpFormat indica que se aproxima un modificador para caracter*/
		{
			*bpString = *(char *)(*(vpaExtraArguments + bIndiceApuntador)+ bIndiceArregloContenido); /*Se toma el valor del arreglo de apuntadores*/
			bpString++; /*Se incrementa el apuntador del arreglo fuente, para escribir el siguiente dato*/
			bIndiceApuntador++; /*Se recorre al siguiente argumento*/
			bpFormat = bpFormat + 2; /*Se recorre en 2 bpFormat para no escribir el argumento de conversión*/
			wSize++; /*Se incrementa la variable del tamaño del arreglo destino*/
		}
		else if (*bpFormat == '%' && *(bpFormat + 1) == 'd') /*Si el modificador es para número en decimal*/
		{
			bTemporal = *(unsigned char *)(*(vpaExtraArguments + bIndiceApuntador)+ bIndiceArregloContenido); /*Se almacena el valor del argumento en bTemporalDec*/

			while (bTemporal != 0) /*Se calcula el número de dígitos*/
			{
				bTemporal = bTemporal / 10;
				bNumeroDigitos++;
			}

			bTemporal = *(unsigned char *)(*(vpaExtraArguments + bIndiceApuntador)+ bIndiceArregloContenido); /*Se almacena el valor del argumento en bTemporalDec*/
			bpString = bpString + bNumeroDigitos - 1; /*Se deja espacio para escribir el número de dígitos, debido a que se escribirán de LSB  a MSB*/

			while (bNumeroDigitos--)
			{
				*bpString = bTemporal % 10; /*Se escriben primero las unidades, luego las decenas y al final las centenas*/
				bTemporal = bTemporal / 10;
				bpString--;
				wSize++; /*Se incrementa la variable del tamaño del arreglo destino*/
				bEspaciosDiferencia++;
			}
			bpString = bpString + bEspaciosDiferencia + 1; /*Se salta el espacio escrito hasta el siguente espacio vacío a escribir*/
			bIndiceApuntador++; /*Se recorre al siguiente argumento*/
			bEspaciosDiferencia = 0; /*Se reinician los espacios para poder ser utilizados en otra conversión*/
			bpFormat = bpFormat + 2; /*Se recorre en 2 bpFormat para no escribir el argumento de conversión*/
		}
		else if (*bpFormat == '%' && *(bpFormat + 1) == 's')/*Si el modificador es para escribir una cadena*/
		{
			while (*(char *)(*(vpaExtraArguments + bIndiceApuntador)+ bIndiceArregloContenido) != 0) /*Mientras no se haya llegado al nulo de la cadena mandada como parámetro*/
			{
				*bpString = *(char *)(*(vpaExtraArguments + bIndiceApuntador)+ bIndiceArregloContenido); /*Se guarda caracter por caracter en el arreglo destino*/
				bIndiceArregloContenido++; /*Se recorre al siguiente elemento del arreglo apuntado*/
				bpString++; /*Se incrementa el apuntador del arreglo fuente, para escribir el siguiente dato*/
				wSize++; /*Se incrementa la variable del tamaño del arreglo destino*/
			}
			bIndiceArregloContenido = 0; /*Se reinicia el índice para los demás arreglos*/
			bIndiceApuntador++; /*Se recorre al siguiente argumento*/
			bpFormat = bpFormat + 2; /*Se recorre en 2 bpFormat para no escribir el argumento de conversión*/
		}
		else if (*bpFormat == '%' && *(bpFormat + 1) == 'x') /*Si el modificador es para número en hexadecimal*/
		{	
			bTemporal = *(unsigned char *)(*(vpaExtraArguments + bIndiceApuntador)+ bIndiceArregloContenido); /*Se almacena el valor del parámetro leído en la variable temporal*/

			while (bTemporal != 0) /*Se cuenta cuántos dígitos tiene el resultado hexadecimal*/
			{
				bTemporal = bTemporal/16; /*Cada que se pueda dividir el número sobre 16, se incrementa el número de dígitos resultantes*/
				bNumeroDigitos++;
			}
			bNumeroDigitos++;
			bpString = bpString + bNumeroDigitos - 1; /*Debido a que se desea guardar en una cadena el resultado, de izquierda a derecha ("MSB a LSB"), debemos reversear el orden en que se acomodan los datos. Se empezará escribiendo desde el LSB, primero dejando espacio para el número de dígitos resultante, retrocediendo hacia al izquierda hasta llenar el espacio*/
			bTemporal = *(unsigned char *)(*(vpaExtraArguments + bIndiceApuntador)+ bIndiceArregloContenido); /*Se almacena el valor del parámetro leído en la variable del dividendo nuevamente, para reiniciarlo y ahora hacer la conversión*/

			while (bNumeroDigitos--) /*Mientras aun falten dígitos para terminar el resultado*/
			{
				bResiduoHex = bTemporal%16;
				if (bResiduoHex < 10) /*Si el dígito actual se encuentra entre 0 y 9, simplemente se le agrega 48 para convertirlo a ASCII*/
				{
					*bpString = bResiduoHex + 48;
				}
				else /*Si el dígito actual se encuentra entre A y F, se le deben agregar 55*/
				{
					*bpString = bResiduoHex + 55;
				}
				bTemporal = bTemporal/16;
				bpString--; /*Se va retrocediendo en el arreglo fuente para llenar los espacios*/
				bEspaciosDiferencia++;
				wSize++; /*Se incrementa la variable del tamaño del arreglo destino*/
			}
			bpString = bpString + bEspaciosDiferencia + 1; /*Ahora apuntamos a la siguiente dirección vacía del arreglo destino, después de donde se escribió el resultado*/
			bIndiceApuntador++; /*Se recorre al siguiente argumento*/
			bEspaciosDiferencia = 0; /*Se reinician los espacios para poder ser utilizados en otra conversión*/
			bpFormat = bpFormat + 2; /*Se recorre en 2 bpFormat para no escribir el argumento de conversión*/
		}
		else if (*bpFormat == '%' && *(bpFormat + 1) == 'b') /*Si el modificador es para número en binario*/
		{
			bLecturaBin = *(unsigned char *)(*(vpaExtraArguments + bIndiceApuntador)+ bIndiceArregloContenido); /*Se lee el valor del parámetro en la posición actual*/
			while(bLecturaBin != 0) /*Conversión*/
			{
				bResiduoBin = bLecturaBin%2; /*El residuo de 2 representa un 1 o un 0*/
				bLecturaBin = bLecturaBin/2; /*Se divide entre 2 debido a que el número binario representa una potencia de 2*/
				dwResultadoBin = dwResultadoBin + (bResiduoBin*dwPotenciaBin); /*El resultado representará los 1s o 0s de magnitud definida por la potencia de 10 actual*/
				dwPotenciaBin = dwPotenciaBin*10;
			}

			dwTemporalBin = dwResultadoBin; /*Se almacena el resultado en una variable temporal*/
			while (dwTemporalBin != 0) /*Se cuentan el número de bits del resultado*/
			{
				dwTemporalBin = dwTemporalBin/10; /*Cada que se pueda dividir sobre 10, representa espacio para otro dígito en el resultado*/
				bNumeroDigitos++;
			}
			bNumeroDigitos++;
			bpString = bpString + bNumeroDigitos - 1; /*Similar a la conversión a hexadecimal, para escribir en el arreglo, comenzaremos a escribir de LSB a MSB, por lo que hay que dar un salto y dejar un espacio a cada dígito del resultado*/

			while (bNumeroDigitos--) /*Mientras aun queden dígitos*/
			{
				*bpString = dwResultadoBin%10; /*El residuo de dividir sobre 10 representa el LSB*/
				dwResultadoBin = dwResultadoBin/10; /*El valor escrito en el arreglo destino se desecha al dividir sobre 10*/
				bpString--; /*Se va escribiendo en reversa*/
				wSize++; /*Se incrementa la variable del tamaño del arreglo destino*/
				bEspaciosDiferencia++;
			}
			bpString = bpString + bEspaciosDiferencia + 1; /*Ahora apuntamos a la siguiente dirección vacía del arreglo destino, después de donde se escribió el resultado*/
			bIndiceApuntador++; /*Se recorre al siguiente argumento*/
			bEspaciosDiferencia = 0; /*Se reinician los espacios para poder ser utilizados en otra conversión*/
			bpFormat = bpFormat + 2; /*Se recorre en 2 bpFormat para no escribir el argumento de conversión*/
		}
		else
		{
			*bpString = *bpFormat; /*El valor a donde apunta el buffer destino es reemplazado por el valor al cual apunta el apuntador de formato fuente*/
			bpString++;  /*Se incrementa el apuntador del arreglo fuente, para escribir el siguiente dato*/
			bpFormat++; /*Se incrementa el apuntador de formato para poder leer el siguiente elemento antes de copiarlo, verificando si es un modificador de conversión (%)*/
			wSize++; /*Se incrementa la variable del tamaño del arreglo destino*/
		}
	}
	while (*bpFormat != 0); /*El ciclo continuará hasta que se haya llegado al nulo de la cadena fuente*/
	return wSize; /*Se retorna el tamaño del buffer destino*/
}
