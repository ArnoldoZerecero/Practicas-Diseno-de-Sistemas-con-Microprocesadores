/*
 * main implementation: use this 'C' sample to create your own application
 *
 */

/*Link to video demonstration: https://photos.app.goo.gl/GruwuIGN9bWVHR6Q2*/

#include "ButtonDriver.h"
#include "DAC.h"
#include "LCD.h"
#include "PIT.h"
#include "LedDriver.h"
#include "MISCELANEO.h"
#include "derivative.h" /* include peripheral declarations */

#define BUTTON_SIGNAL_CHANGE 0
#define BUTTON_FREQUENCY_UP 1
#define BUTTON_FREQUENCY_DOWN 2
#define BUTTON_SIGNAL_OFF 3
#define LED_VERDE 2
#define BTNS_TIMER 0
#define LEDS_TIMER 1

void vfnLCDSignalWrite(void); /*Función para escribir en el LCD el nombre de la señal actual y su frecuencia*/

void vfnPitCallback(void); /*Función a la que accede la interrupción del PIT cada que su cuenta base finaliza*/

unsigned char gbSenal = 0; /*Variable global para elegir qué señal crear*/

unsigned char gbFrecuencia = 1; /*Variable global para alterar la frecuencia de la señal (de 100Hz en 100Hz hasta 2.5KHz)*/

volatile unsigned char gbIndex = 0; /*Índice para los arreglos de todas las señales*/

