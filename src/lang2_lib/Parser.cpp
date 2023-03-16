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
	this->lexed = true;
}

std::vector<std::shared_ptr<Ast::Node>> Parser::get_nodes() const {
	return nodes;
}

void Parser::parse() {
	if (!lexed) {
		lexer->lex();
		tokens = lexer->get_tokens();
	}

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
			print_location(text, ex.get_row(), ex.get_start_col(),
						   ex.get_end_col());
			std::cerr << RED << ex.what() << std::endl << RESET;
			return;
		}
	}

	// @Todo verify EOF token
}

std::shared_ptr<Ast::Node> Parser::parse_expression() {
	return parse_equality();
}

std::shared_ptr<Ast::Node> Parser::parse_statement() {
	if (is_peek_of_type({TokenType::PRINT})) {
		return parse_print_statement();
	}

	return parse_expression_statement();
}

std::shared_ptr<Ast::Node> Parser::parse_term() {
	using enum Lang::TokenType;

	std::shared_ptr<Ast::Node> expression = parse_factor();

	while(is_peek_of_type({MINUS, PLUS})) {
		auto op = next();
		auto right = parse_factor();
		expression = std::make_shared<Ast::Node>(Ast::Node::binary(expression, right, op));
	}

	return expression;
}

std::shared_ptr<Ast::Node> Parser::parse_factor() {
	using enum Lang::TokenType;

	std::shared_ptr<Ast::Node> expression = parse_unary();

	while(is_peek_of_type({SLASH, STAR})) {
		auto op = next();
		auto right = parse_unary();
		expression = std::make_shared<Ast::Node>(Ast::Node::binary(expression, right, op));
	}

	return expression;
}

std::shared_ptr<Ast::Node> Parser::parse_unary() {
	using enum Lang::TokenType;

	if (is_peek_of_type({MINUS, BANG})) {
		auto op = next();
		auto expression = parse_primary();
		return std::make_shared<Ast::Node>(Ast::Node::unary(expression, op));
	}

	return parse_primary();
}

std::shared_ptr<Ast::Node> Parser::parse_primary() {
	using enum Lang::TokenType;

	auto token = next();
	if (token->type == FALSE || token->type == TRUE)
		return std::make_shared<Ast::Node>(Ast::Node::bool_literal(token));

	if (token->type == NIL)
		return std::make_shared<Ast::Node>(Ast::Node::nil_literal(token));

	if (token->type == INTEGER)
		return std::make_shared<Ast::Node>(Ast::Node::integer_literal(token));

	if (token->type == FLOAT)
		return std::make_shared<Ast::Node>(Ast::Node::float_literal(token));

	if (token->type == STRING)
		return std::make_shared<Ast::Node>(Ast::Node::string_literal(token));

	if (token->type == CHAR)
		return std::make_shared<Ast::Node>(Ast::Node::char_literal(token));

	if (token->type == LEFT_PARENTHESIS) {
		std::shared_ptr<Ast::Node> expression = parse_expression();
		expect(Lang::TokenType::RIGHT_PARENTHESIS);
		return std::make_shared<Ast::Node>(Ast::Node::grouping_statement(expression, token));
	}

	if (token->type == IDENTIFIER) {
		return std::make_shared<Ast::Node>(Ast::Node::identifier(token));
	}

	throw Parser_Token_Error("Unexpected token", token);
}

std::shared_ptr<Ast::Node> Parser::parse_comparison() {
	using enum Lang::TokenType;

	std::shared_ptr<Ast::Node> expression = parse_term();

	while(is_peek_of_type({GREATER_EQUAL, LESS_EQUAL, GREATER, LESS})) {
		auto op = next();
		auto right = parse_term();
		expression = std::make_shared<Ast::Node>(Ast::Node::binary(expression, right, op));
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
		expression = std::make_shared<Ast::Node>(Ast::Node::binary(expression, right, op));
	}

	return expression;
}

void Parser::expect(TokenType type) {
	if (!this->is_peek_of_type({type})) {
		throw Parser_Token_Error(std::string("Expected token of type ") + find_by_value(type), peek());
	}
	next();
}

std::shared_ptr<Ast::Node> Parser::parse_print_statement() {
	auto token = next();
	auto expression = parse_expression();
	expect(TokenType::SEMICOLON);
	auto retval = std::make_shared<Ast::Node>(Ast::Node::print_statement(expression, token));
	return retval;
}

std::shared_ptr<Ast::Node> Parser::parse_expression_statement() {
	auto expression = parse_expression();
	expect(TokenType::SEMICOLON);
	return expression;
}

Parser::Parser(const std::string& text): text(text) {
	this->lexer = std::make_unique<Lexer>(text);
}

}