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


int main()
{
	//output variables
	int insts = 0, r_type = 0, i_type = 0, j_type = 0, fwd_taken = 0, bkw_taken = 0, not_taken = 0, loads = 0, stores = 0;
	//is this how you define a new array? also from what i understand since i have my constructor are there already
	//initilized values in all of the slotted array spots?
	registerRW registers[31];
	
	//needed variables for I/O
	ofstream outFile;
	FILE * inputFile;
	//ifstream inputFile1;
	string stringLine;
	unsigned int pcLine, instrucLine;
	int instructionIndex = 0;
	//inputFile1.open("trace.txt");
	

	fopen_s(&inputFile,"trace.txt", "r");
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
		while (fscanf_s(inputFile, "%x %x", &pcLine, &instrucLine) == 2)
		{
			insts++;
			
			switch ((instrucLine >> 26))
			{
			case 0x00: r_type++;

			default:
				break;
			}
			//do all computations and incrementing of variables here
			outFile << pcLine << " " << instrucLine << endl;
			


		}
		//inputFile.close();
	}
	else {
		cout << "Unable to open file";
		return -1;
	}
	

	
	outFile << "insts: " << insts << endl;
	outFile << "r-type: " << r_type << endl;
	outFile << "i-type:\n";
	outFile << "j-type:\n";
	outFile << "fwd-taken:\n";
	outFile << "bkw-taken:\n";
	outFile << "not-taken:\n";
	outFile << "loads:\n";
	outFile << "stores:\n";
	for (size_t i = 0; i < 31; i++)
	{
		//outFile << "reg-" << i << ":" << printReg() << "\n";
	}
	outFile.close();
    return 0;
}

string printReg(registerRW currReg) {
	return std::to_string(currReg.read) +" "+ std::to_string(currReg.write);
}

