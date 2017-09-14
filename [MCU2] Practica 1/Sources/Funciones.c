/*
 * Funciones.c
 * 
 *
 *  Created on: Sep 10, 2017
 *      Author: Jes�s Arnoldo Zerecero N��ez
 */
#include "Funciones.h"


void vfnMemCpy (unsigned char * bpSource, unsigned char * bpDest, unsigned short wSize)
{
	while (wSize--) /*El ciclo continuar� hasta que se hayan recorrido todos los elementos de ambos arreglos, es decir, hasta que el valor del n�mero de elementos especificado sea 0*/
	{
		*bpDest++ = *bpSource++; /*El valor a donde apunta el apuntador destino es reemplazado por el valor al cual apunta el apuntador fuente*/
	}
}

void vfnMemSet(unsigned char * bpDest, unsigned char bByteToFill, unsigned short wSize)
{
	while (wSize--) /*El ciclo continuar� hasta que se hayan recorrido todos los elementos del arreglo, es decir, hasta que el valor del n�mero de elementos especificado sea 0*/
	{
		*bpDest++ = bByteToFill; /*La posici�n actual del arreglo adquiere el caracter especificado*/
	}
}

unsigned char bfnFindMax(unsigned char * bpDest, unsigned short wSize)
{
	unsigned char bMax = 0; /*Variable de retorno, en donde terminar� el caracter de mayor valor*/
	while (wSize--) /*El ciclo continuar� hasta que se hayan recorrido todos los elementos del arreglo, es decir, hasta que el valor del n�mero de elementos especificado sea 0*/
	{
		if (*bpDest > bMax)/*Si la posici�n actual es mayor al valor m�ximo encontrado hasta el momento*/
		{
			bMax = *bpDest; /*bMax adquiere ese nuevo valor, debido a que ser� el nuevo valor mayor*/
		}
		bpDest++; /*El apuntador se incrementa a la siguiente posici�n del arreglo*/
	}
	return bMax; /*Se regresa el mayor valor encontrado*/
}

unsigned char bfnFindMin(unsigned char * bpDest, unsigned short wSize)
{
	unsigned char bMin = 255; /*Variable de retorno, en donde terminar� el caracter de menor valor*/
	while (wSize--) /*El ciclo continuar� hasta que se hayan recorrido todos los elementos del arreglo, es decir, hasta que el valor del n�mero de elementos especificado sea 0*/
	{
		if (*bpDest < bMin)/*Si la posici�n actual es menor al valor m�nimo encontrado hasta el momento*/
		{
			bMin = *bpDest; /*bMin adquiere ese nuevo valor, debido a que ser� el nuevo valor menor*/
		}
		bpDest++; /*El apuntador se incrementa a la siguiente posici�n del arreglo*/
	}
	return bMin; /*Se regresa el menor valor encontrado*/
}

unsigned char bfnStrCmp(unsigned char * bpSource, unsigned char * bpDest, unsigned short wSize)
{
	while (wSize--) /*El ciclo continuar� hasta que se hayan recorrido todos los elementos de ambos arreglos, es decir, hasta que el valor del n�mero de elementos especificado sea 0*/
	{
		if (*bpSource++ != *bpDest++) /*En caso de que el contenido de los apuntadores sea diferente, la funci�n regresa un 0*/
		{
			return 0;
		}
	}
	return 1; /*Si se recorrieron todos los elementos y la funci�n sali� del ciclo, quiere decir que los arreglos son iguales*/
}

unsigned char * bpfnByteAddress(unsigned char * bpString, unsigned char bCharToFind, unsigned short wSize)
{
	while (wSize--) /*El ciclo continuar� hasta que se hayan recorrido todos los elementos del arreglo, es decir, hasta que el valor del n�mero de elementos especificado sea 0*/
	{
		if (*bpString == bCharToFind) /*Si se encuentra una posici�n del arreglo que contenga el valor de bCharToFind*/
		{
			return bpString; /*Se retorna esa posici�n*/
		}
		bpString++;/*El apuntador se incrementa a la siguiente posici�n del arreglo*/
	}
	return '\0'; /*Si no se encontr� un valor igual a bCharToFind, se regresa un apuntador a NULL*/
}

