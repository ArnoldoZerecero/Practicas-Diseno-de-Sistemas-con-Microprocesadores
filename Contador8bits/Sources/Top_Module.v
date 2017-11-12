`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    23:45:45 10/05/2017 
// Design Name: 
// Module Name:    Top_Module 
// Project Name: 
// Target Devices: 
// Tool versions: 
// Description: 
//
// Dependencies: 
//
// Revision: 
// Revision 0.01 - File Created
// Additional Comments: 
//
//////////////////////////////////////////////////////////////////////////////////
module Top_module(
input iClk, /*System clk*/
input iReset, /*System reset*/
input iEventos, /*Entrada de eventos (flancos)*/
input iInputCaptureEstimulo, /*Estímulo de entrada para realizar el input capture*/
input [2:0] ivInputSel, /*Selecciona qué tipo de evento se contarán*/
input [2:0] ivInputEstimuloSel, /*Selecciona qué tipo de estimulo que estará esperando el input capture*/
input [2:0] ivDivSel, /*Selecciona cuánto dividir la frecuencia del contador*/
input [7:0] ivCountLoad, /*Selecciona el valor de reset o recarga del contador*/
input iTimerOverflowACK, /*Entrada que confirma cuando el software ya recibió la bandera de Timer Overflow*/
input iInputCaptureACK, /*Entrada que confirma cuando el software ya recibió la captura de cuenta*/
input iOutputCompareACK, /*Entrada que confirma cuando el software ya recibió la bandera de comparación*/
input [7:0] ivCompareValue, /*Valor a comparar en el output compare*/
output [7:0] ovCuenta, /*Salida de la cuenta actual*/
output oTimerOverflow, /*Bandera de Timer Overflow hacia el software*/
output oCapturaFlag, /*Bandera para cuando se realiza una captura en el input capture*/
output [7:0] ovCaptura, /*Valor capturado por el input capture*/
output oComparisonTrueFlag /*Bandera cuando el contador llegó a ser igual al valor de comparación en el output compare*/
    );
	 
wire wFlancosP; /*Entrada basada en detección de flancos positivos*/
wire wFlancosN; /*Entrada basada en detección de flancos negativos*/
wire wFlancosX; /*Entrada basada en detección de cualquier flanco*/
wire wInputMuxContador; /*Entrada elegida para ser medida (eventos, sysclk...)*/
wire wClkDiv2; /*Clk dividido 2 veces*/
wire wClkDiv4; /*Clk dividido 4 veces*/
wire wClkDiv8; /*Clk dividido 8 veces*/
wire wClkDiv16; /*Clk dividido 16 veces*/
wire wDivisorMuxContador; /*División de clk elegida para el contador*/
wire wTimeTargetReachedFlag; /*Bandera de que el contador llegó a su límite*/
wire [7:0] wvCuenta; /*Valor del contador*/
wire wFlancosP2; /*Estimulo para input capture basado en detección de flancos positivos*/
wire wFlancosN2; /*Estimulo para input capture basado en detección de flancos negativos*/
wire wFlancosX2; /*Estimulo para input capture basado en detección de cualquier flanco*/
wire wInputMuxEstimulo; /*Estímulo seleccionado para el input capture*/
wire wFlancoTimerOverflowACK; /*Salida del detector de flancos*/
wire wFlancoInputCaptureACK; /*Salida del detector de flancos*/
wire wFlancoOutputCompareACK; /*Salida del detector de flancos*/


assign ovCuenta = wvCuenta; /*Se manda la cuenta como salida externa para poder ser leida por el microcontrolador*/

	flancos flancos( /*Se crean 3 tipos de cuentas basadas en el tipo de flanco de entrada del evento externo*/
	.iClk (iClk),
	.iReset (iReset),
	.iExternalInput (iEventos),
	.oFlancosP (wFlancosP),
	.oFlancosN (wFlancosN),
	.oFlancosX (wFlancosX)
	);
	
	input_mux input_mux( /*Multiplexor entre el tipo de evento a contar*/
	.iClk (iClk),
	.iReset (iReset),
	.ivSel (ivInputSel),
	.iFlancosP (wFlancosP),
	.iFlancosN (wFlancosN),
	.iFlancosX (wFlancosX),
	.oSalida (wInputMuxContador)
	);
	
	divisor divisor( /*Divisor de frecuencia*/
	.iClk (iClk),
	.iReset (iReset),
	.oClkDiv2 (wClkDiv2),
	.oClkDiv4 (wClkDiv4),
	.oClkDiv8 (wClkDiv8),
	.oClkDiv16 (wClkDiv16)
	);
	
	divisor_mux divisor_mux( /*Multiplexor para elegir qué clk dividido utilizará el contador*/
	.iClk (iClk),
	.iReset (iReset),
	.ivSel (ivDivSel),
	.iClk2 (wClkDiv2),
	.iClk4 (wClkDiv4),
	.iClk8 (wClkDiv8),
	.iClk16 (wClkDiv16),
	.oSalida (wDivisorMuxContador)
	);
	
	contador contador( /*Contador de 8 bits que se recarga con un valor definido al llegar a 0*/
	.iClk (iClk),
	.iClkE (wDivisorMuxContador),
	.iReset (iReset),
	.ivCountLoad (ivCountLoad),
	.iSenalCont (wInputMuxContador),
	.oCompareFlag (wTimeTargetReachedFlag),
	.ovCuenta (wvCuenta)
	);
	
	detector_flancos detector_flancos_timer_event( /*Manda un uno único al detectar una señal de ACK (para evitar un reset continuo del módulo)*/
	.iClk (iClk),
	.iReset (iReset),
	.iSenal (iTimerOverflowACK),
	.oFlanco (wFlancoTimerOverflowACK)
	);
	
	timer_event timer_event( /*Checa el acknowledge que regresa el micro para verificar si ya se recibió la bandera de Timer Overflow*/
	.iClk (iClk),
	.iReset (wFlancoTimerOverflowACK), /*Cuando se reciba la confirmación por software, la bandera de Timer Overflow se apaga*/
	.iComparisonTrue (wTimeTargetReachedFlag),
	.oTimerOverflow (oTimerOverflow)
	);
	
	flancos flancos_input_capture( /*Se crean 3 tipos de cuentas basadas en el tipo de flanco de entrada del estímulo externo para el input capture*/
	.iClk (iClk),
	.iReset (iReset),
	.iExternalInput (iInputCaptureEstimulo),
	.oFlancosP (wFlancosP2),
	.oFlancosN (wFlancosN2),
	.oFlancosX (wFlancosX2)
	);
	
	input_mux input_mux_estimulo_input_capture( /*Multiplexor entre el tipo de estimulo a detectar para el input capture*/
	.iClk (iClk),
	.iReset (iReset),
	.ivSel (ivInputEstimuloSel),
	.iFlancosP (wFlancosP2),
	.iFlancosN (wFlancosN2),
	.iFlancosX (wFlancosX2),
	.oSalida (wInputMuxEstimulo)
	);
	
	detector_flancos detector_flancos_input_capture( /*Manda un uno único al detectar una señal de ACK (para evitar un reset continuo del módulo)*/
	.iClk (iClk),
	.iReset (iReset),
	.iSenal (iInputCaptureACK),
	.oFlanco (wFlancoInputCaptureACK)
	);
	
	input_capture input_capture( /*Adquiere el valor actual del contador cuando recibe cierto estimulo (algún tipo de flanco definido por el input_mux)*/
	.iClk (iClk),
	.iReset (wFlancoInputCaptureACK), /*Cuando reciba la confirmación de software, se limpian los registros de salida*/
	.iEstimulo (wInputMuxEstimulo),
	.ivCuenta (wvCuenta),
	.ovCaptura (ovCaptura),
	.oCapturaFlag (oCapturaFlag)
	);
	
	detector_flancos detector_flancos_output_compare( /*Manda un uno único al detectar una señal de ACK (para evitar un reset continuo del módulo)*/
	.iClk (iClk),
	.iReset (iReset),
	.iSenal (iOutputCompareACK),
	.oFlanco (wFlancoOutputCompareACK)
	);
	
	output_compare output_compare( /*Compara constantemente el contador con un valor de comparación*/
	.iClk (iClk),
	.iReset (wFlancoOutputCompareACK),/*Cuando reciba la confirmación de software, se limpian los registros de salida*/
	.ivCuenta (wvCuenta),
	.ivCompareValue (ivCompareValue),
	.oComparisonTrueFlag (oComparisonTrueFlag)
	);

endmodule
