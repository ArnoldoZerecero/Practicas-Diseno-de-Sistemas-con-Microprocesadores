/*
 * LCD.c
 *
 *  Created on: Oct 27, 2017
 *      Author: Jesús Arnoldo Zerecero Núñez
 */

#include "derivative.h"
#include "LCD.h"

extern unsigned long kdwaPinValue[32]; /*Se utilizará el arreglo externo de potencias de dos*/

volatile unsigned char gbData; /*Variable para almacenar el caracter o comando a mandar*/

volatile unsigned long gdwDelay; /*Cuenta para el delay entre estados*/

void (* const vfnapEstados[])(void) = /*Arreglo de apuntadores a las funciones (estados)*/
{
		vfnIdle,
		vfnLCDDelay,
		vfnRSSet,
		vfnRSClear,
		vfnEnableSet,
		vfnEnableClear,
		vfnPrevDataClear,
		vfnDataSend,
};

void vfnLCDGPIOInit(void) /*Inicialización de pantalla LCD*/
{
	#if PORTA_ENABLE
	SIM_SCGC5  |= SIM_SCGC5_PORTA_MASK; /*Se activa el clk para el puerto A*/
	#endif
	#if PORTB_ENABLE
	SIM_SCGC5  |= SIM_SCGC5_PORTB_MASK; /*Se activa el clk para el puerto B*/
	#endif
	#if PORTC_ENABLE
	SIM_SCGC5  |= SIM_SCGC5_PORTC_MASK; /*Se activa el clk para el puerto C*/
	#endif
	#if PORTD_ENABLE
	SIM_SCGC5  |= SIM_SCGC5_PORTD_MASK; /*Se activa el clk para el puerto C*/
	#endif
	#if PORTE_ENABLE
	SIM_SCGC5  |= SIM_SCGC5_PORTE_MASK; /*Se activa el clk para el puerto E*/
	#endif

	RS_PORT_PCR |= PORT_PCR_MUX(1); 
	RS_PORT_PDDR |= kdwaPinValue[RS_PIN];

	ENABLE_PORT_PCR |= PORT_PCR_MUX(1);
	ENABLE_PORT_PDDR |= kdwaPinValue[ENABLE_PIN];
	
	DATA1_PORT_PCR |= PORT_PCR_MUX(1); 
	DATA1_PORT_PDDR |= kdwaPinValue[DATA1_PIN];
	
	DATA2_PORT_PCR |= PORT_PCR_MUX(1);
	DATA2_PORT_PDDR |= kdwaPinValue[DATA2_PIN];

	DATA3_PORT_PCR |= PORT_PCR_MUX(1);
	DATA3_PORT_PDDR |= kdwaPinValue[DATA3_PIN];

	DATA4_PORT_PCR |= PORT_PCR_MUX(1);
	DATA4_PORT_PDDR |= kdwaPinValue[DATA4_PIN];

	BACKLIGHT_PORT_PCR |= PORT_PCR_MUX(1); 
	BACKLIGHT_PORT_PDDR |= kdwaPinValue[BACKLIGHT_PIN];

	tVariablesEstados.bEstadoActual = IDLE_STATE; /*El sistema comienza en estado IDLE*/
}

void vfnBacklightOn(void)
{
	BACKLIGHT_PORT_PDOR |= kdwaPinValue[BACKLIGHT_PIN];
}

void vfnBacklightOff(void)
{
	BACKLIGHT_PORT_PDOR &= ~kdwaPinValue[BACKLIGHT_PIN];
}

void vfnLCDDriver(void)
{
	if(tVariablesEstados.bEstadoActual < MAX_STATES) /*Si el estado elegido existe*/
	{
		vfnapEstados[tVariablesEstados.bEstadoActual](); /*Se accede a la función de estado correspondiente a través del arreglo de apuntadores a funciones*/
	}
}

unsigned char bfnLCDBusy(void) /*Revisa si el LCD se encuentra en un estado diferente a IDLE (está desocupado)*/
{
	if(tVariablesEstados.bEstadoActual != IDLE_STATE)
	{
		return 1;
	}
	return 0;
}

