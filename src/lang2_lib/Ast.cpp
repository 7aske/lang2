//
// Created by nik on 12/18/22.
//

#include "Ast.h"


const Lang::TokenType& Lang::Ast::Binary_Expression::get_operator() const {
	return this->token.type;
}

const Lang::Ast::Expression& Lang::Ast::Binary_Expression::get_left() const {
	return this->left;
}

const Lang::Ast::Expression& Lang::Ast::Binary_Expression::get_right() const {
	return this->right;
}

void Lang::Ast::Binary_Expression::accept(Visitor& v) {
	v.visit_binary_expression(this);
}

const Lang::Token& Lang::Ast::Expression::get_token() const {
	return this->token;
}
