//
// Created by nik on 11/29/22.
//

#pragma once

#ifndef LANG2_TOKEN_H
#define LANG2_TOKEN_H

#include <map>
#include <string>
#include <cstring>
#include <ostream>

#undef NULL // shouldn't be used anyway

namespace Lang {

enum class TokenType {
	INVALID = 0,
	WHILE,       // while
	IF,          // if
	ELSE,        // else
	FOR,         // for
	FOREACH,     // foreach
	IN,          // in
	CONTINUE,    // continue
	BREAK,       // break
	TRUE,        // true
	FALSE,       // false
	NULL,        // null
	IMPORT,      // import
	INCL,        // include
	AS,          // as
	FN,          // fn
	RETURN,      // return
	FAT_ARROW,   // =>
	THIN_ARROW,  // ->
	ASSN,        // =
	DQM,         // ??
	QM,          // ?
	COL,         // :
	ADD,         // +
	SUB,         // -
	DIV,         // /
	STAR,        // *
	STARSTAR,    // **
	MOD,         // %
	AMP,         // &
	AND,         // &&
	CARET,       // ^
	PIPE,        // |
	OR,          // ||
	NOT,         // !
	EQ,          // ==
	NE,          // !=
	GT,          // >=
	LT,          // <=
	GE,          // >
	LE,          // <
	LSHIFT,      // <<
	RSHIFT,      // >>
	TILDE,       // ~
	INC,         // ++
	DEC,         // --
	SUBASSN,     // -=
	ADDASSN,     // +=
	MULASSN,     // *=
	DIVASSN,     // /=
	DOT,         // .
	DDOT,        // ..
	COMMA,       // ,
	SCOL,        // ;
	LPAREN,      // (
	RPAREN,      // )
	LBRACE,      // {
	RBRACE,      // }
	LBRACK,      // [
	RBRACK,      // ]
	IDENTIFIER,
	LIT_STR,
	LIT_CHR,
	LIT_INT,
	LIT_FLT,
	LIT_BOOL,
	__TOK_SIZE,
};


struct Token {
	Token(TokenType type, std::string value, int row, int start_char,
		  int end_char);

	Token(Token const& other) = default;

	~Token() = default;

	// TODO: should include a filename
	const TokenType type;
	std::string value;
	int row = 0;
	int start_char = 0;
	int end_char = 0;
};

static const std::map<TokenType, char const*> types = {
		{TokenType::INVALID,    "TOK_INVALID",},
		{TokenType::WHILE,      "while",},
		{TokenType::IF,         "if",},
		{TokenType::ELSE,       "else",},
		{TokenType::FOR,        "for",},
		{TokenType::FOREACH,    "foreach",},
		{TokenType::IN,         "in",},
		{TokenType::CONTINUE,   "continue",},
		{TokenType::BREAK,      "break",},
		{TokenType::TRUE,       "true",},
		{TokenType::FALSE,      "false",},
		{TokenType::NULL,       "null",},
		{TokenType::IMPORT,     "import",},
		{TokenType::INCL,       "include",},
		{TokenType::AS,         "as",},
		{TokenType::FN,         "fn",},
		{TokenType::RETURN,     "return",},
		{TokenType::FAT_ARROW,  "=>",},
		{TokenType::THIN_ARROW, "->",},
		{TokenType::ASSN,       "=",},
		{TokenType::DQM,        "??",},
		{TokenType::QM,         "?",},
		{TokenType::COL,        ":",},
		{TokenType::ADD,        "+",},
		{TokenType::SUB,        "-",},
		{TokenType::DIV,        "/",},
		{TokenType::STAR,       "*",},
		{TokenType::STARSTAR,   "**",},
		{TokenType::MOD,        "%",},
		{TokenType::AMP,        "&",},
		{TokenType::AND,        "&&",},
		{TokenType::CARET,      "^",},
		{TokenType::PIPE,       "|",},
		{TokenType::OR,         "||",},
		{TokenType::NOT,        "!",},
		{TokenType::EQ,         "==",},
		{TokenType::NE,         "!=",},
		{TokenType::GT,         ">=",},
		{TokenType::LT,         "<=",},
		{TokenType::GE,         ">",},
		{TokenType::LE,         "<",},
		{TokenType::LSHIFT,     "<<",},
		{TokenType::RSHIFT,     ">>",},
		{TokenType::TILDE,      "~",},
		{TokenType::INC,        "++",},
		{TokenType::DEC,        "--",},
		{TokenType::SUBASSN,    "-=",},
		{TokenType::ADDASSN,    "+=",},
		{TokenType::MULASSN,    "*=",},
		{TokenType::DIVASSN,    "/=",},
		{TokenType::DOT,        ".",},
		{TokenType::DDOT,       "..",},
		{TokenType::COMMA,      ",",},
		{TokenType::SCOL,       ";",},
		{TokenType::LPAREN,     "(",},
		{TokenType::RPAREN,     ")",},
		{TokenType::LBRACE,     "{",},
		{TokenType::RBRACE,     "}",},
		{TokenType::LBRACK,     "[",},
		{TokenType::RBRACK,     "]",},
		{TokenType::IDENTIFIER, "TOK_IDEN",},
		{TokenType::LIT_STR,    "TOK_LIT_STR",},
		{TokenType::LIT_CHR,    "TOK_LIT_CHR",},
		{TokenType::LIT_INT,    "TOK_LIT_INT",},
		{TokenType::LIT_FLT,    "TOK_LIT_FLT",},
		{TokenType::LIT_BOOL,   "TOK_LIT_BOOL",},
};

static TokenType find_by_value(const char* val) {
	for (const auto [first, second]: types) {
		if (strcmp(second, val) == 0) {
			return first;
		}
	}

	return TokenType::INVALID;
}

}
#endif //LANG2_TOKEN_H
