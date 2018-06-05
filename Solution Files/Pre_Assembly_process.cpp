
#include "stdafx.h"
#include <iostream>
#include <string>
#include <vector>
#include "Pre_Assembly_process.h"
#include "Instruction_table.h"
#include "Record_operations.h"


void pre_assembly_process(std::string &record)
{
	bool output = !DONE;
	char state = S0;
	char error_flag = 0;
	int matched_instruction_index = -1;
	int args_in_record = 0;
	std::string label;
	std::vector<std::string> tokens;

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
			matched_instruction_index = verify_token(capitalize_string(tokens[0]));

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
			state = S4;
			break;

		case(S4):
			std::cout << record << error_message(error_flag) << std::endl;
			output = DONE;
			break;

		default:
			break;
		}
	}
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