//
// Created by nik on 12/6/22.
//

#ifndef LANG2_AST_H
#define LANG2_AST_H

#include <utility>
#include <memory>

#include "Token.h"


namespace Lang::Ast {


struct Node {

	enum class Type {
		IDENTIFIER,

		// Literals
		NIL_LITERAL,
		BOOL_LITERAL,
		CHAR_LITERAL,
		STRING_LITERAL,
		INTEGER_LITERAL,
		FLOAT_LITERAL,

		// ternary
		TERNARY,

		// binary
		BINARY,

		// unary
		UNARY,
		NOT,
		MINUS,
		PRE_INCREMENT,
		POST_INCREMENT,
		PRE_DECREMENT,
		POST_DECREMENT,

		FOR,
		BREAK,
		CONTINUE,
		IN,
		ITER,
		WHILE,
		IF,

		BLOCK,
		GROUPING,

		// @Todo type, function declarations
	};

	Node(const std::shared_ptr<Token> token);

	Node(std::shared_ptr<Node> left,
		 std::shared_ptr<Node> middle,
		 std::shared_ptr<Node> right,
		 const std::vector<std::shared_ptr<Node>>& nodes,
		 Type type,
		 const std::shared_ptr<Token> token);

	Node(std::shared_ptr<Node> left,
		 std::shared_ptr<Node> right,
		 Lang::Ast::Node::Type type,
		 const std::shared_ptr<Token> token);

	Node(std::shared_ptr<Node> left,
		 Lang::Ast::Node::Type type,
		 const std::shared_ptr<Token> token);

	Node(std::string& value,
		 const std::shared_ptr<Token> token);

	Node(long value,
		 const std::shared_ptr<Token> token);

	Node(bool value,
		 const std::shared_ptr<Token> token);

	Node(double value,
		 const std::shared_ptr<Token> token);

	Node(char value,
		 const std::shared_ptr<Token> token);

	std::shared_ptr<Node> left = nullptr;
	std::shared_ptr<Node> middle = nullptr;
	std::shared_ptr<Node> right = nullptr;
	std::vector<std::shared_ptr<Node>> nodes;
	Node::Type type;
	std::shared_ptr<Token> token;

	union {
		bool boolean_value;
		long integer_value;
		double float_value;
		char char_value;
	} basic_value;

	std::string string_value;
};

}

#endif //LANG2_AST_H
