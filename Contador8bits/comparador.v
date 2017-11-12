`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    01:56:54 10/05/2017 
// Design Name: 
// Module Name:    comparador 
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
module comparador(
	input iClk,
	input iReset,
	input [7:0] ivCuenta,
	input [7:0] ivCompareValue,
	output oCompareFlag
    );
	 
reg r_Q; /*Un solo flip flop de salida*/
reg r_D;

assign oCompareFlag = r_Q;

always @ (posedge iClk)
begin
	if (iReset) /*Si se hace un reset del sistema*/
	begin
		r_Q<=0; /*Todos los estados vuelven a cero*/
	end
	else
	begin
		r_Q<=r_D; /*Estado anterior igual a estado actual. El sistema se actualiza*/
	end
end

always  @*
begin
	if (ivCuenta == ivCompareValue) /*Si la cuenta llegó a su valor de comparación*/
	begin
		r_D = 1; /*La bandera de finalizado se activa*/
	end
	else
	begin
		r_D = 0;
	end
end
endmodule
