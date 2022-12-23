//
// Created by nik on 12/18/22.
//

#ifndef LANG2_VISITOR_H
#define LANG2_VISITOR_H

#include "Ast.h"

namespace Lang::Ast {
class Binary_Expression;

class Unary_Expression;

template<class T>
class Literal_Expression;

class Grouping_Expression;

class Primary;

class Boolean_Literal;

class Char_Literal;

class String_Literal;

class Nil_Literal;

class Integer_Literal;

class Float_Literal;

}


namespace Lang {

class Visitor {
public:
	virtual void
	visit_binary_expression(Lang::Ast::Binary_Expression* expression) = 0;

	virtual void
	visit_unary_expression(Lang::Ast::Unary_Expression* expression) = 0;

	virtual void
	visit_boolean_literal_expression(Lang::Ast::Boolean_Literal* pExpression) = 0;

	virtual void
	visit_literal_integer_expression(Lang::Ast::Integer_Literal* pExpression) = 0;

	virtual void
	visit_literal_float_expression(Lang::Ast::Float_Literal* pExpression) = 0;

	virtual void
	visit_literal_nil_expression(Lang::Ast::Nil_Literal* pExpression) = 0;

	virtual void
	visit_literal_string_expression(Lang::Ast::String_Literal* pExpression) = 0;

	virtual void
	visit_literal_char_expression(Lang::Ast::Char_Literal* pExpression) = 0;

	virtual void visit_primary(Lang::Ast::Primary* pPrimary) = 0;

	virtual void visit_grouping_expression(Lang::Ast::Grouping_Expression* pExpression) = 0;

	virtual ~Visitor() = default;

};

class Ast_Printer : public Visitor {
public:
	void visit_binary_expression(
			Lang::Ast::Binary_Expression* expression) override;

	void visit_unary_expression(Ast::Unary_Expression* expression) override;

	void visit_primary(Lang::Ast::Primary* pPrimary) override;

	void visit_grouping_expression(Lang::Ast::Grouping_Expression* pExpression) override;

	void
	visit_boolean_literal_expression(Lang::Ast::Boolean_Literal* pExpression) override;

	void
	visit_literal_integer_expression(Lang::Ast::Integer_Literal* pExpression) override;

	void
	visit_literal_float_expression(Lang::Ast::Float_Literal* pExpression) override;

	void
	visit_literal_nil_expression(Lang::Ast::Nil_Literal* pExpression) override;

	void
	visit_literal_string_expression(Lang::Ast::String_Literal* pExpression) override;

	void
	visit_literal_char_expression(Lang::Ast::Char_Literal* pExpression) override;
};

}

#endif //LANG2_VISITOR_H