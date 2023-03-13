//
// Created by nik on 11/29/22.
//

#pragma once

#ifndef LANG2_TOKEN_H
#define LANG2_TOKEN_H

#include <unordered_map>
#include <string>
#include <cstring>
#include <ostream>

namespace Lang {

enum class TokenType {
	INVALID = 0,
	SUPER,                     // super
	CLASS,                     // class
	THIS,                      // this
	WHILE,                     // while
	IF,                        // if
	ELSE,                      // else
	FOR,                       // for
	FOREACH,                   // foreach
	IN,                        // in
	CONTINUE,                  // continue
	BREAK,                     // break
	TRUE,                      // true
	FALSE,                     // false
	NIL,                       // nil
	IMPORT,                    // import
	INCL,                      // include
	AS,                        // as
	FN,                        // fn
	RETURN,                    // return
	FAT_ARROW,                 // =>
	THIN_ARROW,                // ->
	EQUAL,                     // =
	QUESTIONMARK_QUESTIONMARK, // ??
	QUESTIONMARK,              // ?
	COLON,                     // :
	PLUS,                      // +
	MINUS,                     // -
	SLASH,                     // /
	STAR,                      // *
	STAR_STAR,                 // **
	PERCENT,                   // %
	AMPERSAND,                 // &
	AMPERSAND_AMPERSAND,       // &&
	CARET,                     // ^
	PIPE,                      // |
	PIPE_PIPE,                 // ||
	BANG,                      // !
	EQUAL_EQUAL,               // ==
	BANG_EQUAL,                // !=
	GREATER_EQUAL,             // >=
	LESS_EQUAL,                // <=
	GREATER,                   // >
	LESS,                      // <
	LESS_LESS,                 // <<
	GREATER_GREATER,           // >>
	TILDE,                     // ~
	PLUS_PLUS,                 // ++
	MINUS_MINUS,               // --
	MINUS_EQUAL,               // -=
	PLUS_EQUAL,                // +=
	STAR_EQUAL,                // *=
	SLASH_EQUAL,               // /=
	DOT,                       // .
	DOT_DOT,                   // ..
	COMMA,                     // ,
	SEMICOLON,                 // ;
	LEFT_PARENTHESIS,          // (
	RIGHT_PARENTHESIS,         // )
	LEFT_BRACE,                // {
	RIGHT_BRACE,               // }
	LEFT_BRACKET,              // [
	RIGHT_BRACKET,             // ]
	LET,                       // let
	CONST,                     // const
	IDENTIFIER,
	STRING,
	CHAR,
	INTEGER,
	FLOAT,
	__TOK_SIZE,
};


struct Token {
	Token(TokenType type, std::string value, int row, int start_char,
		  int end_char);

	Token(Token const& other) = default;

	~Token() = default;

	// TODO: should include a filename
	TokenType type;
	std::string value;
	int row = 0;
	int start_char = 0;
	int end_char = 0;

};

static const std::unordered_map<std::string, TokenType> types = {
		{"class",    TokenType::CLASS,},
		{"super",    TokenType::SUPER,},
		{"this",     TokenType::THIS,},
		{"while",    TokenType::WHILE,},
		{"if",       TokenType::IF,},
		{"else",     TokenType::ELSE,},
		{"for",      TokenType::FOR,},
		{"foreach",  TokenType::FOREACH,},
		{"in",       TokenType::IN,},
		{"continue", TokenType::CONTINUE,},
		{"break",    TokenType::BREAK,},
		{"true",     TokenType::TRUE,},
		{"false",    TokenType::FALSE,},
		{"nil",      TokenType::NIL,},
		{"import",   TokenType::IMPORT,},
		{"include",  TokenType::INCL,},
		{"as",       TokenType::AS,},
		{"fn",       TokenType::FN,},
		{"return",   TokenType::RETURN,},
		{"=>",       TokenType::FAT_ARROW,},
		{"->",       TokenType::THIN_ARROW,},
		{"=",        TokenType::EQUAL,},
		{"??",       TokenType::QUESTIONMARK_QUESTIONMARK,},
		{"?",        TokenType::QUESTIONMARK,},
		{":",        TokenType::COLON,},
		{"+",        TokenType::PLUS,},
		{"-",        TokenType::MINUS,},
		{"/",        TokenType::SLASH,},
		{"*",        TokenType::STAR,},
		{"**",       TokenType::STAR_STAR,},
		{"%",        TokenType::PERCENT,},
		{"&",        TokenType::AMPERSAND,},
		{"&&",       TokenType::AMPERSAND_AMPERSAND,},
		{"^",        TokenType::CARET,},
		{"|",        TokenType::PIPE,},
		{"||",       TokenType::PIPE_PIPE,},
		{"!",        TokenType::BANG,},
		{"==",       TokenType::EQUAL_EQUAL,},
		{"!=",       TokenType::BANG_EQUAL,},
		{">=",       TokenType::GREATER_EQUAL,},
		{"<=",       TokenType::LESS_EQUAL,},
		{">",        TokenType::GREATER,},
		{"<",        TokenType::LESS,},
		{"<<",       TokenType::LESS_LESS,},
		{">>",       TokenType::GREATER_GREATER,},
		{"~",        TokenType::TILDE,},
		{"++",       TokenType::PLUS_PLUS,},
		{"--",       TokenType::MINUS_MINUS,},
		{"-=",       TokenType::MINUS_EQUAL,},
		{"+=",       TokenType::PLUS_EQUAL,},
		{"*=",       TokenType::STAR_EQUAL,},
		{"/=",       TokenType::SLASH_EQUAL,},
		{".",        TokenType::DOT,},
		{"..",       TokenType::DOT_DOT,},
		{",",        TokenType::COMMA,},
		{";",        TokenType::SEMICOLON,},
		{"(",        TokenType::LEFT_PARENTHESIS,},
		{")",        TokenType::RIGHT_PARENTHESIS,},
		{"{",        TokenType::LEFT_BRACE,},
		{"}",        TokenType::RIGHT_BRACE,},
		{"[",        TokenType::LEFT_BRACKET,},
		{"]",        TokenType::RIGHT_BRACKET,},
		{"let",      TokenType::LET,},
		{"const",    TokenType::CONST,},
};

static const std::string& find_by_value(TokenType val) {
	for (const auto& [first, second]: types) {
		if (second == val) {
			return first;
		}
	}

	throw std::runtime_error("Unable to find token type value");
}

}
#endif //LANG2_TOKEN_H
