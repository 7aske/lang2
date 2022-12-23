//
// Created by nik on 12/18/22.
//

#include "Ast.h"


Lang::TokenType& Lang::Ast::Binary_Expression::get_operator() {
	return this->token.type;
}

std::shared_ptr<Lang::Ast::Expression> Lang::Ast::Binary_Expression::get_left() {
	return this->left;
}

std::shared_ptr<Lang::Ast::Expression> Lang::Ast::Binary_Expression::get_right() {
	return this->right;
}

void Lang::Ast::Binary_Expression::accept(Visitor& v) {
	v.visit_binary_expression(this);
}

const Lang::Token& Lang::Ast::Expression::get_token() const {
	return this->token;
}

std::shared_ptr<Lang::Ast::Expression>
Lang::Ast::Unary_Expression::get_expression() {
	return this->expression;
}

const Lang::TokenType& Lang::Ast::Unary_Expression::get_operator() {
	return this->token.type;
}

void Lang::Ast::Unary_Expression::accept(Lang::Visitor& v) {
	v.visit_unary_expression(this);
}

void Lang::Ast::Grouping_Expression::accept(Lang::Visitor& v) {
	v.visit_grouping_expression(this);
}

void Lang::Ast::Primary::accept(Lang::Visitor& v) {
	v.visit_primary(this);
}

void Lang::Ast::Char_Literal::accept(Lang::Visitor& v) {
	v.visit_literal_char_expression(this);
}

void Lang::Ast::String_Literal::accept(Lang::Visitor& v) {
	v.visit_literal_string_expression(this);
}

void Lang::Ast::Nil_Literal::accept(Lang::Visitor& v) {
	v.visit_literal_nil_expression(this);
}

void Lang::Ast::Float_Literal::accept(Lang::Visitor& v) {
	v.visit_literal_float_expression(this);
}

void Lang::Ast::Integer_Literal::accept(Lang::Visitor& v) {
	v.visit_literal_integer_expression(this);
}

void Lang::Ast::Boolean_Literal::accept(Lang::Visitor& v) {
	v.visit_boolean_literal_expression(this);
}
