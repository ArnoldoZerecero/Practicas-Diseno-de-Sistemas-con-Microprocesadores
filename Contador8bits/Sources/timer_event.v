`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    19:45:40 10/08/2017 
// Design Name: 
// Module Name:    timer_event 
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
module timer_event(
	input iClk,
	input iReset,
	input iComparisonTrue,
	output oTimerOverflow
    );
	 
reg r_Q = 0; /*Un solo flip flop de salida*/
reg r_D = 0;

assign oTimerOverflow = r_Q;

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
	if (iComparisonTrue) /*Si se llegó al final de la comparación*/
	begin
		r_D = 1'b1; /*Activa la bandera de timer overflow*/
	end
	else
	begin
		r_D = r_Q; /*La bandera de salida mantendrá su valor hasta que llegue el reset por ACK*/
	end
end

endmodule
