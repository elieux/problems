#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define WORD_SIZE 1000
typedef unsigned int Word;

#define REGISTERS 10

#define BUF_LEN 8

typedef enum { I_JNZ, I_HALT, I_SET, I_ADD, I_MUL, I_SETREG, I_ADDREG, I_MULREG, I_LOAD, I_STOR } Instruction;

int main(int argc, char *argv[]) {
	Word ram[WORD_SIZE];
	Word registers[REGISTERS];
	char line[BUF_LEN];
	unsigned int i, j, cases, c, ip;
	unsigned int instr[3];
	
	fgets(line, BUF_LEN, stdin);
	sscanf(line, "%u", &cases);
	fgets(line, BUF_LEN, stdin);
	for (i = 0; i < cases; i++)
	{
		memset(ram, 0, WORD_SIZE * sizeof(Word));
		memset(registers, 0, REGISTERS * sizeof(Word));
		j = 0;
		while (NULL != fgets(line, BUF_LEN, stdin) && '\n' != line[0])
		{
			sscanf(line, "%u", &ram[j]);
			j++;
		}
		ip = 0;
		c = 0;
		while (ip < WORD_SIZE)
		{
			c++;
			instr[0] = ram[ip] / 100;
			instr[1] = (ram[ip] % 100) / 10;
			instr[2] = ram[ip] % 10;
			ip++;
			switch (instr[0]) {
				case I_HALT:
					ip = WORD_SIZE;
					break;
				case I_SET:
					registers[instr[1]] = instr[2];
					break;
				case I_ADD:
					registers[instr[1]] += instr[2];
					registers[instr[1]] %= WORD_SIZE;
					break;
				case I_MUL:
					registers[instr[1]] *= instr[2];
					registers[instr[1]] %= WORD_SIZE;
					break;
				case I_SETREG:
					registers[instr[1]] = registers[instr[2]];
					break;
				case I_ADDREG:
					registers[instr[1]] += registers[instr[2]];
					registers[instr[1]] %= WORD_SIZE;
					break;
				case I_MULREG:
					registers[instr[1]] *= registers[instr[2]];
					registers[instr[1]] %= WORD_SIZE;
					break;
				case I_LOAD:
					registers[instr[1]] = ram[registers[instr[2]]];
					break;
				case I_STOR:
					ram[registers[instr[2]]] = registers[instr[1]];
					break;
				case I_JNZ:
					if (0 != registers[instr[2]])
						ip = registers[instr[1]];
					break;
			}
		}
		if (0 < i)
			printf("\n");
		printf("%d\n", c);
	}
	
	return 0;
}
