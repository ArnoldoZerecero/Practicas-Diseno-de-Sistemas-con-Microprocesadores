/*
 * main implementation: use this 'C' sample to create your own application
 *
 */

/*Video demonstration link: https://photos.app.goo.gl/5Qrs6c0xtQt8rwso1*/

#include "I2C.h"
#include "derivative.h" /* include peripheral declarations */
#include "UART.h"
#include "MISCELANEO.h"
#include "Funciones.h" /*MemSet*/

void vfnReadCommand(void); /*Funci�n para acceder a la funci�n del comando tecleado*/

void vfnWriteMemoryFound(void); /*Funci�n a la que se accede al mandar el comando de buscar memorias*/

void vfnCheckMemoryWrite(void); /*Funci�n a la que se accede al mandar el comando de escribir en la memoria*/

void vfnWriteMemoryRead(void); /*Funci�n a la que se accede al mandar el comando de leer la memoria*/

UartConfigInit_t InitUartParameters = /*Inicializamos los valores de la estructura*/
{
		0, /*Solo 1 stop bit*/
		BAUD_RATE, /*7*/
		0, /*0 = 8 bits de longitud, 1 = 9 bits de longitud*/ 
		0, /*0 = paridad desactivada, 1 = paridad activada*/
		0, /*0 = paridad par, 1 = paridad impar*/
		OSR, /*25*/
		&vfnUARTCallback /*Apuntador a funci�n Callback*/
};

volatile unsigned char gbCharacterReceivedFlag = 0; /*�ndice para cuando se tecle� algo en la terminal*/

volatile unsigned char gbNewCharacterReceived = 0; /*Variable para guardar el caracter tecleado en la terminal*/

volatile unsigned char gbComando = 0; /*Variable para almacenar el comando*/

volatile unsigned short gwMemoryAddress = 0; /*Variable para almacenar la direcci�n de la memoria que se desea leer/escribir*/

volatile unsigned char gbSize = 0; /*Variable para almacenar la cantidad de bytes que se desean leer/escribir*/

unsigned char gbaDataToWrite[8]; /*Arreglo que se llenar� con los valores a escribir en la memoria*/



