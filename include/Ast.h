//
// Created by nik on 12/6/22.
//

#ifndef LANG2_AST_H
#define LANG2_AST_H

#include <utility>
#include <memory>

#include "Token.h"
#include "Visitor.h"


namespace Lang::Ast {

class Expression {
public:
	[[nodiscard]] Token const& get_token() const;

	virtual ~Expression() = default;

	virtual void accept(Lang::Visitor& v) = 0;

protected:
	explicit Expression(const Token& token)
			: token(token) {}

	// TODO: maybe should be a ptr
	Token token;

};

class Binary_Expression : public Expression {

public:
	Binary_Expression(std::shared_ptr<Expression> left, const Token& token,
					  std::shared_ptr<Expression> right)
			: Expression(token)
			  , left(std::move(left))
			  , right(std::move(right)) {}

	std::shared_ptr<Expression> get_left();

	std::shared_ptr<Expression> get_right();

	TokenType& get_operator();

	void accept(Visitor& v) override;

	~Binary_Expression() override = default;

protected:
	std::shared_ptr<Expression> left;
	std::shared_ptr<Expression> right;
};

class Unary_Expression : public Expression {

public:
	Unary_Expression(Token const& token, std::shared_ptr<Expression> expression)
			: Expression(token)
			  , expression(std::move(expression)) {}

	std::shared_ptr<Expression> get_expression();

	[[nodiscard]] TokenType const& get_operator();

	void accept(Visitor& v) override;

	~Unary_Expression() override = default;

protected:
	std::shared_ptr<Expression> expression;

};

template<typename T>
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

class Boolean_Literal : public Literal_Expression<bool> {
public:
	explicit Boolean_Literal(Token const& token, bool value)
			: Literal_Expression(token, value) {}

	void accept(Visitor& v) override;
};

class Integer_Literal : public Literal_Expression<int> {
public:
	explicit Integer_Literal(Token const& token, int value)
			: Literal_Expression(token, value) {}

	void accept(Visitor& v) override;
};

class Float_Literal : public Literal_Expression<double> {
public:
	explicit Float_Literal(Token const& token, double value)
			: Literal_Expression(token, value) {}

	void accept(Visitor& v) override;
};

class Nil_Literal : public Literal_Expression<void*> {
public:
	explicit Nil_Literal(Token const& token)
			: Literal_Expression(token) {}

	void accept(Visitor& v) override;
};

class String_Literal : public Literal_Expression<std::string> {
public:
	String_Literal(Token const& token, std::string value)
			: Literal_Expression(token, std::move(value)) {}

	void accept(Visitor& v) override;
};

class Char_Literal : public Literal_Expression<char> {
public:
	explicit Char_Literal(Token const& token, char value)
			: Literal_Expression(token, value) {}

	void accept(Visitor& v) override;
};

class Grouping_Expression : public Expression {
public:
	Grouping_Expression(Token const& token,
						std::shared_ptr<Expression> expression)
			: Expression(token)
			  , expression(std::move(expression)) {}


	~Grouping_Expression() override = default;

	void accept(Visitor& v) override;

protected:
	std::shared_ptr<Expression> expression;
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
	explicit Primary(const Token& token, std::shared_ptr<Expression> expression)
			: Expression(token)
			  , expression(std::move(expression)) {}

	~Primary() override = default;

	void accept(Visitor& v) override;

protected:
	std::shared_ptr<Expression> expression;
};

}

#endif //LANG2_AST_H
