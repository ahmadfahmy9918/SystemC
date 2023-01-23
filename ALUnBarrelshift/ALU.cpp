// ALU CODE
//////////////////////////////////
#include "ALU.h"

void ALU :: ALU_method(){
	//sc_int<8> A, B;
	//sc_in<int> A, B;
	//sc_in_clk clock;
	//sc_in<bool> OP;
	//int i;

	//sc_out<int> alu_out;

	if(OP.read() == 1){ //addition
		alu_out.write(A.read()+B.read());		
	}
	else{ //subtraction
		alu_out.write(A.read()-B.read());
	}
}