int main(void)
{
	static const unsigned char _kbaPalabraComando[] = /*Lo que se escribe antes de cada comando*/
	{
			"\n\rComando>"
	}; 
	
	static unsigned char _bParametroActual = 0; /*Variable utilizada para conocer qu� par�metro del comando se est� tecleando*/
	static unsigned char _bIndexData = 0; /*�ndice para almacenar en gwaDataToWrite los datos que se escribir�n en la memoria*/
	static unsigned char _bAddressByte = 0; /*Variable para saber cu�l de los 4 bytes de la direcci�n en memoria se est� tecleando*/
	static unsigned char _baAddressBytes[4]; /*Conjunto de los 4 caracteres que forman la direcci�n hexadecimal a leer/escribir en memoria*/
	static unsigned char _bFirstOrSecondDataByte = 0; /*Variable para saber cu�l de los 2 bytes de dato a escribir en memoria se est� tecleando*/
	static unsigned char _bFirstByte = 0; /*Variable para almacenar el primer byte de alg�n dato a escribir en memoria*/
	static unsigned char _bSecondByte = 0; /*Variable para almacenar el segundo byte de alg�n dato a escribir en memoria*/

	vfnI2CInitConfig(); /*Inicializaci�n del I2C*/
	vfnI2CPortsInit();
	vfnUartInit(&InitUartParameters); /*Inicializaci�n del UART*/
	vfnUartTransmision((unsigned char *)&_kbaPalabraComando[0], (sizeof(_kbaPalabraComando) - 1U)); /*Se escribe "Comando>"*/
	for(;;) 
	{	   
		if(gbCharacterReceivedFlag) /*Si se recibi� un caracter*/
		{
			gbCharacterReceivedFlag = 0; /*Se reinicia bandera*/
			if (gbNewCharacterReceived == '\r')  /*Cuando se mande un enter*/
			{
				vfnReadCommand(); /*Se lee el comando escrito*/
				_bParametroActual = 0; /*Se reinician banderas e �ndices*/
				_bIndexData = 0;
				gbComando = 0; /*Se reinicia las variable globales*/
				gbSize = 0;
				gwMemoryAddress = 0;
				vfnMemSet((unsigned char *)&gbaDataToWrite[0], 0, sizeof(gbaDataToWrite));
				vfnUartTransmision((unsigned char *)&_kbaPalabraComando[0], (sizeof(_kbaPalabraComando) - 1U)); /*Se escribe "Comando>*/
			}
			else if (gbNewCharacterReceived == ' ')  /*Cuando se mande un espacio*/
			{
				if (_bParametroActual == 0) /*El par�metro a escribir ahora ser� la direcci�n en memoria*/
				{
					_bParametroActual = 1;
				}
				else if (_bParametroActual == 1) /*El par�metro a escribir ahora ser� el tama�o*/
				{
					_bParametroActual = 2;
				}
				else if (_bParametroActual == 2) /*El par�metro a escribir ahora ser�n los datos a escribir en memoria*/
				{
					_bParametroActual = 3;
				}
			}
			else if (_bParametroActual == 1) /*Se escribe la direcci�n en memoria*/
			{
				if(_bAddressByte == 0) /*Se almacena byte por byte la direcci�n*/
				{
					_baAddressBytes[0] = gbNewCharacterReceived;
					_bAddressByte++;
				}
				else if(_bAddressByte == 1)
				{
					_baAddressBytes[1] = gbNewCharacterReceived;
					_bAddressByte++;
				}
				else if(_bAddressByte == 2)
				{
					_baAddressBytes[2] = gbNewCharacterReceived;
					_bAddressByte++;
				}
				else
				{
					_baAddressBytes[3] = gbNewCharacterReceived;
					_bAddressByte++;
				}

				if(_bAddressByte == 4) /*Al tener los 4 bytes, se convierten de d�gitos a decimal y se transfieren a la variable global*/
				{
					gwMemoryAddress = wfnHexCharADecimal(_baAddressBytes[3], _baAddressBytes[2], _baAddressBytes[1], _baAddressBytes[0]);
					_bAddressByte = 0;
				}
			}
			else if (_bParametroActual == 2) /*Se escribe el tama�o*/
			{
				gbSize = gbNewCharacterReceived - 48;
			}
			else if (_bParametroActual == 3) /*Se escriben los datos que se escribir�n en memoria*/
			{
				if(_bFirstOrSecondDataByte == 0) /*Se guarda el primer byte*/
				{
					_bFirstByte = gbNewCharacterReceived;
					_bFirstOrSecondDataByte = 1;
				}
				else if(_bFirstOrSecondDataByte == 1)/*Se guarda el segundo byte*/
				{
					_bSecondByte = gbNewCharacterReceived;
					_bFirstOrSecondDataByte = 2;
				}

				if(_bFirstOrSecondDataByte == 2) /*Al tener ambos bytes, estos se convierten de d�gitos a decimal, y se almacenan en el arreglo global*/
				{
					gbaDataToWrite[_bIndexData++] = wfnHexCharADecimal(_bSecondByte, _bFirstByte, 0, 0);
					_bFirstOrSecondDataByte = 0;
				}
			}
			else /*Se escribe el comando*/
			{
				gbComando = gbNewCharacterReceived; /*Se almacena el comando en la variable global*/
			}
			vfnUartTransmision((unsigned char *)&gbNewCharacterReceived, 1);  /*Se manda el eco de los caracteres que se est�n escribiendo en la terminal*/	
		}
	}

	return 0;
}

void vfnReadCommand(void) 
{
	static const unsigned char _kbaComandoNoReconocido[] =
	{
			"\n\romando no reconocido.\n\rComando>"
	}; 

	if(gbComando == 'S') /*Comando de buscar memorias*/
	{
		vfnWriteMemoryFound();
	}
	else if(gbComando == 'W') /*Comando de escribir en memoria*/
	{
		vfnCheckMemoryWrite();
	}

	else if(gbComando == 'R') /*Comando de leer la memoria*/
	{
		vfnWriteMemoryRead();
	}

	else /*Si el comando especificado no existe*/
	{
		vfnUartTransmision((unsigned char *)&_kbaComandoNoReconocido[0], (sizeof(_kbaComandoNoReconocido) - 1U));
	}
}

