/*
 * I2C.c
 *
 *  Created on: Dec 2, 2017
 *      Author: Jesús Arnoldo Zerecero Núñez
 */

#include "I2C.h"
#include "MISCELANEO.h"
#include "Funciones.h" /*MemSet*/

volatile unsigned short gwTimeout = 0;

void vfnI2CInitConfig(void)
{
	SIM_SCGC4 |= SIM_SCGC4_I2C0_MASK;
	I2C0_F |= I2C_F_MULT(0) | I2C_F_ICR(0x21); /*Multiplicador por 1 y SCL divider de 192 para un baud rate de 21MHz/192 = 109KHz*/

	I2C0_C2 |= I2C_C2_HDRS_MASK; /*High Drive Enable*/
			
	I2C0_C1 |= I2C_C1_IICEN_MASK; /*I2C Enabled*/
	}

void vfnI2CPortsInit(void)
{
	SIM_SCGC5 |= SIM_SCGC5_PORTC_MASK;

	PORTC_PCR8 |= PORT_PCR_MUX(2); /*SCL*/
	PORTC_PCR9 |= PORT_PCR_MUX(2); /*SDA*/
}

void vfnStartCondition(void)
{
	I2C0_C1 |= I2C_C1_TXAK_MASK; /*Master ACKs disabled*/
	I2C0_C1 |= I2C_C1_TX_MASK; /*Transmit mode*/
	I2C0_C1 |= I2C_C1_MST_MASK; /*Master sends start condition*/
}

void vfnStopCondition(void)
{
	I2C0_C1 &= ~I2C_C1_MST_MASK; /*Master sends stop condition*/
	I2C0_C1 &= ~I2C_C1_TX_MASK; /*Receive mode*/
}

unsigned char bpfnMemorySearch(void)
{
	static unsigned char _baMemoryFound; /*Variable para almacenar las direcciones de las memorias encontradas durante el barrido*/
	static unsigned char _bSlaveAddress = 0x50; /*Variable que almacena las direcciones entre 0x50 y 0x57*/ 
	
	if(_bSlaveAddress != 0x58) /*Se buscarán memorias con direcciones entre 0x50 y 0x57*/
	{
		_bSlaveAddress = _bSlaveAddress << 1; /*Se recorre la dirección debido a que se encontraba en hex 7-bits*/
		vfnStartCondition(); /*Start*/
		vfnTransmitData(_bSlaveAddress); /*Se llama a esa dirección*/
		vfnWaitForTranfer(); /*Se le da un tiempo para ver si llegó o no un ACK*/
		_bSlaveAddress = _bSlaveAddress >> 1; /*Se devuelve a modo hex 7-bits*/
		if(!gwTimeout) /*Si se recibió un ACK debido a que el Timeout fue reiniciado*/
		{
			_baMemoryFound = _bSlaveAddress; /*Se guarda esa dirección*/
		}
		else
		{
			_baMemoryFound = 0; /*Se retorna un cero*/
			gwTimeout = 0;
		}
		vfnStopCondition(); /*Se libera el bus*/
		_bSlaveAddress++; 
		return _baMemoryFound;
	}
	else /*Cuando se llegue al 0x58*/
	{
		_bSlaveAddress = 0x50;
		vfnStopCondition(); /*Se libera el bus*/
		return 1; /*Se regresa un uno para hacerle saber a main que el barrido finalizó*/
	}
}

unsigned char bfnWriteMode(unsigned char bSlaveAddress, unsigned short wMemoryAddress, unsigned char bSize, unsigned char *bpData)
{
	if(!bSize) /*Si no se escribirá dato alguno*/
	{
		return 0;
	}

	bSlaveAddress = bSlaveAddress << 1; /*R/W = 0*/

	vfnStartCondition(); /*Start*/
	vfnTransmitData(bSlaveAddress); /*Se escribe al esclavo deseado*/ 
	vfnWaitForTranfer(); /*Se espera el ACK*/
	if(gwTimeout == 50000) /*Si no hay respuesta del esclavo*/
	{
		vfnStopCondition(); /*Finaliza la transmisión de datos, se libera el Bus*/
		gwTimeout = 0;
		return 0;
	}
	vfnTransmitData(wMemoryAddress); /*Se le dice al esclavo en qué espacio escribir*/
	vfnWaitForTranfer(); /*Se espera el ACK*/
	if(gwTimeout == 50000) /*Si no hay respuesta del esclavo*/
	{
		vfnStopCondition(); /*Finaliza la transmisión de datos, se libera el Bus*/
		gwTimeout = 0;
		return 0;
	}

	while(bSize--) /*Se escriben bSize número de datos*/
	{
		vfnTransmitData(*bpData++);
		vfnWaitForTranfer(); /*Se espera el ACK*/
		if(gwTimeout == 50000) /*Si no hay respuesta del esclavo*/
		{
			vfnStopCondition(); /*Finaliza la transmisión de datos, se libera el Bus*/
			gwTimeout = 0;
			return 0;
		}
	}
	vfnStopCondition(); /*Stop*/
	vfnWaitForWriteCycle(bSlaveAddress); /*Se espera mientras se realiza el write cycle*/
	I2C0_C1 |= I2C_C1_RSTA_MASK; /*Se manda otro Start*/
	vfnStopCondition(); /*Finaliza la transmisión de datos, se libera el Bus*/
	return 1;
}

