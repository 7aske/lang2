//
// Created by nik on 12/6/22.
//

#ifndef LANG2_AST_H
#define LANG2_AST_H

#include <utility>
#include <cstdint>
#include <memory>

#include "Token.h"


namespace Lang::Ast {


struct Node {

	enum class Type {
		INVALID = -1,
		IDENTIFIER,

		// Literals
		NIL_LITERAL,
		BOOL_LITERAL,
		CHAR_LITERAL,
		STRING_LITERAL,
		INTEGER_LITERAL,
		FLOAT_LITERAL,
		// @Todo double literal

		// Ternary
		TERNARY,

		// Binary
		ADDITION,
		SUBTRACTION,
		MULTIPLICATION,
		DIVISION,
		MODULO,
		POWER,
		EQUAL,
		NOT_EQUAL,
		GREATER_THAN,
		LESS_THAN,
		GREATER_THAN_EQUAL,
		LESS_THAN_EQUAL,

		// Unary
		NOT,
		MINUS,
		PRE_INCREMENT,
		POST_INCREMENT,
		PRE_DECREMENT,
		POST_DECREMENT,

		// Statements
		FUNCTION,
		IF,
		FOR,
		WHILE,
		DECLARATION,
		RETURN,
		// @Todo CLASS,

		// misc
		BREAK,
		CONTINUE,
		// @Todo IN,

		// Composite
		BLOCK,
		GROUPING,

		// @Todo type, function declarations
	};


	static Lang::Ast::Node identifier(std::shared_ptr<Token> token);

	static Lang::Ast::Node nil_literal(std::shared_ptr<Token> token);
	static Lang::Ast::Node bool_literal(std::shared_ptr<Token> token);
	static Lang::Ast::Node char_literal(std::shared_ptr<Token> token);
	static Lang::Ast::Node string_literal(std::shared_ptr<Token> token);
	static Lang::Ast::Node integer_literal(std::shared_ptr<Token> token);
	static Lang::Ast::Node float_literal(std::shared_ptr<Token> token);

	static Lang::Ast::Node ternary(std::shared_ptr<Token> token);
	static Lang::Ast::Node binary(std::shared_ptr<Lang::Ast::Node> left,
								  std::shared_ptr<Lang::Ast::Node> right,
								  std::shared_ptr<Token> token);
	static Lang::Ast::Node unary(std::shared_ptr<Lang::Ast::Node> left,
								 std::shared_ptr<Token> token);

	static Lang::Ast::Node function_statement(std::shared_ptr<Token> token);
	static Lang::Ast::Node if_statement(std::shared_ptr<Token> token);
	static Lang::Ast::Node return_statement(std::shared_ptr<Token> token);
	static Lang::Ast::Node break_statement(std::shared_ptr<Token> token);
	static Lang::Ast::Node continue_statement(std::shared_ptr<Token> token);

	static Lang::Ast::Node grouping_statement(std::shared_ptr<Node> expression,
											  std::shared_ptr<Token> token);


	Node(std::shared_ptr<Lang::Ast::Node> left,
						  std::shared_ptr<Lang::Ast::Node> right,
						  std::shared_ptr<Lang::Ast::Node> middle,
						  const std::vector<std::shared_ptr<Lang::Ast::Node>>& nodes,
						  Lang::Ast::Node::Type type,
						  const std::shared_ptr<Token> token);

	Node::Type get_type() const { return type; };
	std::shared_ptr<Token> get_token() const { return token; };
	std::shared_ptr<Node> get_left() const { return left; };
	std::shared_ptr<Node> get_middle() const { return left; };
	std::shared_ptr<Node> get_right() const { return left; };
	const std::vector<std::shared_ptr<Node>>& get_nodes() const { return nodes; };
	int64_t integer_value() const { return basic_value.integer_value; }
	double float_value() const { return basic_value.float_value; }
	char char_value() const { return basic_value.char_value; }
	long boolean_value() const { return basic_value.boolean_value; }
	const std::string& get_string_value() const { return string_value; }
	const std::string& name() const { return string_value; }

private:

	Node::Type type;
	std::shared_ptr<Token> token;
	std::shared_ptr<Node> left = nullptr;
	std::shared_ptr<Node> middle = nullptr;
	std::shared_ptr<Node> right = nullptr;
	std::vector<std::shared_ptr<Node>> nodes;

	union {
		long integer_value;
		double float_value;
		char char_value;
		bool boolean_value;
	} basic_value;

	std::string string_value;
};

}

#endif //LANG2_AST_H
