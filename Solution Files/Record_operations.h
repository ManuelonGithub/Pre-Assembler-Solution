
#pragma once
#ifndef TOKEN_OPERATIONS_H
#define TOKEN_OPERATIONS_H
	
void record_tokenizer(std::string record, std::vector<std::string> &tokens);

void remove_comment(std::string &line);

bool is_whitespace(std::string &line);

std::string capitalize_string(std::string line);

#endif // !TOKEN_OPERATIONS_H
