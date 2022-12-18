//
// Created by nik on 12/18/22.
//

#ifndef LANG2_VISITOR_H
#define LANG2_VISITOR_H

namespace Lang::Ast {
class Binary_Expression;
}

namespace Lang {

class Visitor {
public:
	virtual void
	visit_binary_expression(Lang::Ast::Binary_Expression* expression) const = 0;
};

class Ast_Printer : public Visitor {
public:
	void visit_binary_expression(
			Lang::Ast::Binary_Expression* expression) const override;
};

}

#endif //LANG2_VISITOR_H