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
									expression->get_left().get_token().value,
									 expression->get_right().get_token().value);
	std::cerr << data << std::endl;
	expression->get_left().accept(*this);
	expression->get_right().accept(*this);
}

void Lang::Ast_Printer::visit_unary_expression(
		Lang::Ast::Unary_Expression* expression) {
	std::string data = parenthesize(find_by_value(expression->get_token().type),
									expression->get_expression().get_token().value);
	std::cerr << data << std::endl;
	expression->get_expression().accept(*this);
}
