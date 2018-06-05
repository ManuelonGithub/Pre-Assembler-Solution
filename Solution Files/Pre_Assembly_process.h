#pragma once
#ifndef PRE_ASSEMBLY_PROCESS_H
#define PRE_ASSEMBLY_PROCESS

#define DONE 1
enum STATES { S0, S1, S2, S3, S4 };

std::string out_file_name(std::string filename);

void pre_assembly_process(std::string &record);

#endif // !PRE_ASSEMBLY_PROCESS_H
