# Tomasulo-Algorithm-Simulator
This project is simulation of Dynamic Scheduling using Tomasulo Algorithm for Arithmetic Operations and will take contraint inputs from the User to simulate different scenarios for the same algorithm and instructions.

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
