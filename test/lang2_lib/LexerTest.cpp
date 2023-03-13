//
// Created by nik on 12/6/22.
//

#include <string>

#include "gtest/gtest.h"
#include "Parser.h"
#include "Lexer.h"

class LexerTest : public ::testing::Test {
protected:

	virtual void SetUp() {

	}


};

TEST (LexerTest, TestBlockComment) {
	std::string text = "/*1 + 1*/";

	Lang::Lexer lexer(text);
	lexer.lex();

	ASSERT_EQ(0, lexer.get_tokens().size());
}

TEST (LexerTest, TestBlockCommentThrow) {
	std::string text = "/*1 + 1";

	Lang::Lexer lexer(text);
	try {
		lexer.lex();
		FAIL();
	} catch (Lang::Lexer_Error& ignored) {
		ASSERT_EQ(ignored.what(), std::string("Unterminated block comment"));
		ASSERT_EQ(0, lexer.get_tokens().size());
	}

}

TEST (LexerTest, TestNestedBlockComment) {
	std::string text = "/*1 + 1 /*This is nested*/ */";

	Lang::Lexer lexer(text);
	lexer.lex();

	ASSERT_EQ(0, lexer.get_tokens().size());
}

TEST (LexerTest, TestLet) {
	std::vector<Lang::Token> tokens;
	std::string text = "let a:i32 = \"test\";";

	Lang::Lexer lexer(text);
	lexer.lex();

	// @formatter:off
	ASSERT_EQ(7, lexer.get_tokens().size());
	ASSERT_EQ(Lang::TokenType::LET,        lexer.get_tokens()[0].type);
	ASSERT_EQ(Lang::TokenType::IDENTIFIER, lexer.get_tokens()[1].type);
	ASSERT_EQ(Lang::TokenType::COLON,      lexer.get_tokens()[2].type);
	ASSERT_EQ(Lang::TokenType::IDENTIFIER, lexer.get_tokens()[3].type);
	ASSERT_EQ(Lang::TokenType::EQUAL,      lexer.get_tokens()[4].type);
	ASSERT_EQ(Lang::TokenType::STRING,     lexer.get_tokens()[5].type);
	ASSERT_EQ(Lang::TokenType::SEMICOLON,  lexer.get_tokens()[6].type);
	// @formatter:on
}