void vfnWriteMemoryFound(void)
{
	static const unsigned char _kbaFailMessage[] =
	{
			"\n\rFAIL\n\rComando>"
	}; 
	static const unsigned char _kbaMemoryFoundMessage[] =
	{
			"\n\rMemory found in hex address(es): "
	}; 
	unsigned char bMemoryFound = 0; /*Variable para almacenar las direcciones de memoria encontradas*/ 
	unsigned char flgMemoryFound = 0; /*Bandera que se activa al haberse encontrado al menos un esclavo por medio de MemorySearch*/
	unsigned char bDecenas = 0; /*Variable que almacena las decenas del valor de la direcci�n*/
	unsigned char bUnidades = 0; /*Variable que almacena las unidades del valor de la direcci�n*/
	unsigned char bCaracterEspacio = ' '; /*Caracter de espacio*/

	while(bpfnMemorySearch() != 1) /*Se barren las direcciones*/
	{
		bMemoryFound = bpfnMemorySearch(); /*Se leen las direcciones encontradas*/
		if(bMemoryFound) /*Si se encontr� una direcci�n*/
		{			
			if(!flgMemoryFound) /*Si es la primera memoria que se encuentra, se manda el mensaje de memoria encontrada*/
			{
				vfnUartTransmision((unsigned char *) &_kbaMemoryFoundMessage[0], sizeof(_kbaMemoryFoundMessage));
				vfnDelay(5000); /*Se le da un tiempo al UART de escribir el arreglo*/
				flgMemoryFound = 1;
			}
			bDecenas = (bMemoryFound/16) + 48;
			vfnUartTransmision((unsigned char *) &bDecenas, 1);
			vfnDelay(200); /*Se le da un tiempo al UART de escribir el caracter*/

			bUnidades = CLEAR_ALL_BUT_UNITS(wfnBCD(bMemoryFound))+ 48;
			vfnUartTransmision((unsigned char *) &bUnidades, 1);
			vfnDelay(200); /*Se le da un tiempo al UART de escribir el caracter*/
			
			vfnUartTransmision((unsigned char *) &bCaracterEspacio, 1); /*Se separan por espacios las direcciones encontradas*/
		}
	}

	if(!flgMemoryFound) /*Si no se encontr� direcci�n alguna*/
	{
		vfnUartTransmision((unsigned char *)&_kbaFailMessage[0], (sizeof(_kbaFailMessage) - 1U));
	}
}