void vfnLCDUpdate(unsigned char *bpLCDArray) /*Actualiza toda la pantalla de LCD*/
{
	unsigned char bIndexEspacio = 0; /*Índice para saber qué espacio del LCD escribir*/
	unsigned char bLineaActual = 0; /*Variable para saber en qué linea se está escribiendo*/

	#if !LCD_16X2_OR_20X2	
	while(bIndexEspacio != 32) /*Mientras no se hayan terminado de escribir todos los caracteres*/
	#else
	while(bIndexEspacio != 40) /*Mientras no se hayan terminado de escribir todos los caracteres*/
	#endif
	{
		if(bLineaActual == 0) /*Se comenzará a escribir desde la primera linea*/
		{
			vfnSendLCDCommand(FIRST_ROW_BEGIN); 
			bLineaActual = 1;
		}
		#if !LCD_16X2_OR_20X2	
		else if(bLineaActual == 1 && bIndexEspacio == 16) /*Al llenar la primera linea, se comenzará a escribir desde la segunda*/
		#else
		else if(bLineaActual == 1 && bIndexEspacio == 20) /*Al llenar la primera linea, se comenzará a escribir desde la segunda*/
		#endif
		{
			vfnSendLCDCommand(SECOND_ROW_BEGIN);
			bLineaActual = 2;
		}
		else /*Se escriben uno por uno los caracteres*/
		{
			vfnSendLCDCharacter(bpLCDArray[bIndexEspacio]); /*Se manda escribir la posición del arreglo de caracteres definida por el índice*/
			bIndexEspacio++;
		}
		while(tVariablesEstados.bEstadoActual != IDLE_STATE) /*Se entra al driver para hacer mandar el comando o el caracter*/
		{
			vfnLCDDriver();
		}
	}
}


void vfnSendLCDCommand(unsigned char bCommand) /*Función para escribir un comando*/
{
	gbData = bCommand; /*La variable global adquiere el comando recibido para ser mandado al LCD*/
	tVariablesEstados.bEstadoActual = RS_CLEAR_STATE; /*El estado ahora será el de RS en cero, debido a que se mandará un comando*/
}

void vfnSendLCDCharacter(unsigned char bCharacter) /*Función para escribir un caracter*/
{
	gbData = bCharacter; /*La variable global adquiere el caracter recibido para ser mandado al LCD*/
	tVariablesEstados.bEstadoActual = RS_SET_STATE; /*El estado ahora será el de RS en uno, debido a que se mandará un caracter*/
}

void vfnLCDInitConfig(void)
{
	vfnSendLCDCommand(FOUR_BIT_TWO_LINES); /*Se configura el LCD en modo de 4 bits*/
	while(tVariablesEstados.bEstadoActual != IDLE_STATE) /*Se entra al driver para hacer el cambio de estados hasta que el comando haya finalizado de mandarse*/
	{
		vfnLCDDriver();
	}

	vfnSendLCDCommand(CLEAR_DISPLAY); /*Se limpia la pantalla*/
	while(tVariablesEstados.bEstadoActual != IDLE_STATE) /*Se entra al driver para hacer el cambio de estados hasta que el comando haya finalizado de mandarse*/
	{
		vfnLCDDriver();
	}
}

void vfnDisplayOn(void)
{
	vfnSendLCDCommand(CURSOR_OFF);
}

void vfnDisplayOff(void)
{
	vfnSendLCDCommand(DISPLAY_OFF);
}

void vfnCursorOn(void)
{
	vfnSendLCDCommand(CURSOR_ON);
}

void vfnCursorOff(void)
{
	vfnSendLCDCommand(CURSOR_OFF);
}

void vfnCursorBlink(void)
{
	vfnSendLCDCommand(CURSOR_BLINK);
}


void vfnNewCharacter(const unsigned char *bpDibujo, unsigned char bSize, unsigned char bAddress) /*Declara un nuevo caracter para pintar en la memoria del LCD*/
{
	if(bAddress <= 7) /*Por seguridad, en caso de que el usuario introduce una dirección no válida*/
	{
		vfnSendLCDCommand(CGRAM_ADDRESS + 8*bAddress); /*Se manda el comando de la dirección de CGRAM para saber donde guardar el nuevo caracter*/
		while(tVariablesEstados.bEstadoActual != IDLE_STATE) /*Se entra al driver para hacer el cambio de estados hasta que el comando haya finalizado de mandarse*/
		{
			vfnLCDDriver();
		}

		while(bSize--) /*Hasta que se hayan mandado todas las partes del dibujo*/
		{
			vfnSendLCDCharacter(*bpDibujo++); /*Se manda una parte del dibujo*/
			while(tVariablesEstados.bEstadoActual != IDLE_STATE) /*Se entra al driver para hacer el cambio de estados hasta que esa parte del dibujo haya finalizado de mandarse*/
			{
				vfnLCDDriver();
			}
		}
	}
}

void vfnIdle(void) /*Función vacía a la cual se accederá mientras el LCD esté desocupado*/
{

}

void vfnLCDDelay(void) /*Cuenta para dejar pasar un tiempo entre estados, respetando las especificaciones del LCD*/
{
	if(!(--gdwDelay))
	{
		tVariablesEstados.bEstadoActual = tVariablesEstados.bEstadoSiguiente; /*Cuando se termine el delay, se accede al siguiente estado*/
	}
}

