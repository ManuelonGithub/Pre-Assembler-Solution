#include "stdafx.h"
#include <string>
#include <vector>
#include "Record_operations.h"


void record_tokenizer(std::string record, std::vector<std::string> &tokens)
{
	size_t prev_token_pos= 0, current_token_pos = 0;
	std::string token, delimiter = " , \t \n";

	while (current_token_pos != std::string::npos) {

		current_token_pos = record.find_first_of(delimiter, prev_token_pos);

		token = record.substr(prev_token_pos, current_token_pos - prev_token_pos);

		if(!token.empty())
			tokens.emplace_back(token);

		prev_token_pos = current_token_pos + 1;
	}
}


void remove_comment(std::string &line)
{
	char current_token_pos = 0;

	current_token_pos = line.find_first_of(';');

	line = line.substr(0, current_token_pos);
}


bool is_whitespace(std::string &line)
{
	for (int i = 0; i < line.size(); i++) {
		if (!isblank(line[i])) {
			return false;
		}
	}

	return true;
}


std::string capitalize_string(std::string line)
{
	for (int i = 0; i < line.length(); i++) {
		line[i] = toupper(line[i]);
	}

	return line;
}