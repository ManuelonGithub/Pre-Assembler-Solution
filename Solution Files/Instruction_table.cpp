#include "stdafx.h"
#include <iostream>
#include <iomanip>
#include <string>
#include "Instruction_table.h"

const struct emulated_instruction inst_table[] = {
	{ "ADC", "ADDC", "#0,", AFTER, 1 },
	{ "ADC.W", "ADDC.W", "#0,", AFTER, 1 },
	{ "ADC.B", "ADDC.B", "#0,", AFTER, 1 },
	{ "CALL", "BL", "", AFTER,  1 },
	{ "CLR", "MOV", "#0,", AFTER,  1 },
	{ "CLR.W", "MOV.W", "#0,", AFTER, 1 },
	{ "CLR.B", "MOV.B", "#0,", AFTER, 1 },
	{ "CLRC", "BIC", "#1,R6", NO_ARG, 0 },
	{ "CLRN", "BIC", "#4,R6", NO_ARG, 0 },
	{ "CLRZ", "BIC", "#2,R6", NO_ARG, 0 },
	{ "DADC", "DADD", "#0,", AFTER, 1 },
	{ "DADC.W", "DADD.W", "#0,", AFTER, 1 },
	{ "DADC.B", "DADD.B", "#0,", AFTER, 1 },
	{ "DEC", "SUB", "#1,", AFTER, 1 },
	{ "DEC.W", "SUB.W", "#1,", AFTER, 1 },
	{ "DEC.B", "SUB.B", "#1,", AFTER, 1 },
	{ "DECD", "SUB", "#2,", AFTER, 1 },
	{ "DECD.W", "SUB.W", "#2,", AFTER, 1 },
	{ "DECD.B", "SUB.B", "#2,", AFTER, 1 },
	{ "INC", "ADD", "#1,", AFTER, 1 },
	{ "INC.W", "ADD.W", "#1,", AFTER, 1 },
	{ "INC.B", "ADD.B", "#1,", AFTER, 1 },
	{ "INCD", "ADD", "#2,", AFTER, 1 },
	{ "INCD.W", "ADD.W", "#2,", AFTER, 1 },
	{ "INCD.B", "ADD.B", "#2,", AFTER, 1 },
	{ "INV", "XOR", "#-1,", AFTER, 1 },
	{ "INV.W","XOR.W", "#-1,", AFTER, 1 },
	{ "INV.B", "XOR.B", "#-1,", AFTER, 1 },
	{ "JUMP", "MOV", ",rR7",  BEFORE, 1 },
	{ "NOP", "MOV", "R6,R6", NO_ARG, 0 },
	{ "PULL", "LD", "R5+,", AFTER, 1 },
	{ "PUSH", "ST", ",-R5,", BEFORE, 1 },
	{ "RET", "MOV", "R4,R7", NO_ARG, 0 },
	{ "RLC", "ADDC", "", BOTH, 1 },
	{ "RLC.W", "ADDC.W", "", BOTH, 1 },
	{ "RLC.B", "ADDC.B", "", BOTH, 1 },
	{ "SBC", "SUBC", "#0,", AFTER, 1 },
	{ "SBC.W", "SUBC.W", "#0,", AFTER, 1 },
	{ "SBC.B", "SUBC.B", "#0,", AFTER, 1 },
	{ "SETC", "BIS", "#1,R6", NO_ARG, 0 },
	{ "SETN", "BIS", "#4,R6", NO_ARG, 0 },
	{ "SETZ", "BIS", "#2,R6", NO_ARG, 0 },
	{ "SLA", "ADD", "", BOTH, 1 },
	{ "SLA.W", "ADD.W", "", BOTH, 1 },
	{ "SLA.B", "ADD.B", "", BOTH, 1 },
	{ "SPL0", "MOVLZ", "#$0,R6", NO_ARG, 0 },
	{ "SPL1", "MOVLZ", "#$20,R6", NO_ARG, 0 },
	{ "SPL2", "MOVLZ", "#$40,R6", NO_ARG, 0 },
	{ "SPL3", "MOVLZ", "#$60,R6", NO_ARG, 0 },
	{ "SPL4", "MOVLZ", "#$80,R6", NO_ARG, 0 },
	{ "SPL5", "MOVLZ", "#$A0,R6", NO_ARG, 0 },
	{ "SPL6", "MOVLZ", "#$C0,R6", NO_ARG, 0 },
	{ "SPL7", "MOVLZ", "#$E0,R6", NO_ARG, 0 },
	{ "TST", "CMP", "#0,", AFTER, 1 },
	{ "TST.W", "CMP.W", "#0,", AFTER, 1 },
	{ "TST.B", "CMP.B", "#0,", AFTER, 1 },
};

int size_of_table()
{
	return (sizeof(inst_table) / sizeof(emulated_instruction));
}

void print_whole_table(std::string arg, std::ostream &out)
{
	for (int i = 0; i < size_of_table(); i++) {
		out << print_emulated_record(i, arg) << std::endl;
	}
}

std::string print_emulated_record(int inst_index, std::string arg, std::string label)
{
	std::string emulated_record = label + "    " + inst_table[inst_index].XM_emulated_inst + "\t";

	switch (inst_table[inst_index].retrieved_arg_pos) {
	case NO_ARG:
		emulated_record = emulated_record + inst_table[inst_index].XM_emulated_inst_arg;
		break;

	case BEFORE:
		emulated_record = emulated_record + arg + inst_table[inst_index].XM_emulated_inst_arg;
		break;

	case AFTER:
		emulated_record = emulated_record + inst_table[inst_index].XM_emulated_inst_arg + arg;
		break;

	case BOTH:
		emulated_record = emulated_record + arg + "," + arg;
		break;

	default:
		emulated_record = "Invalid input";
		break;
	}

	return emulated_record;
}

int token_verifier(std::string token, int min_index, int max_index) 
{
	if (max_index < min_index) {
		return (NOT_IN_TABLE);
	}

	int pivot_index = min_index + ((max_index - min_index) / 2);

	if (token == inst_table[pivot_index].asm_inst) {
		return pivot_index;
	}

	else if (token_offset(token, inst_table[pivot_index].asm_inst) == BEFORE) {
		return token_verifier(token, min_index, (pivot_index - 1));
	}

	else 
		return token_verifier(token, (pivot_index + 1), max_index);
}

int token_offset(std::string token, std::string asm_inst)
{
	int i = 0;

	while (token[i] == asm_inst[i]) {
		i++;
	}

	//while (i < asm_inst.length()) {
	//	if (token[i] < asm_inst[i]) {
	//		offset = BEFORE;
	//		break;
	//	}

	//	else if (token[i] > asm_inst[i]) {
	//		offset = AFTER;
	//		break;
	//	}
	//	i++;
	//}

	if (token[i] < asm_inst[i]) {
		return BEFORE;
	}

	else
		return AFTER;
}

int arg_check(char record_arg_no, char inst_index)
{
	signed char offset = record_arg_no - inst_table[inst_index].retrieved_arg_amount;

	if (offset == CORRECT_ARGS) {
		return CORRECT_ARGS;
	}

	else if (offset > CORRECT_ARGS) {
		return TOO_MANY_ARGS;
	}

	else {
		return TOO_LITTLE_ARGS;
	}
}