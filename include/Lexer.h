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
static constexpr int max_identifier_length = 256;

class Lexer : public Indexed_Char_Iterator {
public:
	explicit Lexer(std::string const& text);

	~Lexer() override = default;

	void lex();

	std::vector<Token> get_tokens() const;

private:
	std::string buffer;

	std::vector<Token> tokens;

	void do_lex();

	bool is_startof_line_comment();

	TokenType parse_operator();

	Token parse_keyword();

	bool is_startof_identifier();

	bool is_startof_block_comment();

	bool is_endof_block_comment();

	void emit_token(const Token& token);

	bool is_startof_string();

	Token parse_string();

	bool is_startof_number();

	Token parse_number();

	char resolve_escape_sequence(char) const;

	bool is_startof_char();

	Token parse_char();

	void parse_block_comment();

	bool is_identifier();
};

class Lexer_Error : public std::exception {
public:
	explicit Lexer_Error(const char* msg)
			: msg(msg) {}

	const char* what() const _GLIBCXX_TXN_SAFE_DYN _GLIBCXX_NOTHROW override {
		return msg;
	}

	virtual int get_row() const = 0;

	virtual int get_start_col() const = 0;

	virtual int get_end_col() const = 0;

protected:
	const char* msg;
};

class Lexer_Token_Error : public Lexer_Error {
public:
	Lexer_Token_Error(const char* msg, const Token& token)
			: Lexer_Error(msg), token(token) {}

	const Token& get_token() const { return token; }

	int get_row() const override { return token.row; }

	int get_start_col() const override { return token.start_char; }

	int get_end_col() const override { return token.end_char; }

protected:
	const Token token;
};

class Lexer_Location_Error : public Lexer_Error {
public:
	Lexer_Location_Error(const char* msg, int row, int start_col, int end_col)
			: Lexer_Error(msg)
			  , row(row)
			  , start_col(start_col)
			  , end_col(end_col) {}

	int get_row() const override { return row; }

	int get_start_col() const override { return start_col; }

	int get_end_col() const override { return end_col; }

protected:
	const int row;
	const int start_col;
	const int end_col;
};

}

#endif //LANG2_LEXER_H