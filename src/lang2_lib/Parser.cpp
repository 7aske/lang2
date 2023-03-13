//
// Created by nik on 12/6/22.
//

#include <iostream>

#include "Parser.h"
#include "Utility.h"

namespace Lang {

Parser::Parser(const std::string& text, std::vector<Token> const& tokens)
		: Iterator<std::shared_ptr<Token>>()
		  , text(text)
		  , tokens(tokens) {

	this->iter = this->tokens.begin();
	this->end = this->tokens.end();
	this->nodes.reserve(1024);
}

std::vector<std::shared_ptr<Ast::Node>> Parser::get_nodes() const {
	return nodes;
}

void Parser::parse() {

	while (has_next()) {
		try {
			// @Todo implement synchronization
			//   Synchronizing a recursive decent parser 6.3.3
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

std::shared_ptr<Ast::Node> Parser::parse_expression() {
	return parse_equality();
//	throw Parser_Token_Error("Unsupported operation", peek());
}

std::shared_ptr<Ast::Node> Parser::parse_statement() {
	return parse_expression();
}

std::shared_ptr<Ast::Node> Parser::parse_term() {
	using enum Lang::TokenType;

	std::shared_ptr<Ast::Node> expression = parse_factor();

	while(is_peek_of_type({MINUS, PLUS})) {
		auto op = next();
		auto right = parse_factor();
		expression = std::make_shared<Ast::Node>(expression, right, Ast::Node::Type::BINARY, op);
	}

	return expression;
}

std::shared_ptr<Ast::Node> Parser::parse_factor() {
	using enum Lang::TokenType;

	std::shared_ptr<Ast::Node> expression = parse_unary();

	while(is_peek_of_type({SLASH, STAR})) {
		auto op = next();
		auto right = parse_unary();
		expression = std::make_shared<Ast::Node>(expression, right, Ast::Node::Type::BINARY, op);
	}

	return expression;
}

std::shared_ptr<Ast::Node> Parser::parse_unary() {
	using enum Lang::TokenType;

	if (is_peek_of_type({MINUS})) {
		auto op = next();
		auto right = parse_primary();
		return std::make_shared<Ast::Node>(right, Ast::Node::Type::MINUS, op);
	}

	if (is_peek_of_type({BANG})) {
		auto op = next();
		auto right = parse_primary();
		return std::make_shared<Ast::Node>(right, Ast::Node::Type::NOT, op);
	}

	return parse_primary();
}

std::shared_ptr<Ast::Node> Parser::parse_primary() {
	using enum Lang::TokenType;

	auto token = next();
	if (token->type == FALSE || token->type == TRUE)
		return std::make_shared<Ast::Node>(string_to_bool(token->value), token);

	if (token->type == NIL)
		return std::make_shared<Ast::Node>(token);

	if (token->type == INTEGER)
		return std::make_shared<Ast::Node>(std::stol(token->value), token);

	if (token->type == FLOAT)
		return std::make_shared<Ast::Node>(std::stod(token->value), token);

	if (token->type == STRING)
		return std::make_shared<Ast::Node>(token->value, token);

	if (token->type == CHAR)
		return std::make_shared<Ast::Node>(token->value[0], token);

	if (token->type == LEFT_PARENTHESIS) {
		std::shared_ptr<Ast::Node> expression = parse_expression();
		if (!is_peek_of_type({RIGHT_PARENTHESIS})) {
			throw Parser_Token_Error("Unclosed parenthesis", peek());
		}

		return std::make_shared<Ast::Node>(expression, Ast::Node::Type::GROUPING, token);
	}

	throw Parser_Token_Error("Unexpected token", token);
}

std::shared_ptr<Ast::Node> Parser::parse_comparison() {
	using enum Lang::TokenType;

	std::shared_ptr<Ast::Node> expression = parse_term();

	while(is_peek_of_type({GREATER_EQUAL, LESS_EQUAL, GREATER, LESS})) {
		auto op = next();
		auto right = parse_term();
		expression = std::make_shared<Ast::Node>(expression, right, Ast::Node::Type::BINARY, op);
	}

	return expression;
}

std::shared_ptr<Ast::Node> Parser::parse_equality() {
	using enum Lang::TokenType;

	// Was parse comparison
	std::shared_ptr<Ast::Node> expression = parse_comparison();

	while(is_peek_of_type({BANG_EQUAL, EQUAL_EQUAL})) {
		auto op = next();
		// Was parse comparison
		auto right = parse_comparison();
		expression = std::make_shared<Ast::Node>(expression, right, Ast::Node::Type::BINARY, op);
	}

	return expression;
}

std::shared_ptr<Ast::Node> Parser::parse_ternary_expression() {
	auto expression = parse_expression();

	return expression;
}

}