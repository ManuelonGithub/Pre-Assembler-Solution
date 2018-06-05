
#include "stdafx.h"
#include <iostream>
#include <string>
#include <vector>
#include "Pre_Assembly_process.h"
#include "Instruction_table.h"
#include "Record_operations.h"


void pre_assembly_process(std::string &record, char &error_code)
{
	bool output = !DONE;
	char state = S0;
	int matched_instruction_index = -1;
	int args_in_record = 0;
	std::string label;
	std::vector<std::string> tokens;

	while (output != DONE) {
		switch (state)
		{
		case(S0):
			remove_comment(record);

			if (record.empty() || is_whitespace(record)) {
				state = S4;
			}

			else {
				record_tokenizer(record, tokens);
				state = S1;
			}
			break;

		case(S1):
			matched_instruction_index = verify_token(capitalize_string(tokens[0]));

			if (matched_instruction_index == NOT_IN_TABLE) {
				if (tokens.size() > 1) {
					state = S2;
				}
				
				else {
					record += "\n";
					state = S4;
				}
			}

			else {
				state = S3;
				label = "";
				args_in_record = tokens.size() - 1;
			}
			break;

		case(S2):
			matched_instruction_index = verify_token(capitalize_string(tokens[1]));

			if (matched_instruction_index == NOT_IN_TABLE) {
				record += "\n";
				state = S4;
			}

			else {
				state = S3;
				label = tokens[0];
				args_in_record = tokens.size() - 2;
			}
			break;

		case(S3):
			error_code = error_check(matched_instruction_index, label, args_in_record);
			if (error_code == 0) {
				record = record_emulation(matched_instruction_index, tokens[(tokens.size() - 1)], label);
			}

			else {
				record += "\t; Error: " + error_message(error_code);
			}
			state = S4;
			break;

		case(S4):
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

std::string error_message(int error_code)
{
	switch (error_code) {
	case (NO_ERROR):
		return "";
		break;
	case (LABEL_TOO_LONG):
		return "Label is over 32 characters long \n";
		break;
	case (LABEL_NOT_ALPHANUM):
		return "Non-alphanumeric symbol in label \n";
		break;
	case (TOO_MANY_ARGS):
		return "There are too many arguments for this instruction \n";
		break;
	case (TOO_LITTLE_ARGS):
		return "There are not enough arguments for this instruction \n";
		break;

	default:
		return "";
		break;
	}
}