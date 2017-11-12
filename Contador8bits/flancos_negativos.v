`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    01:55:59 10/05/2017 
// Design Name: 
// Module Name:    flancos_negativos 
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
module flancos_negativos(
	input iClk,
	input iReset, 
	input iSenal,
	output oFlanco 
    );
	 
	reg r_D; /*2 flip flops de comparación y un flip flop para la salida*/
	reg r_Q;
	reg r_D2;
	reg r_Q2;
	reg r_D3;
	reg r_Q3;
	
	assign oFlanco = r_Q;
	
always @ (posedge iClk) 
begin
	if (iReset) /*Si se hace un reset del sistema*/
	begin
		r_Q<=0;  /*Todos los estados vuelven a cero*/
		r_Q2<=0;
		r_Q3<=0;
	end
	else
	begin
		r_Q<=r_D; /*Estado anterior igual a estado actual. El sistema se actualiza*/
		r_Q2<=r_D2;
		r_Q3<=r_D3;
	end
end

always @*
begin
	r_D3 = iSenal; 
	r_D2 = r_Q3;
	r_D = r_Q2 & ~r_Q3; /*Se detectan transiciones de 1 a 0*/
end

endmodule 
