
#pragma once
#ifndef INSTRUCTION_TABLE_H
#define INSTRUCTION_TABLE_H

#define NOT_IN_TABLE -1

enum error_codes { NO_ERROR, LABEL_TOO_LONG, LABEL_NOT_ALPHANUM, TOO_MANY_ARGS, TOO_LITTLE_ARGS};
enum retrieved_arg_syntax_pos { NO_ARG, BEFORE, AFTER, BOTH };

struct emulated_instruction {
	std::string asm_inst;
	std::string XM_emulated_inst;
	std::string XM_emulated_inst_arg;
	char retrieved_arg_pos;
	char retrieved_arg_amount;
};

int size_of_table();

void print_whole_table(std::string arg = "", std::ostream &out = std::cout);

std::string record_emulation(int inst_index, std::string arg = "", std::string label = "");

int verify_token(std::string token, int min_index = 0, int max_index = 0);

int token_offset(std::string token, std::string asm_inst);

int arg_check(char record_arg_no, char inst_index);

int error_check(int inst_index, std::string label, int record_arg_count);

#endif // !INSTRUCTION_TABLE_H