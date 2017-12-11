/*
 * main implementation: use this 'C' sample to create your own application
 *
 */

/*Link to demonstration video: https://photos.app.goo.gl/3ffdFbdUqYCATYiy1*/

#include "derivative.h" /* include peripheral declarations */
#include "PWM.h"
#include "MISCELANEO.h"
#include "ButtonDriver.h"
#include "LedDriver.h"
#include "DisplayDriver.h"

#define LED_VERDE 2
#define BUTTON_SPEED_UP 0
#define BUTTON_SPEED_DOWN 1


/*Ventilador utilizado: PMD1204PQB1-A*/

void vfnPWMCallback(void); /*Funci�n a la que se accede cada que se genera una interrupci�n de canal en el PWM (llega un flanco desde el tac�metro)*/

volatile unsigned char gflgFirstOrSecondCapture = 0; /*Bandera para saber si es el primer o el segundo flanco que se est� midiendo*/
volatile unsigned short gwInputCaptureValue1 = 0; /*Valor de la primera captura del tac�metro*/
volatile unsigned short gwInputCaptureValue2 = 0; /*Valor de la segunda captura del tac�metro*/

volatile unsigned short gwPromedio = 0; /*Lectura de velocidad resultante que se escribir� en los displays*/
unsigned char gbVelocidadPWM = 8; /*Factor de velocidad del ventilador que se controlar� con PWM, siendo 1 la velocidad menor y 16 la mayor*/

int main(void)
{
	static unsigned char _bNoSignalCounter = 0; /*Contador para saber si pas� un tiempo considerable sin se�al, lo cual significa que el ventilador est� apagado*/
	static unsigned short _wVelocidadLeida = 0; /*Resultado de la resta de las muestras de input capture*/
	static unsigned char _bNumeroMuestras = 0; /*Variable para saber las muestras que se han tomado*/
	static unsigned long _dwAcumulador = 0; /*Acumulador para el promedio de muestras*/
	vfnButtonInit(); /*Se inicializan los m�dulos*/
	vfnDisplayInit();
	vfnLedInit();
	vfnPWMInit(&vfnPWMCallback);
	for(;;)
	{	  
		vfnPWMDriver();
		vfnButtonDriver();
		vfnLedDriver();
		vfnDisplayDriver();
		bfnLedBlink(LED_VERDE,10000,10000,1); /*El led verde parpadea una vez cada segundo para demostrar que el sistema funciona*/

		if(gwInputCaptureValue2 && gwInputCaptureValue1) /*Si ya se adquirieron 2 valores del input capture*/
		{
			_wVelocidadLeida = gwInputCaptureValue2 - gwInputCaptureValue1; /*Se hace la resta*/
			if(_wVelocidadLeida > 50000) /*Si la resta da mayor a 50000, quiere decir que hubo un overflow entre los input capture*/
			{
				_wVelocidadLeida = TPM1_MOD - _wVelocidadLeida;
			}
			if(_wVelocidadLeida > 100) /*Usualmente se detectan valores despreciables menores a 100. Estos no deben tomarse en cuenta como una muestra v�lida*/
			{
				_dwAcumulador = _dwAcumulador + _wVelocidadLeida;
				_bNumeroMuestras++;
			}
			gwInputCaptureValue1 = 0; /*Se reinician los valores en cero para no entrar nuevamente en la condici�n*/
			gwInputCaptureValue2 = 0;
			_bNoSignalCounter = 0; /*Como ya hubo se�al, se reinicia esta variable*/
		}
		else if(_bNoSignalCounter == 200) /*Si no hay se�al del tac�metro durante 200 ciclos*/
		{
			gwPromedio  = 0; /*Se afirma que el ventilador est� apagado*/
			_bNoSignalCounter = 0;
		}
		else /*Si no se detect� nada del tac�metro*/
		{
			_bNoSignalCounter++;
		}

		if(_bNumeroMuestras == 200) /*Al haber tomado 200 muestras*/
		{
			gwPromedio = (_dwAcumulador/_bNumeroMuestras); /*Se obtiene un promedio de las muestras*/
			gwPromedio = ((1000000/gwPromedio)*395)/200; /*Se hace una regla de tres para convertir de periodo a RPM (gwPromedio representa el tiempo entre los flancos del tac�metro, es decir, el periodo). Se utilizan ceros dem�s para evitar trabajar con puntos flotantes. La ecuaci�n equivale a 1/periodo para calcular la frecuencia, multiplicado por 3.95, que hace el ajuste de multiplicar por 60 para convertir a RPM y la divisi�n del clk del TPM1 sobre 32. Finalmente se divide este resultado sobre 2, debido a que el tac�metro del PMD1204PQB1-A entrega 2 pulsos por revoluci�n*/
			_bNumeroMuestras = 0;
			_dwAcumulador = 0;
		}


		if(bfnButtonClick(BUTTON_SPEED_UP)) /*Si se presiona el bot�n para acelerar el ventilador*/
		{
			if(gbVelocidadPWM != 16)
			{
				gbVelocidadPWM++;
			}
		}

		if(bfnButtonClick(BUTTON_SPEED_DOWN)) /*Si se presiona el bot�n para desacelerar el ventilador*/
		{
			if(gbVelocidadPWM != 1)
			{
				gbVelocidadPWM--;
			}
		}
	}
}

void vfnPWMCallback(void)
{
	if(!gflgFirstOrSecondCapture)
	{
		gwInputCaptureValue1 = TPM1_C0V; /*Se adquiere la primer captura*/
		gflgFirstOrSecondCapture = 1;
	}

	else
	{
		gwInputCaptureValue2 = TPM1_C0V; /*Se adquiere la segunda captura*/
		gflgFirstOrSecondCapture = 0;
	}
}
