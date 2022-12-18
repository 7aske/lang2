//
// Created by nik on 12/6/22.
//

#ifndef LANG2_AST_H
#define LANG2_AST_H

#include "Token.h"
#include "Visitor.h"


namespace Lang::Ast {

class Expression {
public:
	[[nodiscard]] Token const& get_token() const;

protected:
	explicit Expression(const Token& token)
			: token(token) {}

	Token token;

	virtual void accept(Lang::Visitor& v) { /* stub */ };
};

class Binary_Expression : public Expression {

public:
	Binary_Expression(Expression& left, const Token& token, Expression& right)
			: Expression(token)
			  , left(std::move(left))
			  , right(std::move(right)) {}

	[[nodiscard]] Expression const& get_left() const;

	[[nodiscard]] Expression const& get_right() const;

	[[nodiscard]] TokenType const& get_operator() const;

	void accept(Visitor& v) override;

protected:
	Expression left;
	Expression right;
};

}

#endif //LANG2_AST_H