unsigned char* bpfnReadMode(unsigned char bSlaveAddress, unsigned short wMemoryAddress, unsigned char bSize)
{
	if(!bSize) /*Si no se leerá dato alguno*/
	{
		return 0;
	}
	static unsigned char _baDataRead[8]; /*Arreglo para almacenar los datos leídos*/
	unsigned char bIndex = 0; /*Índice del arreglo*/
	vfnMemSet((unsigned char *)&_baDataRead[0], 0, 8); /*Se limpia el arreglo al llenarlo de ceros*/

	bSlaveAddress = bSlaveAddress << 1; /*R/W = 0*/

	vfnStartCondition(); /*Start*/
	vfnTransmitData(bSlaveAddress); /*Se escribe al esclavo deseado*/ 
	vfnWaitForTranfer(); /*Se espera el ACK*/
	if(gwTimeout == 50000) /*Si no hay respuesta del esclavo*/
	{
		vfnStopCondition(); /*Finaliza la recepción de datos, se libera el Bus*/
		gwTimeout = 0;
		return _baDataRead;
	}
	vfnTransmitData(wMemoryAddress); /*Se le dice al esclavo desde qué espacio leer*/
	vfnWaitForTranfer(); /*Se espera el ACK*/
	if(gwTimeout == 50000) /*Si no hay respuesta del esclavo*/
	{
		vfnStopCondition(); /*Finaliza la recepción de datos, se libera el Bus*/
		gwTimeout = 0;
		return _baDataRead;
	}

	I2C0_C1 |= I2C_C1_RSTA_MASK; /*Se manda otro Start*/
	bSlaveAddress = bSlaveAddress + 1; /*R/W = 1*/
	vfnTransmitData(bSlaveAddress); /*Ahora se comenzará a leer el esclavo deseado*/ 
	vfnWaitForTranfer(); /*Se espera el ACK*/
	if(gwTimeout == 50000) /*Si no hay respuesta del esclavo*/
	{
		vfnStopCondition(); /*Finaliza la recepción de datos, se libera el Bus*/
		gwTimeout = 0;
		return _baDataRead;
	}

	I2C0_C1 &= ~I2C_C1_TX_MASK; /*Receive mode*/
	I2C0_C1 &= ~I2C_C1_TXAK_MASK; /*Master ACKs enable*/
	_baDataRead[bIndex] = bfnReceiveData(); /*El primer dato leído es la dirección de memoria que regresa el esclavo, este dato debe ser desechado*/
	vfnWaitForTranfer(); /*Se espera a que esté listo el siguiente dato*/
	while(bSize != 1) /*Se leen bSize número de datos*/
	{
		bSize--;
		if(bSize == 1)
		{
			I2C0_C1 |= I2C_C1_TXAK_MASK; /*Master ACKs disabled, ya que es el penúltimo dato por leer*/
		}
		_baDataRead[bIndex++] = bfnReceiveData();
		vfnWaitForTranfer(); /*Se espera a que esté listo el siguiente dato*/
	}
	vfnStopCondition(); /*Finaliza la recepción de datos, se libera el Bus*/
	_baDataRead[bIndex++] = bfnReceiveData(); /*Lee el último dato recibido*/
	return _baDataRead; /*Se regresa el apuntador al arreglo con los datos leidos*/
}

unsigned char bfnBusBusy(void)
{
	if(I2C0_S & I2C_S_BUSY_MASK)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

void vfnWaitForTranfer(void)
{
	while(!(I2C0_S & I2C_S_IICIF_MASK)) /*Mientras no se transfiera el dato*/
	{
		gwTimeout++;
		if(gwTimeout == 50000) /*Si no hay respuesta del esclavo*/
		{
			return;
		}
		/*poll*/
	}
	gwTimeout = 0;
	I2C0_S |= I2C_S_IICIF_MASK; /*Se apaga la bandera*/
}

void vfnWaitForWriteCycle(unsigned char bSlaveAddress)
{
	while(!(I2C0_S & I2C_S_IICIF_MASK)) /*Para saber si el write cycle finalizó, se pollea el ACK al mandar la start condition y el slave address repetidas veces*/
	{
		vfnStartCondition();
		vfnTransmitData(bSlaveAddress); 
	}
	I2C0_S |= I2C_S_IICIF_MASK; /*Se apaga la bandera*/
}

void vfnTransmitData(unsigned char bData)
{
	I2C0_D = bData; /*Se escribe en el registro de Dato*/
}

unsigned char bfnReceiveData(void)
{
	return I2C0_D; /*Se lee el registro de Dato*/
}
