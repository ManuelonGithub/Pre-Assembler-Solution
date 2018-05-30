#include "stdafx.h"
#include <string>
#include <vector>
#include "Record_operations.h"

std::vector<std::string> record_tokenizer(std::string record)
{
	char prev_token_pos= 0, current_token_pos = 0;
	std::string token, delimiter = " ,";
	std::vector<std::string> tokens;

	while (current_token_pos != std::string::npos) {

		current_token_pos = record.find_first_of(delimiter, prev_token_pos);

		token = record.substr(prev_token_pos, current_token_pos - prev_token_pos);

		if(!token.empty())
			tokens.emplace_back(token);

		prev_token_pos = current_token_pos + 1;
	}

	return tokens;
}

//std::string read_line()
//{
//
//}
