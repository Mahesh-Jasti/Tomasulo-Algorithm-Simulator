# Tomasulo-Algorithm-Simulator
This project is simulation of Dynamic Scheduling using Tomasulo Algorithm for Arithmetic Operations and will take contraint inputs from the User to simulate different scenarios for the same algorithm and instructions.
Tomasulo Algorithm is a famous algorithm used for scheduling the instructions dynamically and using the Reservation Stations to execute the instructions 
parallelly. The Motive of this algorithm is to parallelise the execution of instruction and reduce the total time of execution of the instructions.
    
The GOAL of my project is to simulate the Tomasulo algorithm's behaviour on instructions. For this, the input must be basic Arithmetic operations which
are ADD, SUB, MUL and DIV and operates on 2 registers and writes the output to another register. 
Also, we can additionally give the DELAY constraints for these arithmetic operations and see the changes in the total time taken for the same algorithm to
work on the same instructions. This project can be used to simulate the Tomasulo Algorithm for different delay constraints and will in turn help us in 
speculating where we can optimise at the hardware level.

Input from the User --
1) Instructions with an opcode and 3 operand registers.
2) Values of the Registers.
3) Delay constraints for Adder, Subtractor, Multiplier and Divider.

Output to the User --
1) Total Running time of the Algorithm with the given constraints and instructions.
2) Final values of the Registers after all the Instructions are executed.
3) The Order of execution of these Instructions as it is expected of this Algorithm to perform Out of Order Execution of the Instructions to use Parallelism.

Basic Design Details --
1) 8 Registers are used which are the Operand Registers for the instructions addressed from 0 through 7.
2) 5 Reservation Stations have been used, 3 of which are used for ADD-SUB instructions and 2 of which are used for MUL-DIV instructions.
3) Register Renaming is performed in the beginning to remove WAW and WAR hazards using unused Registers which are assumed to be sufficiently abundant.
