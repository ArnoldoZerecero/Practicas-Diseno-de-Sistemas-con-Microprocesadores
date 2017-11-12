`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    01:15:24 10/19/2017 
// Design Name: 
// Module Name:    input_capture 
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
module input_capture(
	input iClk,
	input iReset,
	input iEstimulo,
	input [7:0] ivCuenta,
	output [7:0] ovCaptura,
	output oCapturaFlag
    );
	 
reg r_Q ; /*Dos flip flops de salida*/
reg r_D;
reg [7:0] rv_Q = 0;
reg [7:0] rv_D = 0;

assign oCapturaFlag = r_Q;
assign ovCaptura = rv_Q;

always @ (posedge iClk)
begin
	if (iReset) /*Si se hace un reset del sistema*/
	begin
	  r_Q<=0; /*Todos los estados vuelven a cero*/
	  rv_Q<=0;
	end
	else
	begin
	  r_Q<=r_D; /*Estado anterior igual a estado actual. El sistema se actualiza*/
	  rv_Q<=rv_D;
	end
end

always  @*
begin
	if(iEstimulo && !r_Q) /*Cuando llegue el estímulo seleccionado. Si bandera de captura no ha sido cleareada por el ACK de software al momento que llega otro estimulo, el valor de captura no cambiará*/
	begin
		rv_D = ivCuenta; /*Se captura el valor actual de la cuenta*/
		r_D = 1'b1; /*Se setea la bandera de captura*/
	end
	else
	begin
		rv_D = rv_Q; /*Los registros de salida mantendrán su valor hasta que llegue el reset del ACK. Antes de la captura, se mantendrán en cero*/
		r_D = r_Q; 
	end
end

endmodule
