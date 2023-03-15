//
// Created by nik on 12/18/22.
//

#include <vector>
#include "Ast.h"
#include "Utility.h"


Lang::Ast::Node::Node(std::shared_ptr<Lang::Ast::Node> left,
					  std::shared_ptr<Lang::Ast::Node> right,
					  std::shared_ptr<Lang::Ast::Node> middle,
					  const std::vector<std::shared_ptr<Lang::Ast::Node>>& nodes,
					  Lang::Ast::Node::Type type,
					  const std::shared_ptr<Token> token)
		: type(type)
		  , token(token)
		  , left(left)
		  , middle(middle)
		  , right(right)
		  , nodes(nodes) {}


Lang::Ast::Node Lang::Ast::Node::identifier(std::shared_ptr<Token> token) {
	return Node(nullptr,
				nullptr,
				nullptr,
				{},
				Type::IDENTIFIER,
				token);
}

Lang::Ast::Node Lang::Ast::Node::binary(std::shared_ptr<Lang::Ast::Node> left,
										std::shared_ptr<Lang::Ast::Node> right,
										std::shared_ptr<Token> token) {
	using enum Lang::TokenType;

	Node::Type type = Node::Type::INVALID;
	switch (token->type) {
		case MINUS:
			type = Type::SUBTRACTION;
			break;
		case PLUS:
			type = Type::ADDITION;
			break;
		case STAR:
			type = Type::MULTIPLICATION;
			break;
		case SLASH:
			type = Type::DIVISION;
			break;
		case PERCENT:
			type = Type::MODULO;
			break;
		case STAR_STAR:
			type = Type::POWER;
			break;
		case GREATER:
			type = Type::GREATER_THAN;
			break;
		case LESS:
			type = Type::LESS_THAN;
			break;
		case GREATER_EQUAL:
			type = Type::GREATER_THAN_EQUAL;
			break;
		case LESS_EQUAL:
			type = Type::LESS_THAN_EQUAL;
			break;
		case EQUAL_EQUAL:
			type = Type::EQUAL;
			break;
		case BANG_EQUAL:
			type = Type::NOT_EQUAL;
			break;

		// @Todo binary number operations

	}

	return Lang::Ast::Node(left,
						   right,
						   nullptr,
						   {},
						   type,
						   token);
}

Lang::Ast::Node Lang::Ast::Node::unary(std::shared_ptr<Lang::Ast::Node> left,
									   std::shared_ptr<Token> token) {

	using enum Lang::TokenType;

	Node::Type type = Node::Type::INVALID;
	switch (token->type) {
		case MINUS:
			type = Type::MINUS;
			break;
		case BANG:
			type = Type::NOT;
			break;

	}

	return Lang::Ast::Node(left,
						   nullptr,
						   nullptr,
						   {},
						   type,
						   token);
}

Lang::Ast::Node
Lang::Ast::Node::grouping_statement(std::shared_ptr<Node> expression,
									std::shared_ptr<Token> token) {
	return Lang::Ast::Node(expression,
						   nullptr,
						   nullptr,
						   {},
						   Node::Type::GROUPING,
						   token);
}

Lang::Ast::Node Lang::Ast::Node::nil_literal(std::shared_ptr<Token> token) {
	auto node = Lang::Ast::Node(nullptr,
						   nullptr,
						   nullptr,
						   {},
						   Node::Type::NIL_LITERAL,
						   token);
	node.basic_value = {};
	return node;
}

Lang::Ast::Node Lang::Ast::Node::bool_literal(std::shared_ptr<Token> token) {
	auto node = Lang::Ast::Node(nullptr,
								   nullptr,
								   nullptr,
								   {},
								   Node::Type::NIL_LITERAL,
								   token);
	node.basic_value.boolean_value = string_to_bool(token->value);
	return node;
}

Lang::Ast::Node Lang::Ast::Node::char_literal(std::shared_ptr<Token> token) {
	auto node = Lang::Ast::Node(nullptr,
								nullptr,
								nullptr,
								{},
								Node::Type::NIL_LITERAL,
								token);
	node.basic_value.char_value = token->value[0];
	return node;
}

Lang::Ast::Node Lang::Ast::Node::string_literal(std::shared_ptr<Token> token) {
	auto node = Lang::Ast::Node(nullptr,
								nullptr,
								nullptr,
								{},
								Node::Type::NIL_LITERAL,
								token);
	node.string_value = token->value;
	return node;
}

Lang::Ast::Node Lang::Ast::Node::integer_literal(std::shared_ptr<Token> token) {
	auto node = Lang::Ast::Node(nullptr,
								nullptr,
								nullptr,
								{},
								Node::Type::NIL_LITERAL,
								token);
	node.basic_value.integer_value = std::stoll(token->value);
	return node;
}

Lang::Ast::Node Lang::Ast::Node::float_literal(std::shared_ptr<Token> token) {
	auto node = Lang::Ast::Node(nullptr,
								nullptr,
								nullptr,
								{},
								Node::Type::NIL_LITERAL,
								token);
	node.basic_value.float_value = std::stod(token->value);
	return node;
}
