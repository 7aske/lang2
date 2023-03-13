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
	std::string text = "1 == 1";

	Lang::Lexer lexer(text);
	lexer.lex();

	Lang::Parser parser(text, lexer.get_tokens());
	parser.parse();

	std::vector<std::shared_ptr<Lang::Ast::Node>> nodes = parser.get_nodes();

	ASSERT_EQ(1, nodes.size());
	ASSERT_TRUE(nodes[0]->type == Lang::Ast::Node::Type::BINARY);
	ASSERT_TRUE(nodes[0]->token->type == Lang::TokenType::EQUAL_EQUAL);
}

TEST (ParserTest, ParseAssignment) {
	std::string text = "let a:i32 = \"test\";";

	Lang::Lexer lexer(text);
	lexer.lex();

	Lang::Parser parser(text, lexer.get_tokens());
	parser.parse();

	std::vector<std::shared_ptr<Lang::Ast::Node>> nodes = parser.get_nodes();

	ASSERT_EQ(1, nodes.size());
}
