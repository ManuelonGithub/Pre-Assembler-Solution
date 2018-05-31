// PreAssembler.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "Instruction_table.h"
#include "Record_operations.h"

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

	int index = token_verifier("TST.B", 0, size_of_table());

	std::cout << index << std::endl;

	asm_file_in.close();
	asm_file_out.close();

	getchar();

    return 0;
}

std::string out_file_name(std::string filename)
{
	char dot_pos = filename.find_last_of('.');

	if (dot_pos != std::string::npos) {
		filename.insert((dot_pos), "_out");
	}

	else
		filename += "_out";

	return filename;
}