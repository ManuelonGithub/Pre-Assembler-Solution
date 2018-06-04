
#pragma once
#ifndef TOKEN_OPERATIONS_H
#define TOKEN_OPERATIONS_H
	
std::vector<std::string> record_tokenizer(std::string record);

void remove_comment(std::string &line);

void Capitalize_string(std::string &line);

#endif // !TOKEN_OPERATIONS_H
