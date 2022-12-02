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

namespace Lang::Token {

enum class Type {
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
	Token(Type type, std::string value, int row, int start_char, int end_char);
	~Token() = default;

	const Type type;
	const std::string value;
	const int row = 0;
	const int start_char = 0;
	const int end_char = 0;

	friend std::ostream& operator<<(std::ostream& os, const Token& token);
};

static const std::map<Type, char const*> types = {
	{Type::INVALID,    "TOK_INVALID",},
	{Type::WHILE,      "while",},
	{Type::IF,         "if",},
	{Type::ELSE,       "else",},
	{Type::FOR,        "for",},
	{Type::FOREACH,    "foreach",},
	{Type::IN,         "in",},
	{Type::CONTINUE,   "continue",},
	{Type::BREAK,      "break",},
	{Type::TRUE,       "true",},
	{Type::FALSE,      "false",},
	{Type::NULL,       "null",},
	{Type::IMPORT,     "import",},
	{Type::INCL,       "include",},
	{Type::AS,         "as",},
	{Type::FN,         "fn",},
	{Type::RETURN,     "return",},
	{Type::FAT_ARROW,  "=>",},
	{Type::THIN_ARROW, "->",},
	{Type::ASSN,       "=",},
	{Type::DQM,        "??",},
	{Type::QM,         "?",},
	{Type::COL,        ":",},
	{Type::ADD,        "+",},
	{Type::SUB,        "-",},
	{Type::DIV,        "/",},
	{Type::STAR,       "*",},
	{Type::STARSTAR,   "**",},
	{Type::MOD,        "%",},
	{Type::AMP,        "&",},
	{Type::AND,        "&&",},
	{Type::CARET,      "^",},
	{Type::PIPE,       "|",},
	{Type::OR,         "||",},
	{Type::NOT,        "!",},
	{Type::EQ,         "==",},
	{Type::NE,         "!=",},
	{Type::GT,         ">=",},
	{Type::LT,         "<=",},
	{Type::GE,         ">",},
	{Type::LE,         "<",},
	{Type::LSHIFT,     "<<",},
	{Type::RSHIFT,     ">>",},
	{Type::TILDE,      "~",},
	{Type::INC,        "++",},
	{Type::DEC,        "--",},
	{Type::SUBASSN,    "-=",},
	{Type::ADDASSN,    "+=",},
	{Type::MULASSN,    "*=",},
	{Type::DIVASSN,    "/=",},
	{Type::DOT,        ".",},
	{Type::DDOT,       "..",},
	{Type::COMMA,      ",",},
	{Type::SCOL,       ";",},
	{Type::LPAREN,     "(",},
	{Type::RPAREN,     ")",},
	{Type::LBRACE,     "{",},
	{Type::RBRACE,     "}",},
	{Type::LBRACK,     "[",},
	{Type::RBRACK,     "]",},
	{Type::IDENTIFIER, "TOK_IDEN",},
	{Type::LIT_STR,    "TOK_LIT_STR",},
	{Type::LIT_CHR,    "TOK_LIT_CHR",},
	{Type::LIT_INT,    "TOK_LIT_INT",},
	{Type::LIT_FLT,    "TOK_LIT_FLT",},
	{Type::LIT_BOOL,   "TOK_LIT_BOOL",},
};

static Type find_by_value(const char* val) {
	for (const auto & type : types) {
		if (strcmp(type.second, val) == 0) {
			return type.first;
		}
	}

	return Type::INVALID;
}

}
#endif //LANG2_TOKEN_H
