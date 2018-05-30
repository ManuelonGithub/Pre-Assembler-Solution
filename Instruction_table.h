
#pragma once
#ifndef INSTRUCTION_TABLE_H
#define INSTRUCTION_TABLE_H

enum inst_arg_possibilities { CORRECT_ARGS = 0, TOO_LITTLE_ARGS = -1, TOO_MANY_ARGS = 1 };
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

std::string print_emulated_record(std::string arg, struct emulated_instruction inst);

int arg_check(char record_arg_no, char inst_index);


#endif // !INSTRUCTION_TABLE_H