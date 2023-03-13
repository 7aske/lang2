//
// Created by nik on 12/18/22.
//

#include <vector>
#include "Ast.h"


Lang::Ast::Node::Node(std::shared_ptr<Lang::Ast::Node> left,
					  std::shared_ptr<Lang::Ast::Node> right,
					  std::shared_ptr<Lang::Ast::Node> middle,
					  const std::vector<std::shared_ptr<Lang::Ast::Node>>& nodes,
					  Lang::Ast::Node::Type type,
					  const std::shared_ptr<Token> token)
		: left(left)
		  , middle(middle)
		  , right(right)
		  , nodes(nodes)
		  , type(type)
		  , token(token) {}

Lang::Ast::Node::Node(std::shared_ptr<Lang::Ast::Node> left,
					  std::shared_ptr<Lang::Ast::Node> right,
					  Lang::Ast::Node::Type type,
					  const std::shared_ptr<Token> token)
		: left(left)
		  , right(right)
		  , type(type)
		  , token(token) {}

Lang::Ast::Node::Node(std::shared_ptr<Lang::Ast::Node> left,
					  Lang::Ast::Node::Type type,
					  const std::shared_ptr<Token> token)
		: left(left)
		  , type(type)
		  , token(token) {}

Lang::Ast::Node::Node(std::string& value,
					  const std::shared_ptr<Token> token)
		: type(Node::Type::STRING_LITERAL), token(token) {
	this->string_value = value;
}

Lang::Ast::Node::Node(long value,
					  const std::shared_ptr<Token> token)
		: type(Node::Type::STRING_LITERAL), token(token) {
	this->basic_value.integer_value = value;
}

Lang::Ast::Node::Node(double value,
					  const std::shared_ptr<Token> token)
		: type(Node::Type::STRING_LITERAL), token(token) {
	this->basic_value.float_value = value;
}

Lang::Ast::Node::Node(bool value,
					  const std::shared_ptr<Token> token)
		: type(Node::Type::STRING_LITERAL), token(token) {
	this->basic_value.boolean_value = value;
}

Lang::Ast::Node::Node(const std::shared_ptr<Token> token)
		: type(Node::Type::NIL_LITERAL), token(token) {
	this->basic_value.integer_value = 0;
}

Lang::Ast::Node::Node(char value,
					  const std::shared_ptr<Token> token)
		: type(Node::Type::CHAR_LITERAL), token(token) {
	this->basic_value.char_value = value;
}
