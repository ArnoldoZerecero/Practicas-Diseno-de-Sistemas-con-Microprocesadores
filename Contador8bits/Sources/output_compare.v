`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    01:54:53 10/19/2017 
// Design Name: 
// Module Name:    output_compare 
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
module output_compare(
	input iClk,
	input iReset,
	input [7:0] ivCuenta,
	input [7:0] ivCompareValue,
	output oComparisonTrueFlag
    );
	 
reg r_Q; /*Un solo flip flop de salida*/
reg r_D;

assign oComparisonTrueFlag = r_Q;

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
	if(ivCuenta == ivCompareValue) /*Cuando la cuenta sea igual al valor de comparación*/
	begin
		r_D = 1'b1; /*Se setea la bandera de comparación*/
	end
	else
	begin
		r_D = r_Q; /*La bandera de salida mantendrá su valor hasta que llegue el reset por ACK. Previa a la comparación, estará en cero*/
	end
end

endmodule
