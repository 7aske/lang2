//
// Created by nik on 12/18/22.
//

#include "Ast.h"


Lang::TokenType& Lang::Ast::Binary_Expression::get_operator() {
	return this->token.type;
}

Lang::Ast::Expression& Lang::Ast::Binary_Expression::get_left() {
	return this->left;
}

Lang::Ast::Expression& Lang::Ast::Binary_Expression::get_right() {
	return this->right;
}

void Lang::Ast::Binary_Expression::accept(Visitor& v) {
	v.visit_binary_expression(this);
}

const Lang::Token& Lang::Ast::Expression::get_token() const {
	return this->token;
}

Lang::Ast::Expression&
Lang::Ast::Unary_Expression::get_expression() {
	return this->expression;
}

const Lang::TokenType& Lang::Ast::Unary_Expression::get_operator() {
	return this->token.type;
}

void Lang::Ast::Unary_Expression::accept(Lang::Visitor& v) {
	v.visit_unary_expression(this);
}
