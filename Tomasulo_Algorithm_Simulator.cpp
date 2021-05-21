#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;
typedef unsigned long long int ull;
#define mp make_pair
// GCD inbuilt func: __gcd(a,b)
// LCM formula: (a*b)/__gcd(a,b)

/*
    Tomasulo Algorithm is a famous algorithm used for scheduling the instructions dynamically and using the Reservation Stations to execute the instructions 
    parallelly. The Motive of this algorithm is to parallelise the execution of instruction and reduce the total time of execution of the instructions.
    
    The GOAL of my project is to simulate the Tomasulo algorithm's behaviour on instructions. For this, the input must be basic Arithmetic operations which
    are ADD, SUB, MUL and DIV and operates on 2 registers and writes the output to another register. 
    Also, we can additionally give the DELAY constraints for these arithmetic operations and see the changes in the total time taken for the same algorithm to
    work on the same instructions. This project can be used to simulate the Tomasulo Algorithm for different delay constraints and will in turn help us in 
    speculating where we can optimise at the hardware level.
    
    The Algorithm is coded in C++. 
    Used 8 registers. 5 Reservation stations - 3 for ADD,SUB and 2 for MUL,DIV. Kept the code flexible enough to add more reservation stations.
    Coded register renaming initially to avoid WAW and WAR hazards assuming unused registers is abundant enough.
    
    DIVISION BY "ZERO" MUST BE AVOIDED or the PROGRAM will CRASH
*/

// ---------- Reservation Station ------------
struct Reservation_Station{
	bool busy;
	string opcode;
	ll operand1;
	ll operand2;
	ll destination_reg;
	ll down_counter;
};
//--------------------------------------------

// ----------- Register ----------------------
struct Register{
	ll val;
	bool busy;
};
//--------------------------------------------

// ----------- Instruction -------------------
struct Instruction{
	string opcode;
	ll dest_reg;
	ll operand_reg1;
	ll operand_reg2; 
};
//--------------------------------------------

// ------- Reservation Stations' Execution and Writeback ------------------------
void Reservation_Station_Execution(Reservation_Station &RS, vector<Register> &f, vector<Instruction> &exec_order){
	if(!RS.busy) return;
	if(f[RS.operand1].busy || f[RS.operand2].busy) return;
	RS.down_counter--;
	if(!RS.down_counter){
		if(RS.opcode=="ADD"){
			f[RS.destination_reg].val=f[RS.operand1].val+f[RS.operand2].val;
			f[RS.destination_reg].busy=false;
			RS.busy=false;
			exec_order.push_back({RS.opcode,RS.destination_reg,RS.operand1,RS.operand2});
		}
		else if(RS.opcode=="SUB"){
			f[RS.destination_reg].val=f[RS.operand1].val-f[RS.operand2].val;
			f[RS.destination_reg].busy=false;
			RS.busy=false;
			exec_order.push_back({RS.opcode,RS.destination_reg,RS.operand1,RS.operand2});
		}
		else if(RS.opcode=="MUL"){
			f[RS.destination_reg].val=f[RS.operand1].val*f[RS.operand2].val;
			f[RS.destination_reg].busy=false;
			RS.busy=false;
			exec_order.push_back({RS.opcode,RS.destination_reg,RS.operand1,RS.operand2});
		}
		else if(RS.opcode=="DIV"){
			f[RS.destination_reg].val=f[RS.operand1].val/f[RS.operand2].val;
			f[RS.destination_reg].busy=false;
			RS.busy=false;
			exec_order.push_back({RS.opcode,RS.destination_reg,RS.operand1,RS.operand2});
		}
	}
}
//------------------------------------------------------------------------------

// ------------ Initialisation of Reservation Stations with new Instruction ------------
void Instruction_Initialisation(Reservation_Station &RS, ll rs_type, ll dc_a, ll dc_b, vector<Register> &f, Instruction instr, ll &instr_p, bool &initialised){
	if(RS.busy) return;
	if(!rs_type && (instr.opcode=="ADD" || instr.opcode=="SUB")){
		if(instr.opcode=="ADD") RS.down_counter=dc_a;
		else RS.down_counter=dc_b;
		RS.opcode=instr.opcode;
		RS.busy=true;
		RS.operand1=instr.operand_reg1;
		RS.operand2=instr.operand_reg2;
		RS.destination_reg=instr.dest_reg;
		f[RS.destination_reg].busy=true;
		instr_p++;
		initialised=true;
	}
	else if(rs_type && (instr.opcode=="MUL" || instr.opcode=="DIV")){
		if(instr.opcode=="MUL") RS.down_counter=dc_a;
		else RS.down_counter=dc_b;
		RS.opcode=instr.opcode;
		RS.busy=true;
		RS.operand1=instr.operand_reg1;
		RS.operand2=instr.operand_reg2;
		RS.destination_reg=instr.dest_reg;
		f[RS.destination_reg].busy=true;
		instr_p++;
		initialised=true;
	}
}
//-----------------------------------------------------------------------------------

