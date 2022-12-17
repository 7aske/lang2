//
// Created by nik on 12/1/22.
//

#include "Lexer.h"

namespace Lang {

Lexer::Lexer(std::string const& text) : Indexed_Char_Iterator(text) {
	this->buffer.reserve(max_identifier_length);
	this->tokens.reserve(2048);
}

void Lang::Lexer::do_lex() {

	while (has_next()) {
		if (isspace(peek())) {
			next();
		} else if (is_startof_block_comment()) {
			parse_block_comment();
		} else if (is_startof_line_comment()) {
			while (has_next() && peek() != '\n') {
				next();
			}
		} else if (is_startof_number()) {
			auto token = parse_number();
			emit_token(token);
		} else if (is_startof_char()) {
			auto token = parse_char();
			emit_token(token);
		} else if (is_startof_string()) {
			auto token = parse_string();
			emit_token(token);
		} else if (is_startof_identifier()) {
			auto token = parse_keyword();
			emit_token(token);
		} else {
			auto type = parse_operator();

			auto keyword = types.at(type);

			int offset = 1;
			if (type != TokenType::INVALID) {
				offset = (int) strlen(keyword);
			}

			auto token = Token(type,
							   keyword,
							   row,
							   col - offset,
							   col);

			emit_token(token);
		}
	}

}

inline bool Lang::Lexer::is_startof_line_comment() {
	return peek() == '/' && offset(1) == '/';
}


TokenType Lexer::parse_operator() {
	using enum Lang::TokenType;

	char c = next();
	if (c == '!') {
		if (peek() == '=') {
			next();
			return NE;
		} else {
			return NOT;
		}
	}

	if (c == '%') { return MOD; }
	if (c == '&') {
		if (peek() == '&') {
			next();
			return AND;
		} else {
			return AMP;
		}
	}

	if (c == '(') {
		return LPAREN;
	}
	if (c == ')') {
		return RPAREN;
	}
	if (c == '*') {
		if (peek() == '=') {
			next();
			return MULASSN;
		} else if (peek() == '*') {
			next();
			return STARSTAR;
		} else {
			return STAR;
		}
	}
	if (c == '+') {
		if (peek() == '+') {
			next();
			return INC;
		} else if (peek() == '=') {
			next();
			return ADDASSN;
		} else {
			return ADD;
		}
	}
	if (c == ',') {
		return COMMA;
	}
	if (c == '-') {
		if (peek() == '-') {
			next();
			return DEC;
		} else if (peek() == '=') {
			next();
			return SUBASSN;
		} else if (peek() == '>') {
			next();
			return THIN_ARROW;
		} else {
			return SUB;
		}
	}
	if (c == '.') {
		if (peek() == '.') {
			next();
			return DDOT;
		} else {
			return DOT;
		}
	}
	if (c == '/') {
		if (peek() == '=') {
			next();
			return DIVASSN;
		} else {
			return DIV;
		}
	}
	if (c == ':') {
		return COL;
	}
	if (c == ';') {
		return SCOL;
	}
	if (c == '<') {
		if (peek() == '=') {
			next();
			return LE;
		} else {
			return LT;
		}
	}
	if (c == '=') {
		if (peek() == '=') {
			next();
			return EQ;
		} else if (peek() == '>') {
			next();
			return FAT_ARROW;
		} else {
			return ASSN;
		}
	}
	if (c == '>') {
		if (peek() == '=') {
			next();
			return GE;
		} else {
			return GT;
		}
	}

	if (c == '?') {
		if (peek() == '?') {
			next();
			return DQM;
		} else {
			return QM;
		}
	}

	if (c == '[') {
		return LBRACK;
	}
	if (c == ']') {
		return RBRACK;
	}
	if (c == '{') {
		return LBRACE;
	}
	if (c == '|') {
		if (peek() == '|') {
			next();
			return OR;
		} else {
			return PIPE;
		}
	}
	if (c == '}') {
		return RBRACE;
	}

	return INVALID;
}

Token Lang::Lexer::parse_keyword() {
	buffer.erase();

	while (isalnum(peek()) || peek() == '#' || peek() == '$' || peek() == '_') {
		buffer.push_back(next());
	}

	auto type = find_by_value(buffer.c_str());

	return {type == TokenType::INVALID
			? TokenType::IDENTIFIER
			: type,
			buffer, row, col - (int) buffer.size(), col};

}

inline bool Lang::Lexer::is_startof_identifier() {
	char c = peek();
	return isalpha(c) || c == '$' || c == '_';
}

void Lang::Lexer::emit_token(const Token &token) {
	// std::cout << token << std::endl;
	if (token.type == TokenType::INVALID) {
		throw Lexer_Token_Error("Unexpected token", token);
	}
	tokens.push_back(token);
}

inline bool Lang::Lexer::is_startof_number() {
	return isdigit(peek());
}

inline bool Lang::Lexer::is_startof_string() {
	return peek() == '"';
}

Token Lang::Lexer::parse_string() {
	buffer.erase();

	int start_row = row;
	int start_col = col;
	int escape_count = 0;
	char c;

	next(); // skip quote;

	while (has_next() && !is_startof_string()) {
		c = next();

		if (c == '\\') {
			escape_count++;
			c = resolve_escape_sequence(next());
		}

		buffer.push_back(c);
	}

	if (!is_startof_string()) {
		throw Lexer_Location_Error("Unterminated string literal", start_row,
								   start_col, start_col + 1);
	} else {
		next(); // skip string termination
	}

	return {TokenType::LIT_STR,
			buffer, row, col - (int) buffer.size(), col};
}

void Lexer::lex() {
	try {
		do_lex();
	} catch (Lexer_Location_Error &ex) {
		print_location(text, ex.get_row(), ex.get_start_col(),
					   ex.get_end_col());
		std::cerr << RED << ex.what() << std::endl << RESET;
		throw ex;
	} catch (Lexer_Token_Error &ex) {
		print_location(text, ex.get_token().row, ex.get_token().start_char,
					   ex.get_token().end_char);
		std::cerr << RED << ex.what() << std::endl << RESET;
		throw ex;
	}
}

Token Lexer::parse_number() {
	buffer.clear();
	int start_row = row;
	int start_col = col;

	bool comma_found = false;

	char c;
	while (isdigit((c = peek())) || c == '_' || c == '.') {
		if (!comma_found && c == '.') {
			comma_found = true;
		} else if (comma_found && c == '.') {
			throw Lexer_Location_Error("Invalid float literal", start_row,
									   start_col, col + 1);
		} else if (c == '_' && offset(1) == '_') {
			// Just to make the error message more informative.
			while (peek() == '_') next();
			throw Lexer_Location_Error(
					"Number literals cannot contain multiple adjacent separators",
					start_row,
					start_col, col + 1);
		} else if (c == '_') {
			next(); // skip _
		}

		buffer.push_back(next());
	}

	TokenType type = comma_found
					 ? TokenType::LIT_FLT
					 : TokenType::LIT_INT;

	return {type, buffer, row, start_col, col};
}

char Lang::Lexer::resolve_escape_sequence(char c) const {
	switch (c) {
		// @formatter:off
		case 'a':
			return '\a';
		case 'b':
			return '\b';
		case 'f':
			return '\f';
		case 'n':
			return '\n';
		case 'r':
			return '\r';
		case 't':
			return '\t';
		case 'v':
			return '\v';
		case '\\':
			return '\\';
		case '"':
			return '"';
		case '\'':
			return '\'';
		default:
			throw Lexer_Location_Error("Invalid escape sequence", row, col - 1,
									   col);
			// @formatter:on
	}
}

inline bool Lexer::is_startof_char() {
	return peek() == '\'';
}

Token Lexer::parse_char() {
	buffer.clear();

	int start_char = col;
	next(); // skip quote;

	char c;
	if (peek() == '\\') {
		next(); // skip backslash
		c = resolve_escape_sequence(next());
	} else {
		c = next();
	}

	buffer.push_back(c);

	if (peek() != '\'') {
		throw Lexer_Location_Error("Invalid char literal", row, start_char,
								   col + 1);
	} else {
		next(); // skip '
	}

	return {TokenType::LIT_CHR, buffer, row, col - 1, col};
}

std::vector<Token> const& Lexer::get_tokens() const {
	return tokens;
}

bool Lexer::is_startof_block_comment() {
	return peek() == '/' && offset(1) == '*';
}

inline bool Lang::Lexer::is_endof_block_comment() {
	return peek() == '*' && offset(1) == '/';
}

void Lexer::parse_block_comment() {
	int start_col = 0;
	int start_row = 0;
	int depth = 0;

	while(true) {
		if (!has_next()) {
			throw Lexer_Location_Error("Unterminated block comment", start_row,
									   start_col, start_col + 2);
		}

		if (is_startof_block_comment()) {
			start_col = col;
			start_row = row;
			depth++;
			skip(2); // skip start block comment
		} else if (is_endof_block_comment()) {
			depth--;
			skip(2);
		} else {
			next();
		}

		if (depth == 0) {
			break;
		}
	}
}

}