void vfnSort (unsigned char * bpString, unsigned short wStringSize)
{
	unsigned short wIndice = 0; /*Se crea una variable para el �ndice y se inicia en cero*/
	unsigned char *bpApuntadorSiguienteElemento; /*Se declara un nuevo apuntador que comparar� los siguientes elementos con el apuntador base actual (bpString)*/
	unsigned char bTemporal; /*Se crea una variable temporal para evitar p�rdida de datos*/
	unsigned char bOffset = 1; /*Esta variable determina cu�ntas veces le falta por recorrerse el *bApuntadorSiguienteElemento para llegar al final del arreglo. Se inicializa en uno debido a que el *bApuntadorSiguienteElemento comienza en la posici�n [1] del arreglo*/

	do /*Comienza el primer ciclo*/
	{
		bpApuntadorSiguienteElemento = bpString + 1; /*El apuntador para el siguiente elemento siempre comienza uno por delante del apuntador base*/
		do /*Comienza el segundo ciclo*/
		{
			if (*bpString > *bpApuntadorSiguienteElemento) /*En caso de que sea mayor el valor base (de la izquierda), se intercambia con el de la derecha*/
			{
				bTemporal = *bpApuntadorSiguienteElemento; /*Se guarda el elemento al que apunta el *bApuntadorSiguienteElemento en bTemporal para no perderlo*/
				*bpApuntadorSiguienteElemento = *bpString; /**bApuntadorSiguienteElemento adquiere el valor del elemento al que apunta *bApuntadorArreglo*/
				*bpString = bTemporal; /*El apuntador base adquiere el valor en el que estaba el *bApuntadorSiguienteElemento, el cual se guard� en bTemporal*/
			}
			else /*En caso de que el elemento de la izquierda sea menor, quiere decir que se encuentra en orden, y ninguna acci�n ocurre*/
			{
			}
			bpApuntadorSiguienteElemento++; /*Se incrementa en uno el bApuntadorSiguienteElemento para apuntar a la siguiente posici�n de la cadena*/
			wIndice++; /*Se incrementa en uno el �ndice*/
		}
		while ((wIndice != (wStringSize - bOffset)) && wStringSize != 1); /*El ciclo interno continuar� hasta que se haya recorrido bApuntadorSiguienteElemento hasta el �ltimo elemento. En caso de que el arreglo contenga un �nico elemento, el ciclo tambi�n finalizar�*/
		wIndice = 0; /*El �ndice se reinicia a 0 antes de volver a comenzar el ciclo*/
		bpString++; /*El apuntador base se recorre al siguiente elemento, lo que significa que el elemento en el que estaba ya qued� ordenado*/
		bOffset++; /*El bOffset se incrementa en uno, lo cual indica que en el pr�ximo ciclo, el bApuntadorSiguienteElemento tedr� que recorrerse una vez menos para llegar al final del arreglo*/
	}while(bOffset != wStringSize && wStringSize != 1); /*El ciclo principal termina cuando el bOffset se incrementa hasta ser igual al n�mero de elementos, lo cual significa que el apuntador base (bpString) ya ha pasado por todos los elementos.  En caso de que el arreglo contenga un �nico elemento, el ciclo tambi�n finalizar�*/
}

unsigned short wfnStrLen (unsigned char * bpString)
{
	unsigned short wAcumulador = 0; /*Se declara una variable para llevar el conteo del n�mero de caracteres*/
	while (*bpString++ != 0) /*El ciclo termina cuando el apuntador llegue al nulo*/
	{
		wAcumulador++; /*Se incrementa en uno el acumulador*/
	}
	return wAcumulador; /*Se regresa el valor de bAcumulador a main*/
}

