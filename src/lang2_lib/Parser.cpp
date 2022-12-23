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

std::shared_ptr<Ast::Expression> Parser::parse_expression() {
	return parse_equality();
}

std::shared_ptr<Ast::Expression> Parser::parse_statement() {
	return parse_expression();
}

std::shared_ptr<Ast::Expression> Parser::parse_term() {
	using enum Lang::TokenType;

	std::shared_ptr<Ast::Expression> expression = parse_factor();

	while(is_peek_of_type({MINUS, PLUS})) {
		Token op = next();
		auto right = parse_factor();
		expression = std::make_shared<Ast::Term>(expression, op, right);
	}

	return expression;
}

std::shared_ptr<Ast::Expression> Parser::parse_factor() {
	using enum Lang::TokenType;

	std::shared_ptr<Ast::Expression> expression = parse_unary();

	while(is_peek_of_type({SLASH, STAR})) {
		Token op = next();
		auto right = parse_unary();
		expression = std::make_shared<Ast::Factor>(expression, op, right);
	}

	return expression;
}

std::shared_ptr<Ast::Expression> Parser::parse_unary() {
	using enum Lang::TokenType;

	if (is_peek_of_type({MINUS})) {
		Token op = next();
		auto right = parse_primary();
		return std::make_shared<Ast::Minus>(op, right);
	}

	if (is_peek_of_type({BANG})) {
		Token op = next();
		auto right = parse_primary();
		return std::make_shared<Ast::Negation>(op, right);
	}

	return parse_primary();
}

std::shared_ptr<Ast::Expression> Parser::parse_primary() {
	using enum Lang::TokenType;

	Token token = next();
	if (token.type == FALSE || token.type == TRUE)
		return std::make_shared<Ast::Boolean_Literal>(token, string_to_bool(token.value));

	if (token.type == NIL)
		return std::make_shared<Ast::Nil_Literal>(token);

	if (token.type == INTEGER)
		return std::make_shared<Ast::Integer_Literal>(token, std::stol(token.value));

	if (token.type == FLOAT)
		return std::make_shared<Ast::Float_Literal>(token, std::stod(token.value));

	if (token.type == STRING)
		return std::make_shared<Ast::String_Literal>(token, token.value);

	if (token.type == CHAR)
		return std::make_shared<Ast::Char_Literal>(token, token.value[0]);

	if (token.type == LEFT_PARENTHESIS) {
		std::shared_ptr<Ast::Expression> expression = parse_expression();
		if (!is_peek_of_type({RIGHT_PARENTHESIS})) {
			throw Parser_Token_Error("Unclosed parenthesis", peek());
		}

		return std::make_shared<Ast::Grouping_Expression>(token, expression);
	}

	throw Parser_Token_Error("Unexpected token", token);
}

std::shared_ptr<Ast::Expression> Parser::parse_comparison() {
	using enum Lang::TokenType;

	std::shared_ptr<Ast::Expression> expression = parse_term();

	while(is_peek_of_type({GREATER_EQUAL, LESS_EQUAL, GREATER, LESS})) {
		Token op = next();
		auto right = parse_term();
		expression = std::make_shared<Ast::Binary_Expression>(expression, op, right);
	}

	return expression;
}

std::shared_ptr<Ast::Expression> Parser::parse_equality() {
	using enum Lang::TokenType;

	std::shared_ptr<Ast::Expression> expression = parse_comparison();

	while(is_peek_of_type({BANG_EQUAL, EQUAL_EQUAL})) {
		Token op = next();
		auto right = parse_comparison();
		expression = std::make_shared<Ast::Binary_Expression>(expression, op, right);
	}

	return expression;
}

}