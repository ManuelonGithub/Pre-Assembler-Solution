#include "stdafx.h"
#include <string>
#include <vector>
#include "Record_operations.h"

enum error_codes { NO_ERROR, LABEL_TOO_LONG, LABEL_NOT_ALPHANUM, TOO_MANY_ARGS, TOO_LITTLE_ARGS };

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

void remove_comment(std::string &line)
{
	char current_token_pos = 0;

	current_token_pos = line.find_first_of(';');

	line = line.substr(0, current_token_pos);
}

std::string capitalize_string(std::string line)
{
	for (int i = 0; i < line.length(); i++) {
		line[i] = toupper(line[i]);
	}

	return line;
}

std::string error_message(int error_flag)
{
	switch (error_flag) {
	case (NO_ERROR):
		return "";
		break;
	case (LABEL_TOO_LONG):
		return "; Error: Label is over 32 characters long";
		break;
	case (LABEL_NOT_ALPHANUM):
		return "; Error: non-alphanumeric symbol in label";
		break;
	case (TOO_MANY_ARGS):
		return "; Error: there are too many arguments for this instrution";
		break;
	case (TOO_LITTLE_ARGS):
		return "; Error: there are not enough arguments for this instrution";
		break;

	default:
		return "";
		break;
	}
}