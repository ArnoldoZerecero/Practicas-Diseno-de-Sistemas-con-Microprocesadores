`timescale 1ns / 1ps

////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer:
//
// Create Date:   22:39:46 10/22/2017
// Design Name:   Top_module
// Module Name:   D:/Documents/UAG/ISE/Contador8bits/Top_Module_Test.v
// Project Name:  Contador8bits
// Target Device:  
// Tool versions:  
// Description: 
//
// Verilog Test Fixture created by ISE for module: Top_module
//
// Dependencies:
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
////////////////////////////////////////////////////////////////////////////////

module Top_Module_Test;

	// Inputs
	reg iClk;
	reg iReset;
	reg iEventos;
	reg iInputCaptureEstimulo;
	reg [2:0] ivInputSel;
	reg [2:0] ivInputEstimuloSel;
	reg [2:0] ivDivSel;
	reg [7:0] ivCountLoad;
	reg iTimerOverflowACK;
	reg iInputCaptureACK;
	reg iOutputCompareACK;
	reg [7:0] ivCompareValue;

	// Outputs
	wire [7:0] ovCuenta;
	wire oTimerOverflow;
	wire oCapturaFlag;
	wire [7:0] ovCaptura;
	wire oComparisonTrueFlag;

	// Instantiate the Unit Under Test (UUT)
	Top_module uut (
		.iClk(iClk), 
		.iReset(iReset), 
		.iEventos(iEventos), 
		.iInputCaptureEstimulo(iInputCaptureEstimulo), 
		.ivInputSel(ivInputSel), 
		.ivInputEstimuloSel(ivInputEstimuloSel), 
		.ivDivSel(ivDivSel), 
		.ivCountLoad(ivCountLoad), 
		.iTimerOverflowACK(iTimerOverflowACK), 
		.iInputCaptureACK(iInputCaptureACK), 
		.iOutputCompareACK(iOutputCompareACK), 
		.ivCompareValue(ivCompareValue), 
		.ovCuenta(ovCuenta), 
		.oTimerOverflow(oTimerOverflow), 
		.oCapturaFlag(oCapturaFlag), 
		.ovCaptura(ovCaptura), 
		.oComparisonTrueFlag(oComparisonTrueFlag)
	);

	initial begin
		iClk = 0; /*Se comienza haciendo un reset durante 2 ciclos de iClk*/
		iReset = 1'b1; 
		repeat(4) #10 iClk = ~iClk;
		iReset = 0;
		iEventos = 0;
		iInputCaptureEstimulo = 0;
		iTimerOverflowACK = 0; /*El acknowledge por software comienza valiendo 0*/
		iInputCaptureACK = 0;
		iOutputCompareACK = 0;
		ivCountLoad = 8'd5; /*La cuenta siempre se carga con 5*/
		ivCompareValue = 8'd3; /*El valor de comparación siempre será 3*/
		forever #10 iClk = ~iClk; /*Se genera un Clk*/
	end
	
	initial begin
		// Initialize Inputs
		ivInputSel = 3'd4; /*Caso 1: Flancos positivos*/
		ivInputEstimuloSel = 3'd4;
		ivDivSel = 3'd0;
		ivCountLoad = 8'd5; /*La cuenta siempre se carga con 5*/
		ivCompareValue = 8'd3; /*El valor de comparación siempre será 3*/
		repeat(6) #200  iEventos = ~iEventos; /*Se simulan 3 señales externas para los flancos*/
		repeat (4) #200 iInputCaptureEstimulo = ~iInputCaptureEstimulo; /*Se simulan 2 señales externas para el estimulo del input capture*/
		iInputCaptureACK = 1; /*Se simula un ACK para el input capture*/
		iOutputCompareACK = 1; /*Se simula un ACK para el output compare*/
		repeat(6) #200  iEventos = ~iEventos; /*Se simulan 3 señales externas para los flancos*/
		repeat (4) #200 iInputCaptureEstimulo = ~iInputCaptureEstimulo; /*Se simulan 2 señales externas para el estimulo del input capture*/
		iInputCaptureACK = 0; /*Hasta ahora se clearea el ACK para el input capture*/
		iOutputCompareACK = 0; /*Hasta ahora se clearea el ACK para el output compare*/
		#500;
		
		ivInputSel = 3'd3; /*Caso 2: Flancos negativos*/
		ivInputEstimuloSel = 3'd3;
		ivDivSel = 3'd0;
		ivCountLoad = 8'd5; /*La cuenta siempre se carga con 5*/
		ivCompareValue = 8'd3; /*El valor de comparación siempre será 3*/
		repeat(6) #200  iEventos = ~iEventos; /*Se simulan 3 señales externas para los flancos*/
		repeat (4) #200 iInputCaptureEstimulo = ~iInputCaptureEstimulo; /*Se simulan 2 señales externas para el estimulo del input capture*/
		repeat (2) #200 iInputCaptureACK = ~iInputCaptureACK; /*Se simula un ACK para el input capture*/
		repeat (2) #200 iOutputCompareACK = ~iOutputCompareACK; /*Se simula un ACK para el output compare*/
		repeat(6) #200  iEventos = ~iEventos; /*Se simulan 3 señales externas para los flancos*/
		repeat (4) #200 iInputCaptureEstimulo = ~iInputCaptureEstimulo; /*Se simulan 2 señales externas para el estimulo del input capture*/
		repeat (2) #200 iInputCaptureACK = ~iInputCaptureACK; /*Se simula un ACK para el input capture*/
		repeat (2) #200 iOutputCompareACK = ~iOutputCompareACK; /*Se simula un ACK para el output compare*/
		#500;
		
		ivInputSel = 3'd2; /*Caso 3: Cualquier flanco*/
		ivInputEstimuloSel = 3'd2;
		ivDivSel = 3'd0;
		ivCountLoad = 8'd5; /*La cuenta siempre se carga con 5*/
		ivCompareValue = 8'd3; /*El valor de comparación siempre será 3*/
		repeat(6) #200  iEventos = ~iEventos; /*Se simulan 3 señales externas para los flancos*/
		repeat (4) #200 iInputCaptureEstimulo = ~iInputCaptureEstimulo; /*Se simulan 2 señales externas para el estimulo del input capture*/
		repeat (2) #200 iInputCaptureACK = ~iInputCaptureACK; /*Se simula un ACK para el input capture*/
		repeat (2) #200 iOutputCompareACK = ~iOutputCompareACK; /*Se simula un ACK para el output compare*/
		repeat(6) #200  iEventos = ~iEventos; /*Se simulan 3 señales externas para los flancos*/
		repeat (4) #200 iInputCaptureEstimulo = ~iInputCaptureEstimulo; /*Se simulan 2 señales externas para el estimulo del input capture*/
		repeat (2) #200 iInputCaptureACK = ~iInputCaptureACK; /*Se simula un ACK para el input capture*/
		repeat (2) #200 iOutputCompareACK = ~iOutputCompareACK; /*Se simula un ACK para el output compare*/
		#500;
		
		ivInputSel = 3'd1; /*Caso 4: iClk/2 e iClk siendo el estimulo para la captura*/
		ivInputEstimuloSel = 3'd1;
		ivDivSel = 3'd1;
		ivCountLoad = 8'd5; /*La cuenta siempre se carga con 5*/
		ivCompareValue = 8'd3; /*El valor de comparación siempre será 3*/
		repeat(6) #200  iEventos = ~iEventos; /*Se simulan 3 señales externas para los flancos*/
		repeat (4) #200 iInputCaptureEstimulo = ~iInputCaptureEstimulo; /*Se simulan 2 señales externas para el estimulo del input capture*/
		repeat (2) #200 iInputCaptureACK = ~iInputCaptureACK; /*Se simula un ACK para el input capture*/
		repeat (2) #200 iOutputCompareACK = ~iOutputCompareACK; /*Se simula un ACK para el output compare*/
		repeat(6) #200  iEventos = ~iEventos; /*Se simulan 3 señales externas para los flancos*/
		repeat (4) #200 iInputCaptureEstimulo = ~iInputCaptureEstimulo; /*Se simulan 2 señales externas para el estimulo del input capture*/
		repeat (2) #200 iInputCaptureACK = ~iInputCaptureACK; /*Se simula un ACK para el input capture*/
		repeat (2) #200 iOutputCompareACK = ~iOutputCompareACK; /*Se simula un ACK para el output compare*/
		#500;
		
		ivInputSel = 3'd1; /*Caso 5: iClk/4*/
		ivInputEstimuloSel = 3'd4;
		ivDivSel = 3'd2;		
		ivCountLoad = 8'd5; /*La cuenta siempre se carga con 5*/
		ivCompareValue = 8'd3; /*El valor de comparación siempre será 3*/
		repeat(6) #200  iEventos = ~iEventos; /*Se simulan 3 señales externas para los flancos*/
		repeat (4) #200 iInputCaptureEstimulo = ~iInputCaptureEstimulo; /*Se simulan 2 señales externas para el estimulo del input capture*/
		repeat (2) #200 iInputCaptureACK = ~iInputCaptureACK; /*Se simula un ACK para el input capture*/
		repeat (2) #200 iOutputCompareACK = ~iOutputCompareACK; /*Se simula un ACK para el output compare*/
		repeat(6) #200  iEventos = ~iEventos; /*Se simulan 3 señales externas para los flancos*/
		repeat (4) #200 iInputCaptureEstimulo = ~iInputCaptureEstimulo; /*Se simulan 2 señales externas para el estimulo del input capture*/
		repeat (2) #200 iInputCaptureACK = ~iInputCaptureACK; /*Se simula un ACK para el input capture*/
		repeat (2) #200 iOutputCompareACK = ~iOutputCompareACK; /*Se simula un ACK para el output compare*/		
		#500;
		
		ivInputSel = 3'd1; /*Caso 6: iClk/8*/
		ivInputEstimuloSel = 3'd4;
		ivDivSel = 3'd3;
		ivCountLoad = 8'd5; /*La cuenta siempre se carga con 5*/
		ivCompareValue = 8'd3; /*El valor de comparación siempre será 3*/
		repeat(6) #200  iEventos = ~iEventos; /*Se simulan 3 señales externas para los flancos*/
		repeat (4) #200 iInputCaptureEstimulo = ~iInputCaptureEstimulo; /*Se simulan 2 señales externas para el estimulo del input capture*/
		repeat (2) #200 iInputCaptureACK = ~iInputCaptureACK; /*Se simula un ACK para el input capture*/
		repeat (2) #200 iOutputCompareACK = ~iOutputCompareACK; /*Se simula un ACK para el output compare*/
		repeat(6) #200  iEventos = ~iEventos; /*Se simulan 3 señales externas para los flancos*/
		repeat (4) #200 iInputCaptureEstimulo = ~iInputCaptureEstimulo; /*Se simulan 2 señales externas para el estimulo del input capture*/
		repeat (2) #200 iInputCaptureACK = ~iInputCaptureACK; /*Se simula un ACK para el input capture*/
		repeat (2) #200 iOutputCompareACK = ~iOutputCompareACK; /*Se simula un ACK para el output compare*/
		#500;
		
		ivInputSel = 3'd1; /*Caso 7: iClk/16 y sin estímulo para input capture*/
		ivInputEstimuloSel = 0;
		ivDivSel = 3'd4;
		ivCountLoad = 8'd5; /*La cuenta siempre se carga con 5*/
		ivCompareValue = 8'd3; /*El valor de comparación siempre será 3*/
		repeat(6) #200  iEventos = ~iEventos; /*Se simulan 3 señales externas para los flancos*/
		repeat (4) #200 iInputCaptureEstimulo = ~iInputCaptureEstimulo; /*Se simulan 2 señales externas para el estimulo del input capture*/
		repeat (2) #200 iInputCaptureACK = ~iInputCaptureACK; /*Se simula un ACK para el input capture*/
		repeat (2) #200 iOutputCompareACK = ~iOutputCompareACK; /*Se simula un ACK para el output compare*/
		repeat(6) #200  iEventos = ~iEventos; /*Se simulan 3 señales externas para los flancos*/
		repeat (4) #200 iInputCaptureEstimulo = ~iInputCaptureEstimulo; /*Se simulan 2 señales externas para el estimulo del input capture*/
		repeat (2) #200 iInputCaptureACK = ~iInputCaptureACK; /*Se simula un ACK para el input capture*/
		repeat (2) #200 iOutputCompareACK = ~iOutputCompareACK; /*Se simula un ACK para el output compare*/
		#500;
		
		ivInputSel = 3'd0; /*Caso 8: iClk apagado (se pausa la cuenta)*/
		ivInputEstimuloSel = 3'd4;
		ivDivSel = 3'd4;
		ivCountLoad = 8'd5; /*La cuenta siempre se carga con 5*/
		ivCompareValue = 8'd3; /*El valor de comparación siempre será 3*/
		repeat(6) #200  iEventos = ~iEventos; /*Se simulan 3 señales externas para los flancos*/
		repeat (4) #200 iInputCaptureEstimulo = ~iInputCaptureEstimulo; /*Se simulan 2 señales externas para el estimulo del input capture*/
		repeat (2) #200 iInputCaptureACK = ~iInputCaptureACK; /*Se simula un ACK para el input capture*/
		repeat (2) #200 iOutputCompareACK = ~iOutputCompareACK; /*Se simula un ACK para el output compare*/
		repeat(6) #200  iEventos = ~iEventos; /*Se simulan 3 señales externas para los flancos*/
		repeat (4) #200 iInputCaptureEstimulo = ~iInputCaptureEstimulo; /*Se simulan 2 señales externas para el estimulo del input capture*/
		repeat (2) #200 iInputCaptureACK = ~iInputCaptureACK; /*Se simula un ACK para el input capture*/
		repeat (2) #200 iOutputCompareACK = ~iOutputCompareACK; /*Se simula un ACK para el output compare*/
		#500;
		
		ivInputSel = 3'd4; /*Caso 9: La cuenta se carga con 0*/
		ivInputEstimuloSel = 3'd4;
		ivDivSel = 3'd0;
		ivCountLoad = 8'd0; /*La cuenta se carga con 0*/
		ivCompareValue = 8'd3; /*El valor de comparación siempre será 3*/
		repeat(6) #200  iEventos = ~iEventos; /*Se simulan 3 señales externas para los flancos*/
		repeat (4) #200 iInputCaptureEstimulo = ~iInputCaptureEstimulo; /*Se simulan 2 señales externas para el estimulo del input capture*/
		repeat (2) #200 iInputCaptureACK = ~iInputCaptureACK; /*Se simula un ACK para el input capture*/
		repeat (2) #200 iOutputCompareACK = ~iOutputCompareACK; /*Se simula un ACK para el output compare*/
		repeat(6) #200  iEventos = ~iEventos; /*Se simulan 3 señales externas para los flancos*/
		repeat (4) #200 iInputCaptureEstimulo = ~iInputCaptureEstimulo; /*Se simulan 2 señales externas para el estimulo del input capture*/
		repeat (2) #200 iInputCaptureACK = ~iInputCaptureACK; /*Se simula un ACK para el input capture*/
		repeat (2) #200 iOutputCompareACK = ~iOutputCompareACK; /*Se simula un ACK para el output compare*/
		#500;
		
		ivInputSel = 3'd4; /*Caso 10: La cuenta se carga con 0 y la condición de comparación siempre se cumplirá*/
		ivInputEstimuloSel = 3'd4;
		ivDivSel = 3'd0;
		ivCountLoad = 8'd0; /*La cuenta se carga con 0*/
		ivCompareValue = 8'd0; /*El valor de comparación será 0*/
		repeat(6) #200  iEventos = ~iEventos; /*Se simulan 3 señales externas para los flancos*/
		repeat (4) #200 iInputCaptureEstimulo = ~iInputCaptureEstimulo; /*Se simulan 2 señales externas para el estimulo del input capture*/
		repeat (2) #200 iInputCaptureACK = ~iInputCaptureACK; /*Se simula un ACK para el input capture*/
		repeat (2) #200 iOutputCompareACK = ~iOutputCompareACK; /*Se simula un ACK para el output compare*/
		repeat(6) #200  iEventos = ~iEventos; /*Se simulan 3 señales externas para los flancos*/
		repeat (4) #200 iInputCaptureEstimulo = ~iInputCaptureEstimulo; /*Se simulan 2 señales externas para el estimulo del input capture*/
		repeat (2) #200 iInputCaptureACK = ~iInputCaptureACK; /*Se simula un ACK para el input capture*/
		repeat (2) #200 iOutputCompareACK = ~iOutputCompareACK; /*Se simula un ACK para el output compare*/
		#500;
		
		$finish;

		// Wait 100 ns for global reset to finish
		#100;
        
		// Add stimulus here

	end
      
endmodule

