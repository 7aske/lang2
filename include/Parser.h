//
// Created by nik on 12/6/22.
//

#ifndef LANG2_PARSER_H
#define LANG2_PARSER_H

#include <vector>
#include <memory>
#include <algorithm>

#include "Token.h"
#include "Iterator.h"
#include "Ast.h"

namespace Lang {

class Parser : public Iterator<std::shared_ptr<Token>> {
	using iterator = std::vector<Token>::const_iterator;
public:
	explicit Parser(std::string const& text, std::vector<Token> const& tokens);

	virtual ~Parser() = default;

	void parse();

	[[nodiscard]] std::vector<std::shared_ptr<Ast::Node>>
	get_nodes() const;

	std::shared_ptr<Token> next() override {
		if (!has_next())
			throw std::range_error("Index out of range");
		return std::make_shared<Token>(*(iter++));
	}

	inline void skip(int i) override {
		iter += i;
	}

	inline std::shared_ptr<Token> peek() override {
		return std::make_shared<Token>(*iter);
	}

	inline bool
	is_peek_of_type(std::initializer_list<TokenType> const& token_types) {
		if (!has_next()) return false;
		return std::find(token_types.begin(), token_types.end(), peek()->type) !=
			   token_types.end();
	}

	inline std::shared_ptr<Token> offset(int offset) override {
		return std::make_shared<Token>(*(iter + offset));
	}

	inline bool has_next() override {
		return iter < end;
	}

private:
	std::string const& text;
	iterator iter;
	iterator end;
	std::vector<Token> tokens;

	std::vector<std::shared_ptr<Ast::Node>> nodes;

	void expect(TokenType type);

	std::shared_ptr<Ast::Node> parse_statement();

	std::shared_ptr<Ast::Node> parse_expression();

	std::shared_ptr<Ast::Node> parse_comparison();

	std::shared_ptr<Ast::Node> parse_term();

	std::shared_ptr<Ast::Node> parse_factor();

	std::shared_ptr<Ast::Node> parse_unary();

	std::shared_ptr<Ast::Node> parse_primary();

	std::shared_ptr<Ast::Node> parse_equality();

	std::shared_ptr<Ast::Node> parse_print_statement();

	std::shared_ptr<Ast::Node> parse_expression_statement();
};


class Parser_Error : public std::exception {
public:
	explicit Parser_Error(const std::string& msg)
			: msg(msg) {}

	[[nodiscard]] const char*
	what() const _GLIBCXX_TXN_SAFE_DYN _GLIBCXX_NOTHROW override {
		return msg.c_str();
	}

	virtual int get_row() const = 0;

	virtual int get_start_col() const = 0;

	virtual int get_end_col() const = 0;

private:
	std::string msg;
};

class Parser_Token_Error : public Parser_Error {
public:
	Parser_Token_Error(const char* msg, std::shared_ptr<Token> token)
			: Parser_Error(msg), token(*token) {}

	Parser_Token_Error(const std::string& msg, std::shared_ptr<Token> token)
			: Parser_Error(msg), token(*token) {}

	[[nodiscard]] int get_row() const override { return token.row; }

	[[nodiscard]] int get_start_col() const override { return token.start_char; }

	[[nodiscard]] int get_end_col() const override { return token.end_char; }

protected:
	const Token token;
};

class Parser_Location_Error : public Parser_Error {
public:
	Parser_Location_Error(const char* msg, int row, int start_col, int end_col)
			: Parser_Error(msg)
			  , row(row)
			  , start_col(start_col)
			  , end_col(end_col) {}

	[[nodiscard]] int get_row() const override { return row; }

	[[nodiscard]] int get_start_col() const override { return start_col; }

	[[nodiscard]] int get_end_col() const override { return end_col; }

protected:
	const int row;
	const int start_col;
	const int end_col;
};

}

#endif //LANG2_PARSER_H
