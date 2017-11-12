`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    01:56:35 10/05/2017 
// Design Name: 
// Module Name:    divisor 
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
module divisor(
	input iClk,
	input iReset,
	output oClkDiv2,
	output oClkDiv4,
	output oClkDiv8,
	output oClkDiv16
    );
	 
/*4 flip flops para las 4 salidas*/
reg rDiv2_Q; /*Clk/2*/
reg rDiv2_D;

reg rDiv4_D; /*Clk/4*/
reg rDiv4_Q;

reg rDiv8_D; /*Clk/8*/
reg rDiv8_Q;

reg rDiv16_D; /*Clk/15*/
reg rDiv16_Q;

reg [3:0] rvCont_Q = 0; /*Un flip flop para el contador de división*/
reg [3:0] rvCont_D = 0;

assign oClkDiv2 = rDiv2_Q;
assign oClkDiv4 = rDiv4_Q;
assign oClkDiv8 = rDiv8_Q;
assign oClkDiv16 = rDiv16_Q;


always @ (posedge iClk)
begin
	if (iReset) /*Si se hace un reset del sistema*/
	begin
		rDiv2_Q<=0; /*Todos los estados vuelven a cero*/
		rDiv4_Q<=0;
		rDiv8_Q<=0;
		rDiv16_Q<=0;
		rvCont_Q<=0;
	end
	else
	begin
		rDiv2_Q<=rDiv2_D; /*Estado anterior igual a estado actual. El sistema se actualiza*/
		rDiv4_Q<=rDiv4_D;
		rDiv8_Q<=rDiv8_D;
		rDiv16_Q<=rDiv16_D;
		rvCont_Q<=rvCont_D;
	end
end

always @*
begin
	if (rvCont_Q == 4'd15) /*Cuando sea igual a 15*/
	begin
		rDiv16_D = 1; /*Se manda un uno a todas las salidas*/
		rDiv8_D = 1; 
		rDiv4_D = 1; 
		rDiv2_D = 1; 
		rvCont_D = 0; /*Se reinicia el contador*/
	end
	else if (rvCont_Q == 4'd7) /*Cuando sea igual a 7*/
	begin
		rDiv16_D = 0; /*Se manda un uno a todas las salidas iguales o menores a 8*/
		rDiv8_D = 1; 
		rDiv4_D = 1; 
		rDiv2_D = 1; 
		rvCont_D = rvCont_Q + 4'd1; /*Se incrementa la cuenta*/
	end
	else if (rvCont_Q == 4'd3) /*Cuando sea igual a 3*/
	begin
		rDiv16_D = 0; /*Se manda un uno a todas las salidas iguales o menores a 4*/
		rDiv8_D = 0; 
		rDiv4_D = 1; 
		rDiv2_D = 1; 		
		rvCont_D = rvCont_Q + 4'd1; /*Se incrementa la cuenta*/
	end
	else if (rvCont_Q == 4'd1) /*Cuando sea igual a 1*/
	begin
		rDiv16_D = 0; /*Se manda un uno a la salida del divisor/2*/
		rDiv8_D = 0; 
		rDiv4_D = 0; 
		rDiv2_D = 1; 
		rvCont_D = rvCont_Q + 4'd1; /*Se incrementa la cuenta*/
	end
	else
	begin
		rDiv16_D = 0; /*No se manda ningun uno*/
		rDiv8_D = 0; 
		rDiv4_D = 0; 
		rDiv2_D = 0; 
		rvCont_D = rvCont_Q + 4'd1; /*Se incrementa la cuenta*/
	end
end

endmodule
