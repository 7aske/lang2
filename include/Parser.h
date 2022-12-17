//
// Created by nik on 12/6/22.
//

#ifndef LANG2_PARSER_H
#define LANG2_PARSER_H

#include <vector>

#include "Token.h"
#include "Iterator.h"
#include "Ast.h"

namespace Lang {

class Parser : public Iterator<Token> {
	using iterator = std::vector<Token>::const_iterator;
public:
	Parser(std::string const& text, std::vector<Token> const& tokens);
	virtual ~Parser() = default;

	void parse();

	Ast::Node parse_expression();

	[[nodiscard]] std::vector<Ast::Node> get_nodes() const;

	Token next() override {
		if (!has_next())
			throw std::range_error("Index out of range");
		return *(iter++);
	}

	inline void skip(int i) override {
		iter += i;
	}

	inline Token peek() override {
		return *iter;
	}

	inline Token offset(int offset) override {
		return *(iter + offset);
	}

	inline bool has_next() override {
		return iter < end;
	}

private:
	std::string const& text;
	iterator iter;
	iterator end;
	std::vector<Token> tokens;
	std::vector<Ast::Node> nodes;

	Ast::Node parse_statement();

	Ast::Node create_node(Token token);
};


class Parser_Error : public std::exception {
public:
	explicit Parser_Error(const char* msg)
			: msg(msg) {}

	[[nodiscard]] const char*
	what() const _GLIBCXX_TXN_SAFE_DYN _GLIBCXX_NOTHROW override {
		return msg;
	}

protected:
	const char* msg;
};

class Parser_Token_Error : public Parser_Error {
public:
	Parser_Token_Error(const char* msg, const Token& token)
			: Parser_Error(msg), token(token) {}

	[[nodiscard]] const Token& get_token() const { return token; }

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

	[[nodiscard]] int get_row() const { return row; }

	[[nodiscard]] int get_start_col() const { return start_col; }

	[[nodiscard]] int get_end_col() const { return end_col; }

protected:
	const int row;
	const int start_col;
	const int end_col;
};

}

#endif //LANG2_PARSER_H
