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
