//
// Created by nik on 11/29/22.
//
#include "Token.h"

#include <utility>

Lang::Token::Token::Token(const Type type, std::string value, const int row, const int start_char, const int end_char)
	: type(type)
	  , value(std::move(value))
	  , row(row)
	  , start_char(start_char)
	  , end_char(end_char) {}

std::ostream& Lang::Token::operator<<(std::ostream& os, const Lang::Token::Token& token) {
	os << token.value << " " << token.row << ":"
	   << token.start_char << "-" << token.end_char;
	return os;
}