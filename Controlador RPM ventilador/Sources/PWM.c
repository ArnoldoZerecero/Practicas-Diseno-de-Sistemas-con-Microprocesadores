/*
 * PWM.c

 *
 *  Created on: Nov 12, 2017
 *      Author: Jesús Arnoldo Zerecero Núñez
 */
#include "PWM.h"
#include "derivative.h"
#include "MISCELANEO.h"
#include <stddef.h>

static PWMCallback AppCallback;
extern unsigned char gbVelocidadPWM; /*Factor de velocidad del ventilador*/

void vfnPWMInit(PWMCallback ApplicationCallback)
{
	SIM_SOPT2 |= SIM_SOPT2_TPMSRC(1); /*Selecciono MCGFLLCLK*/

	/*Canal de salida de PWM*/
	SIM_SCGC6 |= SIM_SCGC6_TPM0_MASK; /*Se activa clk para TPM0*/
	SIM_SCGC5 |= SIM_SCGC5_PORTD_MASK; /*Se activa clk para puerto D*/
	PORTD_PCR0 |= PORT_PCR_MUX(4); /*Se activa el PTD0 como TPM0_CH0*/

	TPM0_SC |= TPM_SC_CPWMS_MASK; /*Contador en modo center-alligned PWM para TPM0*/
	TPM0_SC |= TPM_SC_CMOD(1); /*Se incrementará el LPTPM con el clock*/

	TPM0_C0SC |= TPM_CnSC_MSB_MASK | TPM_CnSC_ELSB_MASK; /*High true pulses para modo center-alligned PWM para el TPM0_CH0*/ 

	TPM0_MOD = PERIODO; /*Tope de cuenta para TPM0*/

	/*Canal de entrada con Input Capture*/
	NVIC_ISER |= (1<<18); /*Se activan interrupciones para el TPM1*/

	SIM_SCGC6 |= SIM_SCGC6_TPM1_MASK; /*Se activa clk para TPM1*/
	SIM_SCGC5 |= SIM_SCGC5_PORTA_MASK; /*Se activa clk para puerto A*/
	PORTA_PCR12 |= PORT_PCR_MUX(3); /*Se activa el PTA12 como TPM1_CH0 con pullup*/

	TPM1_SC |= TPM_SC_PS(5); /*Clk del contador del TPM1 dividido sobre 32*/

	TPM1_C0SC |= TPM_CnSC_CHIE_MASK; /*Interrupciones de canal activadas*/
	TPM1_C0SC |= TPM_CnSC_ELSA_MASK; /*Modo Input Capture cada flanco positivo para TPM1_CH0*/

	TPM1_SC |= TPM_SC_CMOD(1); /*Se incrementará el LPTPM con el clock*/


	if(ApplicationCallback != NULL)
	{
		AppCallback = ApplicationCallback;
	}
}

void FTM1_IRQHandler()
{
	TPM1_STATUS |= TPM_STATUS_TOF_MASK;
	TPM1_STATUS |= TPM_STATUS_CH0F_MASK; /*Clear channel interrupt flag*/
	AppCallback(); /*Se accede a la función de callback en main*/
}

void vfnPWMDriver(void) /*Se manda el duty cycle para controlar el ventilador. Para una alimentación de 12.5v. Frecuencias de 400Hz a 240Hz para dos pulsos por tacómetro*/
{		
	if(gbVelocidadPWM == 16) 
	{
		TPM0_C0V = PERIODO; /*400 Hz*/
	}
	else if(gbVelocidadPWM == 15)
	{
		TPM0_C0V = 7800; /*390 Hz*/
	}
	else if(gbVelocidadPWM == 14)
	{
		TPM0_C0V = 7650; /*370Hz*/
	}
	else if(gbVelocidadPWM == 13)
	{
		TPM0_C0V = 7500; /*360Hz*/
	}
	else if(gbVelocidadPWM == 13)
	{
		TPM0_C0V = 7400; /*350Hz*/
	}
	else if(gbVelocidadPWM == 12)
	{
		TPM0_C0V = 7300; /*340Hz*/
	}
	else if(gbVelocidadPWM == 11)
	{
		TPM0_C0V = 7100; /*330Hz*/
	}
	else if(gbVelocidadPWM == 10)
	{
		TPM0_C0V = 7000; /*320Hz*/
	}
	else if(gbVelocidadPWM == 9)
	{
		TPM0_C0V = 6800; /*310Hz*/
	}
	else if(gbVelocidadPWM == 8)
	{
		TPM0_C0V = 6600; /*300Hz*/
	}
	else if(gbVelocidadPWM == 7)
	{
		TPM0_C0V = 6500; /*290Hz*/
	}
	else if(gbVelocidadPWM == 6)
	{
		TPM0_C0V = 6350; /*275Hz*/
	}
	else if(gbVelocidadPWM == 5)
	{
		TPM0_C0V = 6200; /*270Hz*/
	}
	else if(gbVelocidadPWM == 4)
	{
		TPM0_C0V = 6050; /*260Hz*/
	}
	else if(gbVelocidadPWM == 3)
	{
		TPM0_C0V = 5800; /*255Hz*/
	}
	else if(gbVelocidadPWM == 2)
	{
		TPM0_C0V = 5500; /*245Hz*/
	}
	else if(gbVelocidadPWM == 1)
	{
		TPM0_C0V = 5000;  /*240Hz*/
	}
}
