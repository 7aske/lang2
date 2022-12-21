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

	virtual ~Expression() = default;

	virtual void accept(Lang::Visitor& v) { /* stub */ };

protected:
	explicit Expression(const Token& token)
			: token(token) {}

	Token token;

};

class Binary_Expression : public Expression {

public:
	Binary_Expression(Expression const& left, const Token& token,
					  Expression const& right)
			: Expression(token)
			  , left(left)
			  , right(right) {}

	[[nodiscard]] Expression& get_left();

	[[nodiscard]] Expression& get_right();

	[[nodiscard]] TokenType& get_operator();

	void accept(Visitor& v) override;

	~Binary_Expression() override = default;

protected:
	Expression left;
	Expression right;
};

class Unary_Expression : public Expression {

public:
	Unary_Expression(Token const& token, Expression const& expression)
			: Expression(token)
			  , expression(expression) {}

	[[nodiscard]] Expression& get_expression();

	[[nodiscard]] TokenType const& get_operator();

	void accept(Visitor& v) override;

	~Unary_Expression() override = default;

protected:
	Expression expression;

};

template<class T>
class Literal_Expression : public Expression {
public:
	Literal_Expression(Token const& token, T value)
			: Expression(token)
			  , value(std::move(value)) {}

	explicit Literal_Expression(Token const& token)
		: Expression(token) {}

	~Literal_Expression() override = default;

protected:
	T value;
};

class Grouping_Expression : public Expression {
public:
	Grouping_Expression(Token const& token, Expression const& expression)
			: Expression(token)
			  , expression(expression) {}


	~Grouping_Expression() override = default;

protected:
	Expression expression;
};

class Equality : public Binary_Expression {
public:
	using Binary_Expression::Binary_Expression;

	~Equality() override = default;
};

class Comparison : public Binary_Expression {
public:
	using Binary_Expression::Binary_Expression;

	~Comparison() override = default;
};

class Term : public Binary_Expression {
public:
	using Binary_Expression::Binary_Expression;

	~Term() override = default;
};

class Factor : public Binary_Expression {
public:
	using Binary_Expression::Binary_Expression;

	~Factor() override = default;
};

class Negation : public Unary_Expression {
public:
	using Unary_Expression::Unary_Expression;

	~Negation() override = default;
};

class Minus : public Unary_Expression {
public:
	using Unary_Expression::Unary_Expression;

	~Minus() override = default;
};

class Primary : public Expression {
public:
	explicit Primary(const Token& token, Expression const& expression)
			: Expression(token)
			  , expression(expression) {}

	~Primary() override = default;

protected:
	Expression expression;
};

}

#endif //LANG2_AST_H
