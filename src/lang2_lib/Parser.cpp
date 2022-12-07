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
		case TokenType::NULL:
		case TokenType::IMPORT:
		case TokenType::INCL:
		case TokenType::AS:
		case TokenType::FN:
		case TokenType::RETURN:
		case TokenType::FAT_ARROW:
		case TokenType::THIN_ARROW:
		case TokenType::ASSN:
		case TokenType::DQM:
		case TokenType::QM:
		case TokenType::COL:
		case TokenType::ADD:
		case TokenType::SUB:
		case TokenType::DIV:
		case TokenType::STAR:
		case TokenType::STARSTAR:
		case TokenType::MOD:
		case TokenType::AMP:
		case TokenType::AND:
		case TokenType::CARET:
		case TokenType::PIPE:
		case TokenType::OR:
		case TokenType::NOT:
		case TokenType::EQ:
		case TokenType::NE:
		case TokenType::GT:
		case TokenType::LT:
		case TokenType::GE:
		case TokenType::LE:
		case TokenType::LSHIFT:
		case TokenType::RSHIFT:
		case TokenType::TILDE:
		case TokenType::INC:
		case TokenType::DEC:
		case TokenType::SUBASSN:
		case TokenType::ADDASSN:
		case TokenType::MULASSN:
		case TokenType::DIVASSN:
		case TokenType::DOT:
		case TokenType::DDOT:
		case TokenType::COMMA:
		case TokenType::SCOL:
		case TokenType::LPAREN:
		case TokenType::RPAREN:
		case TokenType::LBRACE:
		case TokenType::RBRACE:
		case TokenType::LBRACK:
		case TokenType::RBRACK:
		case TokenType::IDENTIFIER:
		case TokenType::LIT_STR:
		case TokenType::LIT_CHR:
		case TokenType::LIT_INT:
		case TokenType::LIT_FLT:
		case TokenType::LIT_BOOL:
			throw Parser_Token_Error("Unexpected token", token);
	}
}

}