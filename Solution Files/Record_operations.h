
#pragma once
#ifndef TOKEN_OPERATIONS_H
#define TOKEN_OPERATIONS_H
	
std::vector<std::string> record_tokenizer(std::string record);

void remove_comment(std::string &line);

std::string capitalize_string(std::string line);

std::string error_message(int error_flag);

#endif // !TOKEN_OPERATIONS_H
