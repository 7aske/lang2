//
// Created by nik on 12/18/22.
//

#include <string>
#include "Ast.h"
#include "Visitor.h"
#include "Utility.h"

void Lang::Ast_Printer::visit_binary_expression(
		Lang::Ast::Binary_Expression* expression) {
	std::string data = parenthesize(find_by_value(expression->get_operator()),
									expression->get_left()->get_token().value,
									expression->get_right()->get_token().value);
	std::cerr << data << std::endl;
	expression->get_left()->accept(*this);
	expression->get_right()->accept(*this);
}

void Lang::Ast_Printer::visit_unary_expression(
		Lang::Ast::Unary_Expression* expression) {
	std::string data = parenthesize(find_by_value(expression->get_token().type),
									expression->get_expression()->get_token().value);
	std::cerr << data << std::endl;
	expression->get_expression()->accept(*this);
}

void Lang::Ast_Printer::visit_primary(Lang::Ast::Primary* expression) {
	std::string data = parenthesize(find_by_value(expression->get_token().type),
									expression->get_token().value);
	std::cerr << data << std::endl;
}

void Lang::Ast_Printer::visit_grouping_expression(
		Lang::Ast::Grouping_Expression* expression) {
	std::cerr << "( ";
	expression->accept(*this);
	std::cerr << " )" << std::endl;
}

void Lang::Ast_Printer::visit_boolean_literal_expression(
		Lang::Ast::Boolean_Literal* pExpression) {
	std::string data = parenthesize("BOOLEAN",
									pExpression->get_token().value);
	std::cerr << data << std::endl;
}

void Lang::Ast_Printer::visit_literal_integer_expression(
		Lang::Ast::Integer_Literal* pExpression) {
	std::string data = parenthesize("INTEGER",
									pExpression->get_token().value);
	std::cerr << data << std::endl;
}

void Lang::Ast_Printer::visit_literal_float_expression(
		Lang::Ast::Float_Literal* pExpression) {
	std::string data = parenthesize("FLOAT",
									pExpression->get_token().value);
	std::cerr << data << std::endl;
}

void Lang::Ast_Printer::visit_literal_nil_expression(
		Lang::Ast::Nil_Literal* pExpression) {
	std::string data = parenthesize("NIL",
									pExpression->get_token().value);
	std::cerr << data << std::endl;
}

void Lang::Ast_Printer::visit_literal_string_expression(
		Lang::Ast::String_Literal* pExpression) {
	std::string data = parenthesize("STRING",
									pExpression->get_token().value);
	std::cerr << data << std::endl;
}

void Lang::Ast_Printer::visit_literal_char_expression(
		Lang::Ast::Char_Literal* pExpression) {
	std::string data = parenthesize("CHAR",
									pExpression->get_token().value);
	std::cerr << data << std::endl;
}
