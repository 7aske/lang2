//
// Created by nik on 12/6/22.
//

#include "gtest/gtest.h"
#include "Parser.h"
#include "Lexer.h"

static std::vector<std::shared_ptr<Lang::Ast::Node>> parse(std::string const& code) {
	Lang::Lexer lexer(code);
	lexer.lex();

	Lang::Parser parser(code, lexer.get_tokens());
	parser.parse();

	return parser.get_nodes();
}

class ParserTest : public ::testing::Test {
};

TEST (ParserTest, ParseEquality) {
	std::string code = "1 == 1;";

	auto nodes = parse(code);

	ASSERT_EQ(1, nodes.size());
	ASSERT_TRUE(nodes[0]->get_type() == Lang::Ast::Node::Type::EQUAL);
	ASSERT_TRUE(nodes[0]->get_token()->type == Lang::TokenType::EQUAL_EQUAL);
}

TEST (ParserTest, ParseAssignment) {
	std::string code = "let a = 1;";

	auto nodes = parse(code);

	ASSERT_EQ(1, nodes.size());
}

TEST (ParserTest, ParseAssignmentConst) {
	std::string code = "const a = 1;";

	auto nodes = parse(code);

	ASSERT_EQ(1, nodes.size());
}

TEST (ParserTest, ParsePrint) {
	std::string code = "print true == true;";

	auto nodes = parse(code);

	ASSERT_EQ(1, nodes.size());
}
