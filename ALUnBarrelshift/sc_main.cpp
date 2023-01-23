// COE838 - Lab1 SystemC Intro
//////////////////////////////////
//Testbench driver for ALU

#include <systemc.h>
#include "ALU.h"
#include "barrelshift.h"


void make_ALU(){
	ALU *a1; 	 

sc_trace_file *tf;                 			    // Create VCD file for tracing

	 sc_signal<bool> OP;      						//Declare signals
	 sc_signal<sc_int<8> > alu_out, A, /*B,*/ data_out_and_B, data_in;	
	 sc_signal<bool> left_in, right_in;     		    //Declare signals
	 sc_signal<bool> en, left_right;

	 sc_clock clock("clk",20,SC_NS,0.5);   			//Create a clock signal
	
	 barrel_shift barrel("barrelshift");   	
	 barrel.l_in(left_in);                          // Connect/map the ports to testbench signals
   	 barrel.r_in(right_in);
   	 barrel.clk(clock);
	 barrel.enable(en);
     barrel.left_right(left_right);
	 barrel.dout(data_out_and_B);
	 barrel.din(data_in);

	 a1 = new ALU("ALU");                                //Create testbench Device Under Test (DUT)
	(*a1) (clock, OP, A, data_out_and_B, alu_out);
	
	//B= data_out;

	/*
   	 alu.A(A);                                      
   	 //alu.B(B);
	 //alu.B(barrel.dout);
   	 alu.clock(clock);
	 alu.alu_out(alu_out);
	 alu.OP(OP);

	 //barrel.dout(B);
	
	 //barrel.dout(alu.B);
	 alu.B(data_out);
*/

	//sc_bind(barrel.dout, alu.B);

/////////////////////////ADD and initialize the vars from barrelshift

       // Create wave file and trace the signals executing
	tf = sc_create_vcd_trace_file("trace_file");
        tf->set_time_unit(1, SC_NS);
	sc_trace(tf, clock, "clock");
	sc_trace(tf, A, "A");
	//sc_trace(tf, B, "B");
	sc_trace(tf, OP, "OP");
	sc_trace(tf, alu_out, "alu_out");

	sc_trace(tf, en, "enable");
	sc_trace(tf, left_in, "left_data");
	sc_trace(tf, right_in, "right_data");
	sc_trace(tf, left_right, "left_right_signal");
	sc_trace(tf, data_out_and_B, "data_out/B");
	sc_trace(tf, data_in, "data_in");
	
	cout << "\nExecuting ALU example... check .vcd produced"<<endl;

	//start the testbench
	en.write(0); //initialize
	left_in.write(0); right_in.write(0);
	left_right.write(0); 
    OP.write(0); //initialize
	A.write(0);
	//B.write(0);
	sc_start(20, SC_NS);

	en.write(0); //enable off
	left_in.write(0); right_in.write(0);
	left_right.write(0); 
	OP.write(1); //ADDITION
	A.write(10);
	data_in.write(7);
	sc_start(20, SC_NS);

	
	OP.write(0); //SUBTRACTION
	A.write(20);
	//B.write(10);
	sc_start(20, SC_NS);


	en.write(1); //enable on
	left_in.write(1); right_in.write(0);
	left_right.write(0); 
	OP.write(1); //ADDITION
	//alu.B(barrel.dout);
	A.write(10);
	sc_start(20, SC_NS);

	
	OP.write(0); //SUBTRACTION
	left_in.write(1); right_in.write(0);
	left_right.write(0); 
	A.write(20);
	//B.write(barrel.dout);
	sc_start(20, SC_NS);




	left_in.write(0); right_in.write(1);
	left_right.write(1); 
	OP.write(1); //ADDITION
	A.write(10);
	sc_start(20, SC_NS);

	
	OP.write(0); //SUBTRACTION
	left_in.write(1); right_in.write(1);
	left_right.write(1); 
	A.write(20);
	sc_start(20, SC_NS);
	

   	sc_close_vcd_trace_file(tf);
}

int sc_main(int argc, char* argv[]){

	make_ALU(); //example of function call in main cpu


	return 0;                         
}