const unsigned char kbaPuntosSenales[8][50] = { /*Tabla con valores para graficar punto por punto las señales*/
{127,143,160,175,190,204,216,227,237,244,249,253,255,253,249,244,237,227,216,204,190,175,160,143,127,120,110,94,78,64,50,38,27,17,10,5,1,0,1,5,10,17,27,38,50,64,78,94,110,120}, /*Senoidal*/
{255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, /*Cuadrada*/
{127, 138, 149, 159, 169, 179, 189, 199, 209, 219, 239, 240, 247, 255, 247, 244, 233, 223, 212, 201, 191, 181, 170, 159, 149, 138, 127, 116, 105, 94, 84, 74, 63, 52, 42, 32, 21, 10, 0, 10, 21, 32, 42, 52, 63, 74, 84, 94, 105, 116}, /*Triangular*/
{0, 5, 10, 15, 20, 25, 30, 35, 40, 46, 51, 56, 61, 66, 71, 76, 81, 86, 92, 97, 102, 107, 112, 117, 122, 127, 132, 138, 143, 148, 153, 158, 163, 168, 173, 178, 184, 190, 196, 202, 208, 214, 220, 226, 232, 238, 244, 250, 255}, /*Diente de sierra*/
{0, 68, 135, 168, 182, 201, 222, 227, 232, 237, 239, 241, 243, 246, 248, 250, 251, 252, 253, 254, 254, 255, 255, 222, 190, 162, 135, 108, 100, 87, 75, 64, 54, 44, 36, 28, 22, 16, 11, 9, 8, 6, 5, 4, 3, 2, 1, 1, 0}, /*Carga y descarga de capacitor*/
{0,6,17,33,49,66,81,97,112,127,141,154,167,179,191,201,211,220,228,235,241,246,250,252,254,255,255,253,251,247,243,237,230,223,214,205,194,183,171,159,145,131,117,102,87,71,55,39,22,6}, /*Senoidal rectificada*/
{40, 46, 50, 54, 58, 60, 58, 50, 46, 42, 40, 40, 40, 40, 36, 29, 20, 90, 160, 230, 255, 225, 155, 85, 15, 0, 25, 40, 40, 40, 40, 40, 40, 45, 50, 56, 62, 68, 74, 78, 80, 78, 74, 68, 63, 58, 52, 46, 40, 38}, /*Complejo QRS*/
{0, 0, 0, 0, 1, 1, 2, 3, 4, 6, 8, 9, 11, 13, 16, 19, 22, 25, 28, 32, 36, 40, 44, 49, 54, 58, 64, 69, 75, 81, 87, 93, 100, 106, 114, 121, 129, 136, 144, 152, 160, 169, 178, 187, 196, 205, 215, 225, 238, 255}};  /*Exponencial*/

int main(void)
{
	vfnButtonInit(); /*Se inicializan los módulos*/
	vfnLCDGPIOInit();
	vfnLCDInitConfig();
	vfnLedInit();
	vfnDACGPIOInit();
	vfnDACInitConfig();
	vfnPitInit(TARGET_TIME_8u,&vfnPitCallback);
	vfnBacklightOn();
	vfnLCDSignalWrite(); /*Se escribe la señal en el LCD*/
	vfnPitStart(); /*Comienza el contador del PIT*/
	for(;;) 
	{	  
		vfnButtonDriver(); /*Se revisan los botones*/
		vfnLedDriver(); /*Se actualiza el led*/
		bfnLedBlink(LED_VERDE, 150*gbFrecuencia,150*gbFrecuencia, 1); /*El led verde parpadeará cada 250ms. Se debe multiplicar por la frecuencia para que este valor siempre sea 250ms sin importar las interrupciones del PIT*/
		if(bfnButtonClick(BUTTON_SIGNAL_CHANGE)) /*Si se presiona el botón para cambiar la señal*/
		{
			if(gbSenal != 7)
			{
				gbSenal++;
			}
			else
			{
				gbSenal = 0;
			}
			vfnLCDSignalWrite(); /*Se escribe la señal en el LCD*/
		}

		if(bfnButtonClick(BUTTON_FREQUENCY_UP)) /*Si se presiona el botón para incrementar en 100Hz la señal*/
		{
			if(gbFrecuencia != 1)
			{
				gbFrecuencia--;
			}
			PIT_LDVAL0 = ((10500000/(2600 - gbFrecuencia*100))/50); /*1/F nos da el periodo, eso se divide sobre las 50 muestras por ciclo. Esto nos da los micros a los que se debe pintar. 1u equivale a 10.5 cuentas, así que se multiplica por 10.5. Se incremetan los ceros de la multiplicación para evitar los decimales*/
			vfnLCDSignalWrite(); /*Se escribe la señal en el LCD*/
		}

		if(bfnButtonClick(BUTTON_FREQUENCY_DOWN)) /*Si se presiona el botón para decrementar en 100Hz la señal*/
		{
			if(gbFrecuencia != 25)
			{
				gbFrecuencia++;
			}
			PIT_LDVAL0 = ((10500000/(2600 - gbFrecuencia*100))/50);  /*1/F nos da el periodo, eso se divide sobre las 50 muestras por ciclo. Esto nos da los micros a los que se debe pintar. 1u equivale a 10.5 cuentas, así que se multiplica por 10.5. Se incremetan los ceros de la multiplicación para evitar los decimales*/
			vfnLCDSignalWrite(); /*Se escribe la señal en el LCD*/
		}

		if(bfnButtonClick(BUTTON_SIGNAL_OFF)) /*Si se presiona el botón para apagar o prender la señal*/
		{
			vfnSignalOnOff();
		}
		
		
	}

	return 0;
}

void vfnLCDSignalWrite(void)
{
	unsigned short wFrecuencia = 2600 - gbFrecuencia*100;
	const unsigned char kbaSenoidal[32] = {' ',' ',' ',' ','S','e','n','o','i','d','a','l',' ',' ',' ',' ',' ',' ',' ',' ', CLEAR_ALL_BUT_THOUSANDS(wfnBCD(wFrecuencia)) + 48, CLEAR_ALL_BUT_HUNDREDS(wfnBCD(wFrecuencia)) + 48, CLEAR_ALL_BUT_TENS(wfnBCD(wFrecuencia)) + 48,CLEAR_ALL_BUT_UNITS(wfnBCD(wFrecuencia)) + 48,'H','z',' ',' ',' ',' ',' ',' '};
	const unsigned char kbaCuadrada[32] = {' ',' ',' ',' ','C','u','a','d','r','a','d','a',' ',' ',' ',' ',' ',' ',' ',' ',CLEAR_ALL_BUT_THOUSANDS(wfnBCD(wFrecuencia)) + 48, CLEAR_ALL_BUT_HUNDREDS(wfnBCD(wFrecuencia)) + 48, CLEAR_ALL_BUT_TENS(wfnBCD(wFrecuencia)) + 48,CLEAR_ALL_BUT_UNITS(wfnBCD(wFrecuencia)) + 48,'H','z',' ',' ',' ',' ',' ',' '};
	const unsigned char kbaTriangular[32] = {' ',' ',' ',' ','T','r','i','a','n','g','u','l','a','r',' ',' ',' ',' ',' ',' ',CLEAR_ALL_BUT_THOUSANDS(wfnBCD(wFrecuencia)) + 48, CLEAR_ALL_BUT_HUNDREDS(wfnBCD(wFrecuencia)) + 48, CLEAR_ALL_BUT_TENS(wfnBCD(wFrecuencia)) + 48,CLEAR_ALL_BUT_UNITS(wfnBCD(wFrecuencia)) + 48,'H','z',' ',' ',' ',' ',' ',' '};
	const unsigned char kbaSawtooth[32] = {' ',' ',' ',' ','S','a','w','t','o','o','t','h',' ',' ',' ',' ',' ',' ',' ',' ',CLEAR_ALL_BUT_THOUSANDS(wfnBCD(wFrecuencia)) + 48, CLEAR_ALL_BUT_HUNDREDS(wfnBCD(wFrecuencia)) + 48, CLEAR_ALL_BUT_TENS(wfnBCD(wFrecuencia)) + 48,CLEAR_ALL_BUT_UNITS(wfnBCD(wFrecuencia)) + 48,'H','z',' ',' ',' ',' ',' ',' '};
	const unsigned char kbaCapacitor[32] = {' ',' ',' ',' ','C','a','p','a','c','i','t','o','r',' ',' ',' ',' ',' ',' ',' ',CLEAR_ALL_BUT_THOUSANDS(wfnBCD(wFrecuencia)) + 48, CLEAR_ALL_BUT_HUNDREDS(wfnBCD(wFrecuencia)) + 48, CLEAR_ALL_BUT_TENS(wfnBCD(wFrecuencia)) + 48,CLEAR_ALL_BUT_UNITS(wfnBCD(wFrecuencia)) + 48,'H','z',' ',' ',' ',' ',' ',' '};
	const unsigned char kbaSenoidalRectificada[32] = {' ',' ',' ',' ','S','e','n','o','i','d','a','l','R','e','c','t',' ',' ',' ',' ',CLEAR_ALL_BUT_THOUSANDS(wfnBCD(wFrecuencia)) + 48, CLEAR_ALL_BUT_HUNDREDS(wfnBCD(wFrecuencia)) + 48, CLEAR_ALL_BUT_TENS(wfnBCD(wFrecuencia)) + 48,CLEAR_ALL_BUT_UNITS(wfnBCD(wFrecuencia)) + 48,'H','z',' ',' ',' ',' ',' ',' '};
	const unsigned char kbaComplejo[32] = {' ',' ',' ',' ','C','o','m','p','l','e','j','o',' ','Q','R','S',' ',' ',' ',' ',CLEAR_ALL_BUT_THOUSANDS(wfnBCD(wFrecuencia)) + 48, CLEAR_ALL_BUT_HUNDREDS(wfnBCD(wFrecuencia)) + 48, CLEAR_ALL_BUT_TENS(wfnBCD(wFrecuencia)) + 48,CLEAR_ALL_BUT_UNITS(wfnBCD(wFrecuencia)) + 48,'H','z',' ',' ',' ',' ',' ',' '};
	const unsigned char kbaExponencial[32] = {' ',' ',' ',' ','E','x','p','o','n','e','n','c','i','a','l',' ',' ',' ',' ',' ',CLEAR_ALL_BUT_THOUSANDS(wfnBCD(wFrecuencia)) + 48, CLEAR_ALL_BUT_HUNDREDS(wfnBCD(wFrecuencia)) + 48, CLEAR_ALL_BUT_TENS(wfnBCD(wFrecuencia)) + 48,CLEAR_ALL_BUT_UNITS(wfnBCD(wFrecuencia)) + 48,'H','z',' ',' ',' ',' ',' ',' '};

	if(gbSenal == 0)
	{
		vfnLCDUpdate((unsigned char *)kbaSenoidal);
	}
	else if(gbSenal == 1)
	{
		vfnLCDUpdate((unsigned char *)kbaCuadrada);
	}
	else if(gbSenal == 2)
	{
		vfnLCDUpdate((unsigned char *)kbaTriangular);
	}
	else if(gbSenal == 3)
	{
		vfnLCDUpdate((unsigned char *)kbaSawtooth);
	}
	else if(gbSenal == 4)
	{
		vfnLCDUpdate((unsigned char *)kbaCapacitor);
	}
	else if(gbSenal == 5)
	{
		vfnLCDUpdate((unsigned char *)kbaSenoidalRectificada);
	}
	else if(gbSenal == 6)
	{
		vfnLCDUpdate((unsigned char *)kbaComplejo);
	}
	else if(gbSenal == 7)
	{
		vfnLCDUpdate((unsigned char *)kbaExponencial);
	}	
}

void vfnPitCallback(void) 
{
	DAC0_DAT0L = kbaPuntosSenales[gbSenal][gbIndex] << 4; /*Se divide el valor, 4 bits en la parte HIGH y 4 bits en la parte LOW del registro de DAT0 del DAC para una resolución de 8 bits*/
	DAC0_DAT0H = kbaPuntosSenales[gbSenal][gbIndex] >> 4;
	if(gbIndex != 49) /*Se incrementa el índice o se reinicia si llegó al final del arreglo*/
	{
		gbIndex++;
	}
	else
	{
		gbIndex = 0;
	}
}

