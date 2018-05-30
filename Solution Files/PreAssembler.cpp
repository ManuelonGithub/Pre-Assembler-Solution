// PreAssembler.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "Instruction_table.h"
#include "Record_operations.h"

int main(int argc, char * argv[])
{
	if (argc != 2) {
		std::cout << "Invalid number of arguments." << std::endl;
		getchar();
		return 0;
	}

	std::ifstream asm_file_in;
	asm_file_in.open(argv[1]);

	if (!asm_file_in) {
		std::cout << "Error opening " << argv[1] << std::endl;
		getchar();
		return 1;
	}

	std::string line;

	while (getline(asm_file_in, line))
	{
		std::vector<std::string> tokens = record_tokenizer(line);

		for (char i = 0; i < tokens.size(); i++) {
			std::cout << tokens[i] << std::endl;
		}

		std::cout << std::endl;
	}

	//print_whole_table("sup");

	getchar();

    return 0;
}

