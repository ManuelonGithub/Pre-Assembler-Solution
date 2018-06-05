// PreAssembler.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <fstream>
#include "Pre_Assembly_process.h"


int main(int argc, char * argv[])
{
	std::ifstream asm_file_in;
	std::ofstream asm_file_out;

	/* checking if the correct amount of files have been passed to the system */
	if (argc != 2) {												
		std::cout << "Invalid number of arguments." << std::endl;
		getchar();
		return 1;	/* If there's too many or too little args, the system will stop operating */
	}

	asm_file_in.open(argv[1]);	/* The system attempts to open the single file that was passed */

	/* In C++ you can use the stream as a boolean entity to determine if it successfully opened the file */
	if (!asm_file_in) {
		std::cout << argv[1] << " is not a valid input file." << std::endl;
		getchar();
		return 1;
	}

	/* creating output file. 'out_file_name' function is specified in Pre_Assembly_process.cpp */
	asm_file_out.open(out_file_name(argv[1]));

	std::cout << "Input file:\t" << argv[1] << "\n\n";	/* It specifies exactly which file the Pre-Assembly is processing */

	std::string record;			/* variable that copies each line of the input file */
	unsigned int line = 0;		/* File line counter */
	char error_code;			/* Variable is set with the code corresponding to its error. See 'enum error_codes' in Instruction_table.h*/
	bool error_flag = false;	/* Flag that is raised if the system finds an error in the input file */

	/* Looping until the system reaches the end of the input file */
	while (std::getline(asm_file_in, record)) {

		line++;
		error_code = 0;	/* resetting the error_code for a new line*/

		pre_assembly_process(record, error_code);	/* The pre-assembly staged process */
		asm_file_out << record;						

		/* Notifying the user if an error was found in the input file. The pre_assembly_process also flags the error in the output file */
		if (error_code != 0) {
			std::cout << "Error found on line " << line << ": " << error_message(error_code);
			error_flag = true;
		}
	}

	asm_file_in.close();
	asm_file_out.close();

	/* If an error was found the system pauses in the end to let the user review the errors */
	if (error_flag) {
		std::cout << "\n\n Press ENTER to continue . . . . .";
		getchar();
	}

    return 0;
}