void vfnRSSet(void) /*Manda un uno al pin de RS (para escribir un caracter)*/
{
	RS_PORT_PDOR |= kdwaPinValue[RS_PIN];
	gdwDelay = 1; /*Delay de 97ns*/
	tVariablesEstados.bEstadoActual = DELAY_STATE;
	tVariablesEstados.bEstadoSiguiente = PREV_DATA_CLEAR_STATE; /*Ahora se limpiará el caracter/comando anterior*/
}

void vfnRSClear(void) /*Manda un cero al pin de RS (para mandar un comando)*/
{
	RS_PORT_PDOR &= ~kdwaPinValue[RS_PIN];
	gdwDelay = 1; /*Delay de 97ns*/
	tVariablesEstados.bEstadoActual = DELAY_STATE;
	tVariablesEstados.bEstadoSiguiente = PREV_DATA_CLEAR_STATE; /*Ahora se limpiará el caracter/comando anterior*/
}

void vfnEnableSet(void) /*Manda un uno al pin de Enable*/
{
	ENABLE_PORT_PDOR |= kdwaPinValue[ENABLE_PIN];
	gdwDelay = 13; /*Delay de 1261ns*/
	tVariablesEstados.bEstadoActual = DELAY_STATE;
	tVariablesEstados.bEstadoSiguiente = ENABLE_CLEAR_STATE; /*Ahora se apagará el enable*/
}

void vfnEnableClear(void) /*Manda un cero al pin de Enable*/
{
	ENABLE_PORT_PDOR &= ~kdwaPinValue[ENABLE_PIN];
	gdwDelay = 3; /*Delay de 291ns*/
	tVariablesEstados.bEstadoActual = DELAY_STATE;
	if(gbData != DATA_SENT) /*Si aun falta una parte del dato por mandar (un 32 en gbData indica que el dato ya fue enviado en su totalidad*/
	{
		tVariablesEstados.bEstadoSiguiente = PREV_DATA_CLEAR_STATE; /*Se limpiará nuevamente el caracter/comando anterior para escribir la segunda parte*/
	}
	else
	{
		tVariablesEstados.bEstadoSiguiente = IDLE_STATE; /*Se desocupa el LCD*/
	}
}

void vfnPrevDataClear(void) /*Se limpia el caracter o comando mandado con anterioridad*/
{
	DATA1_PORT_PDOR &= ~kdwaPinValue[DATA1_PIN];
	DATA2_PORT_PDOR &= ~kdwaPinValue[DATA2_PIN];
	DATA3_PORT_PDOR &= ~kdwaPinValue[DATA3_PIN];
	DATA4_PORT_PDOR &= ~kdwaPinValue[DATA4_PIN];
	/*No se necesita delay*/
	tVariablesEstados.bEstadoActual = DATA_SEND_STATE; /*Ahora se mandará el comando/dato*/
}

void vfnDataSend(void) /*Se manda una parte (de 4 bits) del dato del caracter o del comando para el LCD*/
{
	static unsigned char _bFourBitData; /*Variable para escribir el MSB o el LSB en el puerto*/
	static unsigned char _flgInstancia = 0; /*Bandera para conocer si se está escribiendo la primera parte del dato (0) o la segunda parte del dato (1)*/

	if(gbData <= 0b1111) /*Si no existen MSBs*/
	{
		if(_flgInstancia == 0) /*Si aun no se escribe la primera parte del dato*/
		{
			_bFourBitData = 0; /*Se manda escribir un cero a los MSBs del LCD*/
			_flgInstancia = 1;
		}
		else 
		{
			_bFourBitData = gbData; /*Se escriben en bFourBitData los LSB*/
			gbData = DATA_SENT; /*Se escribe un 32 en gbData para hacerle saber al sistema que ambas partes del dato fueron mandadas (32 es un número que no existe como comando ni como un código ASCII válido desde el punto de vista del LCD)*/ 
			_flgInstancia = 0;
		}
	}
	else if(gbData > 0b1111) /*Si existen MSBs*/
	{
		_bFourBitData = gbData >> 4; /*Se escriben en bFourBitData los MSB*/
		gbData &= ~MSB_CLEAR; /*Los MSB se borran*/
		_flgInstancia = 1;
	}
	DATA1_PORT_PDOR |= ((_bFourBitData & 1) << DATA1_PIN); /*Se manda bit por bit el _bFourBitData al LCD*/
	DATA2_PORT_PDOR |= ((_bFourBitData & 2) << (DATA2_PIN - 1));
	DATA3_PORT_PDOR |= ((_bFourBitData & 4) << (DATA3_PIN - 2));
	DATA4_PORT_PDOR |= ((_bFourBitData & 8) << (DATA4_PIN - 3));

	gdwDelay = 1; /*Delay de 97ns*/
	tVariablesEstados.bEstadoActual = DELAY_STATE;
	tVariablesEstados.bEstadoSiguiente = ENABLE_SET_STATE; /*Ahora se encenderá el enable*/
}



