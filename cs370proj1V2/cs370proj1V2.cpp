// cs370proj1V2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
using namespace std;

struct registerRW
{
	int read;
	int write;
	registerRW() :
		read(0),
		write(0) {};

};
string printReg(registerRW);
void processCommand(unsigned int currpcLine, unsigned int currInstrucLine, unsigned int nextInstrucLine, unsigned int nextpcLine);
//output variables
int insts = 0, r_type = 0, i_type = 0, j_type = 0, fwd_taken = 0, bkw_taken = 0, not_taken = 0, loads = 0, stores = 0;
registerRW registers[32];

int main()
{

	//needed variables for I/O
	ofstream outFile;
	FILE * inputFile;
	//ifstream inputFile1;
	string stringLine;
	unsigned int currpcLine, currInstrucLine, nextInstrucLine, nextpcLine;
	int instructionIndex = 0;
	//inputFile1.open("trace.txt");


	fopen_s(&inputFile, "trace.txt", "r");
	outFile.open("statistics.txt");
	//outFile << registers[0].read;
	//outFile << registers[0].write;

	/*
	while (inputFile1 >> pcLine >> instrucLine) {
	outFile << pcLine << " " << instrucLine;
	}
	inputFile1.close();
	*/
	if (inputFile != NULL)
	{
		
		fscanf_s(inputFile, "%x %x", &currpcLine, &currInstrucLine) == 2;
		while (fscanf_s(inputFile, "%x %x", &nextpcLine, &nextInstrucLine) == 2)
		{
			processCommand(currpcLine, currInstrucLine, nextInstrucLine, nextpcLine);
			//outFile << pcLine << " " << instrucLine << endl;
			currInstrucLine = nextInstrucLine;
			currpcLine = nextpcLine;
		}
		//process one last command...
		processCommand(currpcLine, currInstrucLine, NULL, NULL);

		fclose(inputFile);
	}
	else {
		cout << "Unable to open file";
		return -1;
	}



	outFile << "insts: " << insts << endl;
	outFile << "r-type: " << r_type << endl;
	outFile << "i-type: " << i_type << endl;
	outFile << "j-type: " << j_type << endl;
	outFile << "fwd-taken: " << fwd_taken << endl;
	outFile << "bkw-taken: " << bkw_taken << endl;
	outFile << "not-taken: " << not_taken << endl;
	outFile << "loads: " << loads << endl;
	outFile << "stores: " << stores << endl;
	for (size_t i = 0; i < 32; i++)
	{
		outFile << "reg-" << i << ": " << printReg(registers[i]) << "\n";
	}
	outFile.close();
	return 0;
}

string printReg(registerRW currReg) {
	return std::to_string(currReg.read) + " " + std::to_string(currReg.write);
}

void processCommand(unsigned int currpcLine, unsigned int currInstrucLine, unsigned int nextInstrucLine, unsigned int nextpcLine) {
	insts++;
	unsigned int opcode = currInstrucLine >> 26;
	unsigned int funcCode = (currInstrucLine & 0x0000003f);
	if (opcode == 0x00) {
		//only one special case for R opcodes that is jr
		r_type++;
		if (funcCode == 0x08) {
			unsigned int rsReg = (currInstrucLine & 0x03e00000) >> 21;
			registers[rsReg].read++;

		}
		else if (funcCode == 0x00|| funcCode == 0x02) {
			unsigned int rtReg = (currInstrucLine & 0x001f0000) >> 16;
			unsigned int rdReg = (currInstrucLine & 0x0000f800) >> 11;
			registers[rtReg].read++;
			registers[rdReg].write++;
		}
		else
		{
			unsigned int rsReg = (currInstrucLine & 0x03e00000) >> 21;
			unsigned int rtReg = (currInstrucLine & 0x001f0000) >> 16;
			unsigned int rdReg = (currInstrucLine & 0x0000f800) >> 11;
			registers[rsReg].read++;
			registers[rtReg].read++;
			//can never write to the $zero register... have the check there for that
			registers[rdReg].write++;
		}
	}
	//J type can be either opcode. There are only 2 J types
	else if (opcode == 0x2 || opcode == 0x3) {
		j_type++;
		if (currpcLine+4 == nextpcLine) {
			not_taken++;
		}
		else if(nextpcLine > currpcLine){
			fwd_taken++;
		}
		else {
			bkw_taken++;
		}
	}
	//stores opcode...
	else if (opcode == 0x2b || opcode == 0x29 || opcode == 0x38 || opcode == 0x28) {
		i_type++;
		stores++;
		unsigned int rsReg = (currInstrucLine & 0x03e00000) >> 21;
		unsigned int rtReg = (currInstrucLine & 0x001f0000) >> 16;
		//double check this... i think save word accesses both of the register values...
		registers[rsReg].read++;
		registers[rtReg].read++;
	}
	//slti opcodes and or immediate (ori)
	else if (opcode == 0xa || opcode == 0xb || opcode == 0xd) {
		i_type++;
		unsigned int rsReg = (currInstrucLine & 0x03e00000) >> 21;
		unsigned int rtReg = (currInstrucLine & 0x001f0000) >> 16;
		registers[rsReg].read++;
		registers[rtReg].write++;
	}
	//load words opcodes minus lui
	else if (opcode == 0x23 || opcode == 0x30 || opcode == 0x25 || opcode == 0x24) {
		i_type++;
		loads++;
		unsigned int rsReg = (currInstrucLine & 0x03e00000) >> 21;
		unsigned int rtReg = (currInstrucLine & 0x001f0000) >> 16;
		registers[rsReg].read++;
		registers[rtReg].write++;
	}
	//special case of lui
	else if (opcode == 0xf) {
		i_type++;
		loads++;
		unsigned int rtReg = (currInstrucLine & 0x001f0000) >> 16;
		registers[rtReg].write++;
	}
	//branchesss
	//beq
	else if (opcode == 0x4) {
		i_type++;
		if (currpcLine + 4 == nextpcLine) not_taken++;
		else if (nextpcLine < currpcLine) bkw_taken++;
		else fwd_taken++; 
		unsigned int rsReg = (currInstrucLine & 0x03e00000) >> 21;
		unsigned int rtReg = (currInstrucLine & 0x001f0000) >> 16;
		registers[rsReg].read++;
		registers[rtReg].read++;
	}
	//bne
	else if (opcode == 0x5) {
		i_type++;
		if (currpcLine + 4 == nextpcLine) not_taken++;// UGHGHGHGHG why is this if conditioning failing? The currpcLine is some random number when is should be close to nextpcline... 
		//this is where the error is occuring because of something before this possibly with getting the input of the file? Im not obtaining the correct number for the pc line????
		else if (nextpcLine < currpcLine) bkw_taken++;
		else fwd_taken++;
		unsigned int rsReg = (currInstrucLine & 0x03e00000) >> 21;
		unsigned int rtReg = (currInstrucLine & 0x001f0000) >> 16;
		registers[rsReg].read++;
		registers[rtReg].read++;
	}
	//add immediates
	else if (opcode == 0x8 || opcode == 0x9 || opcode == 0xc) {
		i_type++;
		unsigned int rsReg = (currInstrucLine & 0x03e00000) >> 21;
		unsigned int rtReg = (currInstrucLine & 0x001f0000) >> 16;
		registers[rsReg].read++;
		registers[rtReg].write++;
	}

	

}