void vfnCheckMemoryWrite(void)
{
	static const unsigned char _kbaFailMessage[] =
	{
			"\n\rFAIL\n\rComando>"
	}; 
	static const unsigned char _kbaOkMessage[] =
	{
			"\n\rOK\n\rComando>"
	}; 
	
	static unsigned char _bSlaveAddress = 0; /*Variable para almacenar la direcci�n del c�digo identificador de la memoria*/
	
	/*Se asigna a cu�l de los bloques de memoria disponibles se acceder�. El ST24C16 tiene 16K de memoria (2040 bytes)*/
	if(gwMemoryAddress >= 0 && gwMemoryAddress <= 255)
	{
		_bSlaveAddress = 0b1010000; /*0x50*/
	}
	else if(gwMemoryAddress >= 255 && gwMemoryAddress <= 510)
	{
		_bSlaveAddress = 0b1010001; /*0x51*/
		gwMemoryAddress = gwMemoryAddress - 255; /*Se ajusta el valor de la direcci�n para estar en el rango de 0 a 255 bytes*/
	}
	else if(gwMemoryAddress >= 510 && gwMemoryAddress <= 765)
	{
		_bSlaveAddress = 0b1010010; /*0x52*/
		gwMemoryAddress = gwMemoryAddress - 510; /*Se ajusta el valor de la direcci�n para estar en el rango de 0 a 255 bytes*/
	}
	else if(gwMemoryAddress >= 765 && gwMemoryAddress <= 1020)
	{
		_bSlaveAddress = 0b1010011; /*0x53*/
		gwMemoryAddress = gwMemoryAddress - 765; /*Se ajusta el valor de la direcci�n para estar en el rango de 0 a 255 bytes*/
	}
	else if(gwMemoryAddress >= 1020 && gwMemoryAddress <= 1275)
	{
		_bSlaveAddress = 0b1010100; /*0x54*/
		gwMemoryAddress = gwMemoryAddress - 1020; /*Se ajusta el valor de la direcci�n para estar en el rango de 0 a 255 bytes*/
	}
	else if(gwMemoryAddress >= 1275 && gwMemoryAddress <= 1530)
	{
		_bSlaveAddress = 0b1010101; /*0x55*/
		gwMemoryAddress = gwMemoryAddress - 1275; /*Se ajusta el valor de la direcci�n para estar en el rango de 0 a 255 bytes*/
	}
	else if(gwMemoryAddress >= 1530 && gwMemoryAddress <= 1785)
	{
		_bSlaveAddress = 0b1010110; /*0x56*/
		gwMemoryAddress = gwMemoryAddress - 1530; /*Se ajusta el valor de la direcci�n para estar en el rango de 0 a 255 bytes*/
	}
	else if(gwMemoryAddress >= 1785 && gwMemoryAddress <= 2040)
	{
		_bSlaveAddress = 0b1010111; /*0x57*/
		gwMemoryAddress = gwMemoryAddress - 1785; /*Se ajusta el valor de la direcci�n para estar en el rango de 0 a 255 bytes*/
	}
	else
	{
		vfnUartTransmision((unsigned char *)&_kbaFailMessage[0], (sizeof(_kbaFailMessage) - 1U)); 
		return;
	}
	
	if(bfnWriteMode(_bSlaveAddress, gwMemoryAddress, gbSize, &gbaDataToWrite[0])) /*Se pasan los par�metros globales*/
	{
		vfnUartTransmision((unsigned char *)&_kbaOkMessage[0], (sizeof(_kbaOkMessage) - 1U)); /*Si se regresa un 1*/
	}
	else
	{
		vfnUartTransmision((unsigned char *)&_kbaFailMessage[0], (sizeof(_kbaFailMessage) - 1U)); /*Si se regresa un 0*/
	}
}
void vfnWriteMemoryRead(void)
{
	static const unsigned char _kbaFailMessage[] =
	{
			"\n\rFAIL\n\rComando>"
	}; 
	unsigned char *bpDatosLeidos = 0; /*Apuntador para almacenar la direcci�n arreglo que devuelve la funci�n de ReadMode*/
	unsigned char bDatosLeidosIndex = 0; /*�ndice para hacer un barrido del arreglo que devuelve la funci�n de ReadMode*/
	unsigned char flgDataInMemoryFound = 0; /*Bandera que se activa al haberse encontrado al menos una direcci�n por medio de ReadMode*/
	unsigned char bDecenas = 0; /*Variable que almacena las decenas del valor le�do*/
	unsigned char bUnidades = 0; /*Variable que almacena las unidades del valor le�do*/
	unsigned char bCaracterEspacio = ' '; /*Caracter de espacio*/
	static unsigned char _bSlaveAddress = 0; /*Variable para almacenar la direcci�n del c�digo identificador de la memoria*/
	static unsigned char _bMemoryAddress = 0; /*Variable para almacenar la direcci�n de la memoria de 8 bits a mandar*/
	
	/*Se asigna a cu�l de los bloques de memoria disponibles se acceder�. El ST24C16 tiene 16K de memoria (2040 bytes)*/
	if(gwMemoryAddress >= 0 && gwMemoryAddress <= 255)
	{
		_bSlaveAddress = 0b1010000; /*0x50*/
		_bMemoryAddress = gwMemoryAddress;
	}
	else if(gwMemoryAddress >= 255 && gwMemoryAddress <= 510)
	{
		_bSlaveAddress = 0b1010001; /*0x51*/
		_bMemoryAddress = gwMemoryAddress - 255; /*Se ajusta el valor de la direcci�n para estar en el rango de 0 a 255 bytes*/
	}
	else if(gwMemoryAddress >= 510 && gwMemoryAddress <= 765)
	{
		_bSlaveAddress = 0b1010010; /*0x52*/
		_bMemoryAddress = gwMemoryAddress - 510; /*Se ajusta el valor de la direcci�n para estar en el rango de 0 a 255 bytes*/
	}
	else if(gwMemoryAddress >= 765 && gwMemoryAddress <= 1020)
	{
		_bSlaveAddress = 0b1010011; /*0x53*/
		_bMemoryAddress = gwMemoryAddress - 765; /*Se ajusta el valor de la direcci�n para estar en el rango de 0 a 255 bytes*/
	}
	else if(gwMemoryAddress >= 1020 && gwMemoryAddress <= 1275)
	{
		_bSlaveAddress = 0b1010100; /*0x54*/
		_bMemoryAddress = gwMemoryAddress - 1020; /*Se ajusta el valor de la direcci�n para estar en el rango de 0 a 255 bytes*/
	}
	else if(gwMemoryAddress >= 1275 && gwMemoryAddress <= 1530)
	{
		_bSlaveAddress = 0b1010101; /*0x55*/
		_bMemoryAddress = gwMemoryAddress - 1275; /*Se ajusta el valor de la direcci�n para estar en el rango de 0 a 255 bytes*/
	}
	else if(gwMemoryAddress >= 1530 && gwMemoryAddress <= 1785)
	{
		_bSlaveAddress = 0b1010110; /*0x56*/
		_bMemoryAddress = gwMemoryAddress - 1530; /*Se ajusta el valor de la direcci�n para estar en el rango de 0 a 255 bytes*/
	}
	else if(gwMemoryAddress >= 1785 && gwMemoryAddress <= 2040)
	{
		_bSlaveAddress = 0b1010111; /*0x57*/
		_bMemoryAddress = gwMemoryAddress - 1785; /*Se ajusta el valor de la direcci�n para estar en el rango de 0 a 255 bytes*/
	}
	else
	{
		vfnUartTransmision((unsigned char *)&_kbaFailMessage[0], (sizeof(_kbaFailMessage) - 1U)); 
		return;
	}

	
	unsigned char baDataFoundMessage[] = {LINE_FEED, CARRIAGE_RETURN, bfnDecimalAHexChar((CLEAR_ALL_BUT_THOUSANDS(gwMemoryAddress))) + 48, bfnDecimalAHexChar((CLEAR_ALL_BUT_HUNDREDS(gwMemoryAddress))) + 48, bfnDecimalAHexChar((CLEAR_ALL_BUT_TENS(gwMemoryAddress))) + 48, bfnDecimalAHexChar((CLEAR_ALL_BUT_UNITS(gwMemoryAddress))) + 48, ':', ' '}; /*Arreglo que para escribir la direcci�n de memoria elegida antes de escribIR los datOs encontrados dentro de ella*/ 
	
	bpDatosLeidos = bpfnReadMode(_bSlaveAddress, _bMemoryAddress, gbSize); /*Se pasan los par�metros globales*/
	while(bDatosLeidosIndex != gbSize) /*Se recorre este arreglo para escribir los elementos que no est�n vac�os*/
	{
		if(*bpDatosLeidos != 255 && *bpDatosLeidos != 0) /*De f�brica, el ST24C16 viene relleno de 0xFF, por lo que recibir �nicamente estos tambi�n quiere decir que la memoria en esa direcci�n no ha sido escrita*/ 
		{
			if(!flgDataInMemoryFound)
			{
				vfnUartTransmision((unsigned char *)&baDataFoundMessage[0], sizeof(baDataFoundMessage));
				vfnDelay(5000); /*Se le da un tiempo al UART de escribir el arreglo*/
				flgDataInMemoryFound = 1;
			}
			bDecenas = CLEAR_ALL_BUT_TENS(*bpDatosLeidos);
			bUnidades = CLEAR_ALL_BUT_UNITS(*bpDatosLeidos);

			bDecenas = bfnDecimalAHexChar(bDecenas) + 48;
			vfnUartTransmision((unsigned char *) &bDecenas, 1); 
			vfnDelay(500); /*Se le da un tiempo al UART de escribir el caracter*/

			bUnidades = bfnDecimalAHexChar(bUnidades) + 48;
			vfnUartTransmision((unsigned char *) &bUnidades, 1);
			vfnDelay(500); /*Se le da un tiempo al UART de escribir el caracter*/

			vfnUartTransmision((unsigned char *) &bCaracterEspacio, 1); /*Se separan por espacios las direcciones encontradas*/
			vfnDelay(500);
		}
		bpDatosLeidos++;
		bDatosLeidosIndex++;
	}

	if(!flgDataInMemoryFound) /*Si no se encontraron datos en memoria*/
	{
		vfnUartTransmision((unsigned char *)&_kbaFailMessage[0], (sizeof(_kbaFailMessage) - 1U));
	}

}

void vfnUARTCallback(unsigned char bDatosReceptor)
{
	gbNewCharacterReceived = bDatosReceptor;
	gbCharacterReceivedFlag = 1;
}