unsigned short wfnSprintf (char * bpString, const char * bpFormat, void * vpaExtraArguments[])
{
	unsigned short wSize = 0; /*Variable para medir el tama�o de caracteres de la cadena destino*/
	unsigned char bIndiceApuntador = 0; /*Variable para recorrer los apuntadores (argumentos) almacenados en el arreglo*/
	unsigned char bIndiceArregloContenido = 0; /*Variable para recorrer los arreglos a los cuales apuntan los apuntadores del arreglo*/
	unsigned char bTemporal; /*Variable para almacenar temporalmente valores para cualquier conversi�n*/
	unsigned char bNumeroDigitos = 0; /*Variable para conocer el tama�o de los d�gitos a escribir en la cadena fuente para cualquier conversi�n*/
	unsigned char bEspaciosDiferencia = 0; /*Variable para saber cu�ntos espacios hay que saltar para volver al siguiente espacio vac�o de la cadena destino en cualquier conversi�n*/
	unsigned char bResiduoHex; /*Variable para el residuo de las divisiones sobre 16 en el c�lculo dec - hex*/
	unsigned char bLecturaBin; /*Variable que lee el valor de la actual posici�n del arreglo de par�metros en el c�lculo dec - bin*/
	unsigned char bResiduoBin; /*Variable para el residuo de las divisiones sobre 2 en el c�lculo dec - bin*/
	unsigned long dwPotenciaBin = 1; /*Variable para recorrerse por las potencias de 2 (multiplicaci�n por 10)*/
	unsigned long dwTemporalBin; /*Variable para almacenar temporalmente el resultado del c�lculo dec - bin*/
	unsigned long dwResultadoBin = 0; /*Variable para almacenar el resultado del c�lculo dec - bin*/

	do /*Comienza el ciclo*/
	{
		if (*bpFormat == '%' && *(bpFormat + 1) == 'c') /*Si bpFormat indica que se aproxima un modificador para caracter*/
		{
			*bpString = *(char *)(*(vpaExtraArguments + bIndiceApuntador)+ bIndiceArregloContenido); /*Se toma el valor del arreglo de apuntadores*/
			bpString++; /*Se incrementa el apuntador del arreglo fuente, para escribir el siguiente dato*/
			bIndiceApuntador++; /*Se recorre al siguiente argumento*/
			bpFormat = bpFormat + 2; /*Se recorre en 2 bpFormat para no escribir el argumento de conversi�n*/
			wSize++; /*Se incrementa la variable del tama�o del arreglo destino*/
		}
		else if (*bpFormat == '%' && *(bpFormat + 1) == 'd') /*Si el modificador es para n�mero en decimal*/
		{
			bTemporal = *(unsigned char *)(*(vpaExtraArguments + bIndiceApuntador)+ bIndiceArregloContenido); /*Se almacena el valor del argumento en bTemporalDec*/

			while (bTemporal != 0) /*Se calcula el n�mero de d�gitos*/
			{
				bTemporal = bTemporal / 10;
				bNumeroDigitos++;
			}

			bTemporal = *(unsigned char *)(*(vpaExtraArguments + bIndiceApuntador)+ bIndiceArregloContenido); /*Se almacena el valor del argumento en bTemporalDec*/
			bpString = bpString + bNumeroDigitos - 1; /*Se deja espacio para escribir el n�mero de d�gitos, debido a que se escribir�n de LSB  a MSB*/

			while (bNumeroDigitos--)
			{
				*bpString = bTemporal % 10; /*Se escriben primero las unidades, luego las decenas y al final las centenas*/
				bTemporal = bTemporal / 10;
				bpString--;
				wSize++; /*Se incrementa la variable del tama�o del arreglo destino*/
				bEspaciosDiferencia++;
			}
			bpString = bpString + bEspaciosDiferencia + 1; /*Se salta el espacio escrito hasta el siguente espacio vac�o a escribir*/
			bIndiceApuntador++; /*Se recorre al siguiente argumento*/
			bEspaciosDiferencia = 0; /*Se reinician los espacios para poder ser utilizados en otra conversi�n*/
			bpFormat = bpFormat + 2; /*Se recorre en 2 bpFormat para no escribir el argumento de conversi�n*/
		}
		else if (*bpFormat == '%' && *(bpFormat + 1) == 's')/*Si el modificador es para escribir una cadena*/
		{
			while (*(char *)(*(vpaExtraArguments + bIndiceApuntador)+ bIndiceArregloContenido) != 0) /*Mientras no se haya llegado al nulo de la cadena mandada como par�metro*/
			{
				*bpString = *(char *)(*(vpaExtraArguments + bIndiceApuntador)+ bIndiceArregloContenido); /*Se guarda caracter por caracter en el arreglo destino*/
				bIndiceArregloContenido++; /*Se recorre al siguiente elemento del arreglo apuntado*/
				bpString++; /*Se incrementa el apuntador del arreglo fuente, para escribir el siguiente dato*/
				wSize++; /*Se incrementa la variable del tama�o del arreglo destino*/
			}
			bIndiceArregloContenido = 0; /*Se reinicia el �ndice para los dem�s arreglos*/
			bIndiceApuntador++; /*Se recorre al siguiente argumento*/
			bpFormat = bpFormat + 2; /*Se recorre en 2 bpFormat para no escribir el argumento de conversi�n*/
		}
		else if (*bpFormat == '%' && *(bpFormat + 1) == 'x') /*Si el modificador es para n�mero en hexadecimal*/
		{	
			bTemporal = *(unsigned char *)(*(vpaExtraArguments + bIndiceApuntador)+ bIndiceArregloContenido); /*Se almacena el valor del par�metro le�do en la variable temporal*/

			while (bTemporal != 0) /*Se cuenta cu�ntos d�gitos tiene el resultado hexadecimal*/
			{
				bTemporal = bTemporal/16; /*Cada que se pueda dividir el n�mero sobre 16, se incrementa el n�mero de d�gitos resultantes*/
				bNumeroDigitos++;
			}
			bNumeroDigitos++;
			bpString = bpString + bNumeroDigitos - 1; /*Debido a que se desea guardar en una cadena el resultado, de izquierda a derecha ("MSB a LSB"), debemos reversear el orden en que se acomodan los datos. Se empezar� escribiendo desde el LSB, primero dejando espacio para el n�mero de d�gitos resultante, retrocediendo hacia al izquierda hasta llenar el espacio*/
			bTemporal = *(unsigned char *)(*(vpaExtraArguments + bIndiceApuntador)+ bIndiceArregloContenido); /*Se almacena el valor del par�metro le�do en la variable del dividendo nuevamente, para reiniciarlo y ahora hacer la conversi�n*/

			while (bNumeroDigitos--) /*Mientras aun falten d�gitos para terminar el resultado*/
			{
				bResiduoHex = bTemporal%16;
				if (bResiduoHex < 10) /*Si el d�gito actual se encuentra entre 0 y 9, simplemente se le agrega 48 para convertirlo a ASCII*/
				{
					*bpString = bResiduoHex + 48;
				}
				else /*Si el d�gito actual se encuentra entre A y F, se le deben agregar 55*/
				{
					*bpString = bResiduoHex + 55;
				}
				bTemporal = bTemporal/16;
				bpString--; /*Se va retrocediendo en el arreglo fuente para llenar los espacios*/
				bEspaciosDiferencia++;
				wSize++; /*Se incrementa la variable del tama�o del arreglo destino*/
			}
			bpString = bpString + bEspaciosDiferencia + 1; /*Ahora apuntamos a la siguiente direcci�n vac�a del arreglo destino, despu�s de donde se escribi� el resultado*/
			bIndiceApuntador++; /*Se recorre al siguiente argumento*/
			bEspaciosDiferencia = 0; /*Se reinician los espacios para poder ser utilizados en otra conversi�n*/
			bpFormat = bpFormat + 2; /*Se recorre en 2 bpFormat para no escribir el argumento de conversi�n*/
		}
		else if (*bpFormat == '%' && *(bpFormat + 1) == 'b') /*Si el modificador es para n�mero en binario*/
		{
			bLecturaBin = *(unsigned char *)(*(vpaExtraArguments + bIndiceApuntador)+ bIndiceArregloContenido); /*Se lee el valor del par�metro en la posici�n actual*/
			while(bLecturaBin != 0) /*Conversi�n*/
			{
				bResiduoBin = bLecturaBin%2; /*El residuo de 2 representa un 1 o un 0*/
				bLecturaBin = bLecturaBin/2; /*Se divide entre 2 debido a que el n�mero binario representa una potencia de 2*/
				dwResultadoBin = dwResultadoBin + (bResiduoBin*dwPotenciaBin); /*El resultado representar� los 1s o 0s de magnitud definida por la potencia de 10 actual*/
				dwPotenciaBin = dwPotenciaBin*10;
			}

			dwTemporalBin = dwResultadoBin; /*Se almacena el resultado en una variable temporal*/
			while (dwTemporalBin != 0) /*Se cuentan el n�mero de bits del resultado*/
			{
				dwTemporalBin = dwTemporalBin/10; /*Cada que se pueda dividir sobre 10, representa espacio para otro d�gito en el resultado*/
				bNumeroDigitos++;
			}
			bNumeroDigitos++;
			bpString = bpString + bNumeroDigitos - 1; /*Similar a la conversi�n a hexadecimal, para escribir en el arreglo, comenzaremos a escribir de LSB a MSB, por lo que hay que dar un salto y dejar un espacio a cada d�gito del resultado*/

			while (bNumeroDigitos--) /*Mientras aun queden d�gitos*/
			{
				*bpString = dwResultadoBin%10; /*El residuo de dividir sobre 10 representa el LSB*/
				dwResultadoBin = dwResultadoBin/10; /*El valor escrito en el arreglo destino se desecha al dividir sobre 10*/
				bpString--; /*Se va escribiendo en reversa*/
				wSize++; /*Se incrementa la variable del tama�o del arreglo destino*/
				bEspaciosDiferencia++;
			}
			bpString = bpString + bEspaciosDiferencia + 1; /*Ahora apuntamos a la siguiente direcci�n vac�a del arreglo destino, despu�s de donde se escribi� el resultado*/
			bIndiceApuntador++; /*Se recorre al siguiente argumento*/
			bEspaciosDiferencia = 0; /*Se reinician los espacios para poder ser utilizados en otra conversi�n*/
			bpFormat = bpFormat + 2; /*Se recorre en 2 bpFormat para no escribir el argumento de conversi�n*/
		}
		else
		{
			*bpString = *bpFormat; /*El valor a donde apunta el buffer destino es reemplazado por el valor al cual apunta el apuntador de formato fuente*/
			bpString++;  /*Se incrementa el apuntador del arreglo fuente, para escribir el siguiente dato*/
			bpFormat++; /*Se incrementa el apuntador de formato para poder leer el siguiente elemento antes de copiarlo, verificando si es un modificador de conversi�n (%)*/
			wSize++; /*Se incrementa la variable del tama�o del arreglo destino*/
		}
	}
	while (*bpFormat != 0); /*El ciclo continuar� hasta que se haya llegado al nulo de la cadena fuente*/
	return wSize; /*Se retorna el tama�o del buffer destino*/
}
