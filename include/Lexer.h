//
// Created by nik on 12/1/22.
//

#ifndef LANG2_LEXER_H
#define LANG2_LEXER_H

#include <memory>
#include <string>
#include <vector>
#include <exception>
#include <cstring>
#include <iostream>

#include "Token.h"
#include "Iterator.h"
#include "Utility.h"

namespace Lang {

/**
 * Maximum length of an identifier.
 */
static const int max_identifier_length = 256;

class Lexer : public Iterator::Indexed_Char_Iterator {
public:
	explicit Lexer(std::string& text);
	~Lexer() = default;

	void lex();

private:

	void do_lex();

	std::shared_ptr<std::string> buffer;

	std::vector<Token::Token> tokens;

	bool is_startof_line_comment();

	Lang::Token::Type parse_operator();
	Token::Token parse_keyword();
	bool is_startof_identifier();
	void emit_token(const Lang::Token::Token& token);
	bool is_startof_string();
	Lang::Token::Token parse_string();
	bool is_startof_number();
	Token::Token parse_number();
	char resolve_escape_sequence(const char);
	bool is_startof_char();
	Token::Token parse_char();
};

class Lexer_Error : public std::exception {
public:
	explicit Lexer_Error(const char* msg) : msg(msg) {}

	const char* what() const _GLIBCXX_TXN_SAFE_DYN _GLIBCXX_NOTHROW override {
		return msg;
	}

protected:
	const char* msg;
};

class Lexer_Token_Error : public Lexer_Error {
public:
	Lexer_Token_Error(const char* msg, const Lang::Token::Token& token) : Lexer_Error(msg), token(token) {}

	const Lang::Token::Token& get_token() const { return token; }

protected:
	const Lang::Token::Token token;
};

class Lexer_Location_Error : public Lexer_Error {
public:
	Lexer_Location_Error(const char* msg, int row, int start_col, int end_col)
		: Lexer_Error(msg)
		  , row(row)
		  , start_col(start_col)
		  , end_col(end_col) {}

	const int get_row() const { return row; }

	const int get_start_col() const { return start_col; }

	const int get_end_col() const { return end_col; }

protected:
	const int row;
	const int start_col;
	const int end_col;
};

}

#endif //LANG2_LEXER_H