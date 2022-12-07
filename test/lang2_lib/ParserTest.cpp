//
// Created by nik on 12/6/22.
//

#include "gtest/gtest.h"
#include "Parser.h"
#include "Lexer.h"

class ParserTest : public ::testing::Test {
protected:

	virtual void SetUp() {

	}


};

TEST (ParserTest, Test) {
	char const* text = "1 + 1";

	Lang::Lexer lexer(text);
	lexer.lex();

	Lang::Parser parser(text, lexer.get_tokens());
	parser.parse();

	std::vector<Lang::Ast::Node> nodes = parser.get_nodes();

	ASSERT_EQ(1, nodes.size());
}