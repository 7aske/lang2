//
// Created by nik on 12/18/22.
//

#ifndef LANG2_VISITOR_H
#define LANG2_VISITOR_H

#include "Ast.h"

namespace Lang::Ast {
class Binary_Expression;

class Unary_Expression;
}

namespace Lang {

class Visitor {
public:
	virtual void
	visit_binary_expression(Lang::Ast::Binary_Expression* expression) = 0;

	virtual void
	visit_unary_expression(Lang::Ast::Unary_Expression* expression) = 0;

	virtual ~Visitor() = default;
};

class Ast_Printer : public Visitor {
public:
	void visit_binary_expression(
			Lang::Ast::Binary_Expression* expression) override;

	void visit_unary_expression(Ast::Unary_Expression* expression) override;
};

}

#endif //LANG2_VISITOR_H