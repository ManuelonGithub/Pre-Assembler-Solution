
#pragma once
#ifndef PRE_ASSEMBLY_PROCESS_H
#define PRE_ASSEMBLY_PROCESS

#define DONE 1

/* Number of stages in the pre_assembly_process. Each stage has its description documented beside it */
enum STAGES { S0, S1, S2, S3, S4 };


/* Function prototypes pertaining to the pre-assembly process: */
void pre_assembly_process(std::string &record, char &error_code);

std::string out_file_name(std::string filename);

std::string error_message(int error_code);

#endif // !PRE_ASSEMBLY_PROCESS_H
