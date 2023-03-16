//
// Created by nik on 3/16/23.
//

#ifndef LANG2_INTERPRETER_H
#define LANG2_INTERPRETER_H

#include <memory>
#include <vector>
#include <iostream>
#include <any>
#include "Token.h"
#include "Utility.h"

namespace Lang {
class Node;

class Interpreter;

class Interpreter_Error : public std::exception {
public:
	explicit Interpreter_Error(const std::string& msg)
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


class Interpreter_Token_Error : public Interpreter_Error {
public:
	Interpreter_Token_Error(const char* msg, std::shared_ptr<Token> token)
			: Interpreter_Error(msg), token(*token) {}

	Interpreter_Token_Error(const std::string& msg,
							std::shared_ptr<Token> token)
			: Interpreter_Error(msg), token(*token) {}

	[[nodiscard]] int get_row() const override { return token.row; }

	[[nodiscard]] int
	get_start_col() const override { return token.start_char; }

	[[nodiscard]] int get_end_col() const override { return token.end_char; }

protected:
	const Token token;
};

class Interpretable {
public:
	virtual std::any interpret(Interpreter* interpreter) = 0;
};

class Interpreter {
public:
	explicit Interpreter(const std::string& text,
						 const std::vector<std::shared_ptr<Interpretable>>& interpretables)
			: text(text)
			  , interpretables(interpretables) {}

	void run();

private:
	std::string text;
	std::vector<std::shared_ptr<Interpretable>> interpretables;
};

}

#endif //LANG2_INTERPRETER_H
