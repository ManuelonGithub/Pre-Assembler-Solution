// PreAssembler.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <fstream>
#include "Pre_Assembly_process.h"

std::string out_file_name(std::string filename);


int main(int argc, char * argv[])
{
	std::ifstream asm_file_in;
	std::ofstream asm_file_out;

	//if (argc != 2) {
	//	std::cout << "Invalid number of arguments." << std::endl;
	//	getchar();
	//	return 0;
	//}

	//asm_file_in.open(argv[1]);

	//if (!asm_file_in) {
	//	std::cout << argv[1] << "Is not a valid input file" << std::endl;
	//	getchar();
	//	return 1;
	//}

	//asm_file_out.open(out_file_name(argv[1]));

	std::string record = "l@bel ADC R3";

	//while (std::getline(asm_file_in, record)) {

	//}
	std::cout << record << std::endl;
	pre_assembly_process(record);


	asm_file_in.close();
	asm_file_out.close();

	getchar();

    return 0;
}