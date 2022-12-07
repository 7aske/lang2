//
// Created by nik on 11/29/22.
//
#include "Token.h"

#include <utility>

namespace Lang {

Token::Token(const TokenType type, std::string value, const int row,
			 const int start_char, const int end_char)
		: type(type), value(std::move(value)), row(row), start_char(start_char),
		  end_char(end_char) {}

std::ostream& operator<<(std::ostream& os, const Token& token) {
	os << token.value << " " << token.row << ":"
	   << token.start_char << "-" << token.end_char;
	return os;
}

}
