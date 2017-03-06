// cs370proj1V2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
using namespace std;

struct registerRW
{
	int read;
	int write;
	registerRW() {
		read = 0;
		write = 0;
	}
};
string printReg(registerRW);


int main()
{
	//output variables
	int insts = 0, r_type = 0, i_type = 0, j_type = 0, fwd_taken = 0, bkw_taken = 0, not_taken = 0, loads = 0, stores = 0;
	//is this how you define a new array? c++ is odd...
	registerRW registers[31];
	/*for (size_t i = 0; i < 31; i++)
	{
		//i am unsure if the use of tmp is correct here? ask prof on tuesday...
		registerRW * tmp = new registerRW();
		registers[i] = tmp;
	}*/
	//otherwise do it by hand... it makes me cringe
	registerRW * reg1 = new registerRW();
	registerRW * reg2 = new registerRW();
	registerRW * reg3 = new registerRW();
	registerRW * reg4 = new registerRW();
	registerRW * reg5 = new registerRW();
	registerRW * reg6 = new registerRW();
	registerRW * reg7 = new registerRW();
	registerRW * reg8 = new registerRW();
	registerRW * reg9 = new registerRW();
	registerRW * reg10 = new registerRW();
	registerRW * reg11 = new registerRW();
	registerRW * reg12 = new registerRW();
	registerRW * reg13 = new registerRW();
	registerRW * reg14 = new registerRW();
	registerRW * reg15 = new registerRW();
	registerRW * reg16 = new registerRW();
	registerRW * reg17 = new registerRW();
	registerRW * reg18 = new registerRW();
	registerRW * reg19 = new registerRW();
	registerRW * reg20 = new registerRW();
	registerRW * reg21 = new registerRW();
	registerRW * reg22 = new registerRW();
	registerRW * reg23 = new registerRW();
	registerRW * reg24 = new registerRW();
	registerRW * reg25 = new registerRW();
	registerRW * reg26 = new registerRW();
	registerRW * reg27 = new registerRW();
	registerRW * reg28 = new registerRW();
	registerRW * reg29 = new registerRW();
	registerRW * reg30 = new registerRW();
	registerRW * reg31 = new registerRW();

	
	//needed variables for I/O
	ofstream outFile;
	ifstream inputFile;
	string stringLine;
	unsigned pcLine, instrucLine;
	int instructionIndex = 0;

	inputFile.open("trace.txt");
	outFile.open("statistics.txt");
	if (inputFile.is_open())
	{
		while (inputFile >> hex >> pcLine >> hex >> instrucLine)
		{
			//do all computations and incrementing of variables here
			outFile << pcLine << " " << instrucLine;
		}
		inputFile.close();
	}
	else {
		cout << "Unable to open file";
		return -1;
	}



	
	outFile << "insts:";
	outFile << "r-type:";
	outFile << "i-type:";
	outFile << "j-type:";
	outFile << "fwd-taken:";
	outFile << "bkw-taken:";
	outFile << "not-taken:";
	outFile << "loads:";
	outFile << "stores:";
	for (size_t i = 0; i < 31; i++)
	{
		//outFile << "reg-" << i << ":" << printReg();
	}
	outFile.close();
    return 0;
}

string printReg(registerRW currReg) {
	return std::to_string(currReg.read) +" "+ std::to_string(currReg.write);
}

