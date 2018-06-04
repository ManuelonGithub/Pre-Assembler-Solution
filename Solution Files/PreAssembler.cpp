// PreAssembler.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "Instruction_table.h"
#include "Record_operations.h"
#define DONE 1
enum STATES { S0, S1, S2, S3, S4};

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

	bool output;
	char state;
	char error_flag;
	int matched_instruction_index;
	int args_in_record;
	std::string record;
	std::string label;
	std::vector<std::string> tokens;

	while (std::getline(asm_file_in, record)) {

		output = !DONE;
		state = S0;

		while (output != DONE) {
			switch (state)
			{
			case(S0):
				remove_comment(record);

				if (record.empty()) {
					state = S4;
				}

				else {
					tokens = record_tokenizer(record);
					state = S1;
				}
				break;

			case(S1):
				matched_instruction_index = verify_token(tokens[0]);

				if (matched_instruction_index == NOT_IN_TABLE) {
					state = S2;
				}

				else {
					state = S3;
					label = "";
					args_in_record = tokens.size() - 1;
				}
				break;

			case(S2):
				matched_instruction_index = verify_token(tokens[1]);

				if (matched_instruction_index == NOT_IN_TABLE) {
					state = S4;
				}

				else {
					state = S3;
					label = tokens[0];
					args_in_record = tokens.size() - 2;
				}

			case(S3):
				error_flag = error_check(matched_instruction_index, label, args_in_record);
				if (error_flag == 0) {
					record = record_emulation(matched_instruction_index, tokens[(tokens.size() - 1)], label);
				}

				break;

			case(S4):
				std::cout << "this is state 4, it is the final state" << std::endl;
				state = S0;
				output = DONE;
				break;

			default:
				break;
			}

			std::cout << "Current output state is " << output << std::endl;
		}
	}


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