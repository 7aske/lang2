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

std::vector<std::shared_ptr<Ast::Expression>> Parser::get_nodes() const {
	return nodes;
}

void Parser::parse() {

	while (has_next()) {
		try {
			nodes.push_back(parse_statement());
		} catch (Parser_Location_Error& ex) {
			std::cerr << MAGENTA << "Error occurred during parsing:" << std::endl << RESET;
			print_location(text, ex.get_row(), ex.get_start_col(),
						   ex.get_end_col());
			std::cerr << RED << ex.what() << std::endl << RESET;
			return;
		} catch (Parser_Token_Error& ex) {
			std::cerr << MAGENTA << "Error occurred during parsing:" << std::endl << RESET;
			print_location(text, ex.get_token().row, ex.get_token().start_char,
						   ex.get_token().end_char);
			std::cerr << RED << ex.what() << std::endl << RESET;
			return;
		}
	}

}

std::unique_ptr<Ast::Expression> Parser::parse_expression() {
	return parse_equality();
}

std::unique_ptr<Ast::Expression> Parser::parse_statement() {
	return parse_expression();
}

std::unique_ptr<Ast::Expression> Parser::parse_term() {
	std::unique_ptr<Ast::Expression> expression = parse_factor();

	while(is_peek_of_type({TokenType::MINUS, TokenType::PLUS})) {
		Token op = next();
		auto right = parse_factor();
		expression = std::make_unique<Ast::Binary_Expression>(*expression, op, *right);
	}

	return expression;
}

std::unique_ptr<Ast::Expression> Parser::parse_factor() {
	std::unique_ptr<Ast::Expression> expression = parse_unary();

	while(is_peek_of_type({TokenType::SLASH, TokenType::STAR})) {
		Token op = next();
		auto right = parse_unary();
		expression = std::make_unique<Ast::Binary_Expression>(*expression, op, *right);
	}

	return expression;
}

std::unique_ptr<Ast::Expression> Parser::parse_unary() {
	if (is_peek_of_type({TokenType::BANG, TokenType::MINUS})) {
		Token op = next();
		auto right = parse_primary();
		return std::make_unique<Ast::Unary_Expression>(op, *right);
	}

	return parse_primary();
}

std::unique_ptr<Ast::Expression> Parser::parse_primary() {
	using enum Lang::TokenType;

	Token token = next();
	if (token.type == FALSE || token.type == TRUE)
		return std::make_unique<Ast::Literal_Expression<bool>>(token, string_to_bool(token.value));

	if (token.type == NIL)
		return std::make_unique<Ast::Literal_Expression<void*>>(token);

	if (token.type == INTEGER)
		return std::make_unique<Ast::Literal_Expression<long>>(token, std::stol(token.value));

	if (token.type == FLOAT)
		return std::make_unique<Ast::Literal_Expression<double>>(token, std::stod(token.value));

	if (token.type == STRING)
		return std::make_unique<Ast::Literal_Expression<std::string>>(token, token.value);

	if (token.type == LEFT_PARENTHESIS) {
		std::unique_ptr<Ast::Expression> expression = parse_expression();
		if (!is_peek_of_type({RIGHT_PARENTHESIS})) {
			throw Parser_Token_Error("Unclosed parenthesis", peek());
		}

		return std::make_unique<Ast::Grouping_Expression>(token, *expression);
	}

	throw Parser_Token_Error("Unexpected token", token);
}

std::unique_ptr<Ast::Expression> Parser::parse_comparison() {
	using enum Lang::TokenType;

	std::unique_ptr<Ast::Expression> expression = parse_term();

	while(is_peek_of_type({GREATER_EQUAL, LESS_EQUAL, GREATER, LESS})) {
		Token op = next();
		auto right = parse_term();
		expression = std::make_unique<Ast::Binary_Expression>(*expression, op, *right);
	}

	return expression;
}

std::unique_ptr<Ast::Expression> Parser::parse_equality() {
	std::unique_ptr<Ast::Expression> expression = parse_comparison();

	while(is_peek_of_type({TokenType::BANG_EQUAL, TokenType::EQUAL_EQUAL})) {
		Token op = next();
		auto right = parse_comparison();
		expression = std::make_unique<Ast::Binary_Expression>(*expression, op, *right);
	}

	return expression;
}

Ast::Expression Parser::create_node(Token token) {
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