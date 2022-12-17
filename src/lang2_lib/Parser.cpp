//
// Created by nik on 12/6/22.
//

#include <iostream>

#include "Parser.h"
#include "Utility.h"

namespace Lang {

Parser::Parser(std::string const& text, const std::vector<Token>& tokens)
		: Iterator<Token>()
		  , text(text)
		  , iter(tokens.begin())
		  , end(tokens.end())
		  , tokens(tokens) {

	this->nodes.reserve(1024);
}

std::vector<Ast::Node> Parser::get_nodes() const {
	return nodes;
}

void Parser::parse() {

	while (has_next()) {
		try {
			nodes.push_back(parse_statement());
		} catch (Parser_Location_Error& ex) {
			print_location(text, ex.get_row(), ex.get_start_col(),
						   ex.get_end_col());
			std::cerr << RED << ex.what() << std::endl << RESET;
			return;
		} catch (Parser_Token_Error& ex) {
			print_location(text, ex.get_token().row, ex.get_token().start_char,
						   ex.get_token().end_char);
			std::cerr << RED << ex.what() << std::endl << RESET;
			return;
		}
	}

}

Ast::Node Parser::parse_expression() {
	Ast::Node node = create_node(next());
	return node;
}

Ast::Node Parser::parse_statement() {
	return parse_expression();
}

Ast::Node Parser::create_node(Token token) {
	switch (token.type) {
		case TokenType::INVALID:
		case TokenType::WHILE:
		case TokenType::IF:
		case TokenType::ELSE:
		case TokenType::FOR:
		case TokenType::FOREACH:
		case TokenType::IN:
		case TokenType::CONTINUE:
		case TokenType::BREAK:
		case TokenType::TRUE:
		case TokenType::FALSE:
		case TokenType::NIL:
		case TokenType::IMPORT:
		case TokenType::INCL:
		case TokenType::AS:
		case TokenType::FN:
		case TokenType::RETURN:
		case TokenType::FAT_ARROW:
		case TokenType::THIN_ARROW:
		case TokenType::EQUAL:
		case TokenType::QUESTIONMARK_QUESTIONMARK:
		case TokenType::QUESTIONMARK:
		case TokenType::COLON:
		case TokenType::PLUS:
		case TokenType::MINUS:
		case TokenType::SLASH:
		case TokenType::STAR:
		case TokenType::STAR_STAR:
		case TokenType::PERCENT:
		case TokenType::AMPERSAND:
		case TokenType::AMPERSAND_AMPERSAND:
		case TokenType::CARET:
		case TokenType::PIPE:
		case TokenType::PIPE_PIPE:
		case TokenType::BANG:
		case TokenType::EQUAL_EQUAL:
		case TokenType::BANG_EQUAL:
		case TokenType::GREATER_EQUAL:
		case TokenType::LESS_EQUAL:
		case TokenType::GREATER:
		case TokenType::LESS:
		case TokenType::LESS_LESS:
		case TokenType::GREATER_GREATER:
		case TokenType::TILDE:
		case TokenType::PLUS_PLUS:
		case TokenType::MINUS_MINUS:
		case TokenType::MINUS_EQUAL:
		case TokenType::PLUS_EQUAL:
		case TokenType::STAR_EQUAL:
		case TokenType::SLASH_EQUAL:
		case TokenType::DOT:
		case TokenType::DOT_DOT:
		case TokenType::COMMA:
		case TokenType::SEMICOLON:
		case TokenType::LEFT_PARENTHESIS:
		case TokenType::RIGHT_PARENTHESIS:
		case TokenType::LEFT_BRACE:
		case TokenType::RIGHT_BRACE:
		case TokenType::LEFT_BRACKET:
		case TokenType::RIGHT_BRACKET:
		case TokenType::IDENTIFIER:
		case TokenType::STRING:
		case TokenType::CHAR:
		case TokenType::INTEGER:
		case TokenType::FLOAT:
			throw Parser_Token_Error("Unexpected token", token);
	}
}

}