// ------------- The MAIN Function ------------------
int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	// Tomasulo Algorithm

	// --------- Input of all the Instructions ----------
	vector<Instruction> Raw_Instructions;
	ll instruction_num=0;
	cout << "Enter the Instructions:\n";
	while(1){
		string op;
		ll dest,op1,op2;
		cin >> op;
		if(op[0]=='$') break;
		cin >> dest >> op1 >> op2;
		Raw_Instructions.push_back({op,dest,op1,op2});
		instruction_num++;
	}
	//----------------------------------------------------

	// -------- Register Renaming using unused Registers and a Map ---------
	// -------- To Avoid WAW and WAR Hazards ---------
	ll reg_rename_map[instruction_num][8];
	for(ll i=0;i<8;i++){
		for(ll j=0;j<instruction_num;j++) reg_rename_map[j][i]=i;
	}
	ll pointer=8;
	for(ll i=1;i<instruction_num;i++){
		for(ll j=i;j<instruction_num;j++) reg_rename_map[j][Raw_Instructions[i].dest_reg]=pointer;
		pointer++;
	}
	for(ll i=1;i<instruction_num;i++){
		Raw_Instructions[i].dest_reg=reg_rename_map[i][Raw_Instructions[i].dest_reg];
		Raw_Instructions[i].operand_reg1=reg_rename_map[i-1][Raw_Instructions[i].operand_reg1];
		Raw_Instructions[i].operand_reg2=reg_rename_map[i-1][Raw_Instructions[i].operand_reg2];
	}

	cout << "Instructions with Renamed Registers:\n";
	for(ll i=0;i<instruction_num;i++){
	    cout << Raw_Instructions[i].opcode << " " << Raw_Instructions[i].dest_reg << " " << Raw_Instructions[i].operand_reg1 << " " << Raw_Instructions[i].operand_reg2;
	    cout << "\n";
	}
	cout << "\n";
	//--------------------------------------------------------------------

	// ------- Input of Regsiter Values ------------
	vector<Register> f;
	for(ll i=0;i<1000;i++) f.push_back({0,false});
	cout << "Enter the 8 Registers' values: ";
	for(ll i=0;i<8;i++) cin >> f[i].val;
	//----------------------------------------------

	// ------ Initialising Reservation Stations for the first time -------
	Reservation_Station ADD_1, ADD_2, ADD_3;
	Reservation_Station MUL_1, MUL_2;
	ADD_1.busy=false;
	ADD_2.busy=false;
	ADD_3.busy=false;
	MUL_1.busy=false;
	MUL_2.busy=false;
	//--------------------------------------------------------------------

	// --------- Input of Arithemtic Operation Execution Delays ----------
	ll add_downcounter,sub_downcounter,mul_downcounter,div_downcounter;
	cout << "Adder Delay: ";
	cin >> add_downcounter;
	cout << "Subtractor Delay: ";
	cin >> sub_downcounter;
	cout << "Multiplier Delay: ";
	cin >> mul_downcounter;
	cout << "Divider Delay: ";
	cin >> div_downcounter;
	cout << "\n\n";
	//--------------------------------------------------------------------

	ll time_counter=0, instruction_pointer=0;  // Traking total time and instruction number

	vector<Instruction> Instruction_Execution_order;

	do{
		//-------- Execution of Reservation Stations --------------
		Reservation_Station_Execution(ADD_1,f,Instruction_Execution_order);
		Reservation_Station_Execution(ADD_2,f,Instruction_Execution_order);
		Reservation_Station_Execution(ADD_3,f,Instruction_Execution_order);
		
		Reservation_Station_Execution(MUL_1,f,Instruction_Execution_order);
		Reservation_Station_Execution(MUL_2,f,Instruction_Execution_order);
		//---------------------------------------------------------

		//-------- Assigning an Instruction to an appropriate Reservation Station and Initialising ---------
		if(instruction_pointer<instruction_num){
			Instruction instruction_for_fetch=Raw_Instructions[instruction_pointer];

			bool initialised=false;

			Instruction_Initialisation(ADD_1,0,add_downcounter,sub_downcounter,f,instruction_for_fetch,instruction_pointer,initialised);
			if(!initialised) Instruction_Initialisation(ADD_2,0,add_downcounter,sub_downcounter,f,instruction_for_fetch,instruction_pointer,initialised);
			if(!initialised) Instruction_Initialisation(ADD_3,0,add_downcounter,sub_downcounter,f,instruction_for_fetch,instruction_pointer,initialised);

			if(!initialised) Instruction_Initialisation(MUL_1,1,mul_downcounter,div_downcounter,f,instruction_for_fetch,instruction_pointer,initialised);
			if(!initialised) Instruction_Initialisation(MUL_2,1,mul_downcounter,div_downcounter,f,instruction_for_fetch,instruction_pointer,initialised);
		}
		//---------------------------------------------------------------------------------------------------

		time_counter++; // Tracking Total time

	} while(ADD_1.busy || ADD_2.busy || ADD_3.busy || MUL_1.busy || MUL_2.busy); // Condition for the loop to go on

	// --------- Total Time of Execution of All Instructions ---------
	cout << "Total time: " << time_counter << " units" << "\n\n";
	//----------------------------------------------------------------

	// --------- Clock units per Instruction ---------
	cout << "Clock units per Instruction: " << (double)time_counter/(double)instruction_num << setprecision(4) << fixed << "\n\n";
	//----------------------------------------------------------------
	
	// --------- The Register values at the end of all instructions -----------
	cout << "Register values: ";
	for(ll i=0;i<8;i++) cout << f[reg_rename_map[instruction_num-1][i]].val << " ";
	cout << "\n\n";
	//-------------------------------------------------------------------------

	// --------- The Executed Order of Instructions --------------
	cout << "Executed Order of Instructions:\n";
	for(ll i=0;i<Instruction_Execution_order.size();i++) cout << Instruction_Execution_order[i].opcode << " " << Instruction_Execution_order[i].dest_reg << " " << Instruction_Execution_order[i].operand_reg1 << " " << Instruction_Execution_order[i].operand_reg2 << "\n";
	//------------------------------------------------------------

	return 0;
}
// -------------------------------------------------
