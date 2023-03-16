//
// Created by nik on 3/16/23.
//

#include <string>

#include "gtest/gtest.h"
#include "Interpreter.h"
#include "Parser.h"
#include "Lexer.h"

class InterpreterTest : public ::testing::Test {
protected:

	virtual void SetUp() {

	}


};

TEST (InterpreterTest, TestPrint) {
	std::string text = "print \"Hello World\"; print \"\n123\";";

	Lang::Parser parser(text);
	parser.parse();

	auto nodes = parser.get_nodes();
	std::vector<std::shared_ptr<Lang::Interpretable>> interpretables(nodes.begin(), nodes.end());

	Lang::Interpreter interpreter(text, interpretables);
	interpreter.run();
}
