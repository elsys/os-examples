#include <stdio.h>

int main() {
	// RAM
	int memory[100];

	// "hardware support" for bootstrapping
	memory[0] = 1;
	// "hardware support" for subroutines (see JMP isntruction)
	memory[99] = 800;

	// CPU registers
	int pc = 0;
	int accumulator = 0;
	int instruction = 0;

	// CPU loop
	while(1) {
		// fetch instruction
		instruction = memory[pc];

		// increment program counter
		++pc;

		// decode the instruction
		int opcode = instruction / 100; // Xxx (the first digit of the instruction)
		int address = instruction % 100; // xXX (the last two digits of the instruction)
		//  ^~~~ NOTE: when implementing the SFT instruction the address part is treated differently!


		// execute the instruction
		switch (opcode) {
				int card = 0;
			case 0: // INP (read a card and store it at address)
				scanf("%d", &card); // read the card
				memory[address] = card; // store it

				// actually this instruction can be executed without a temporary variable
				break;
			case 5: // OUT (write a cell from memory to a card)
				printf("%d\n", memory[address]);
				break;
			// TODO: Implement the JMP instruction first, so that you can bootstrap the provided test program
			//case 8:
			//	break;
			case 9: // HRS (Halt)
				return 0;
				break;
			default:
				printf("opcode '%d' not yet implemented! Panicking!\n", opcode);
				return 1;
		}
	}

	return 0;
}
