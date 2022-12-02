//
// Created by nik on 12/1/22.
//

#include "Lexer.h"

Lang::Lexer::Lexer(std::string& text) : Indexed_Char_Iterator(text) {
	auto* buf_ptr = new std::string();
	buf_ptr->reserve(max_identifier_length);

	this->tokens.reserve(2048);

	this->buffer = std::shared_ptr<std::string>(buf_ptr);
}

void Lang::Lexer::do_lex() {

	while (has_next()) {
		if (isspace(peek())) {
			next();
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

			auto keyword = Lang::Token::types.at(type);

			int offset = 1;
			if (type != Token::Type::INVALID) {
				offset = (int) strlen(keyword);
			}

			auto token = Token::Token(type,
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

Lang::Token::Type Lang::Lexer::parse_operator() {
	char c = next();
	if (c == '!') {
		if (peek() == '=') {
			next();
			return Token::Type::NE;
		} else {
			return Token::Type::NOT;
		}
	}

	if (c == '%') { return Token::Type::MOD; }
	if (c == '&') {
		if (peek() == '&') {
			next();
			return Token::Type::AND;
		} else {
			return Token::Type::AMP;
		}
	}

	if (c == '(') {
		return Token::Type::LPAREN;
	}
	if (c == ')') {
		return Token::Type::RPAREN;
	}
	if (c == '*') {
		if (peek() == '=') {
			next();
			return Token::Type::MULASSN;
		} else if (peek() == '*') {
			next();
			return Token::Type::STARSTAR;
		} else {
			return Token::Type::STAR;
		}
	}
	if (c == '+') {
		if (peek() == '+') {
			next();
			return Token::Type::INC;
		} else if (peek() == '=') {
			next();
			return Token::Type::ADDASSN;
		} else {
			return Token::Type::ADD;
		}
	}
	if (c == ',') {
		return Token::Type::COMMA;
	}
	if (c == '-') {
		if (peek() == '-') {
			next();
			return Token::Type::DEC;
		} else if (peek() == '=') {
			next();
			return Token::Type::SUBASSN;
		} else if (peek() == '>') {
			next();
			return Token::Type::THIN_ARROW;
		} else {
			return Token::Type::SUB;
		}
	}
	if (c == '.') {
		if (peek() == '.') {
			next();
			return Token::Type::DDOT;
		} else {
			return Token::Type::DOT;
		}
	}
	if (c == '/') {
		if (peek() == '=') {
			next();
			return Token::Type::DIVASSN;
		} else {
			return Token::Type::DIV;
		}
	}
	if (c == ':') {
		return Token::Type::COL;
	}
	if (c == ';') {
		return Token::Type::SCOL;
	}
	if (c == '<') {
		if (peek() == '=') {
			next();
			return Token::Type::LE;
		} else {
			return Token::Type::LT;
		}
	}
	if (c == '=') {
		if (peek() == '=') {
			next();
			return Token::Type::EQ;
		} else if (peek() == '>') {
			next();
			return Token::Type::FAT_ARROW;
		} else {
			return Token::Type::ASSN;
		}
	}
	if (c == '>') {
		if (peek() == '=') {
			next();
			return Token::Type::GE;
		} else {
			return Token::Type::GT;
		}
	}

	if (c == '?') {
		if (peek() == '?') {
			next();
			return Token::Type::DQM;
		} else {
			return Token::Type::QM;
		}
	}

	if (c == '[') {
		return Token::Type::LBRACK;
	}
	if (c == ']') {
		return Token::Type::RBRACK;
	}
	if (c == '{') {
		return Token::Type::LBRACE;
	}
	if (c == '|') {
		if (peek() == '|') {
			next();
			return Token::Type::OR;
		} else {
			return Token::Type::PIPE;
		}
	}
	if (c == '}') {
		return Token::Type::RBRACE;
	}

	return Token::Type::INVALID;
}

Lang::Token::Token Lang::Lexer::parse_keyword() {
	buffer->erase();

	while (isalnum(peek()) || peek() == '#' || peek() == '$' || peek() == '_') {
		buffer->push_back(next());
	}

	auto type = Token::find_by_value(buffer->c_str());

	return {type == Token::Type::INVALID
			? Token::Type::IDENTIFIER
			: type,
			*buffer, row, col - (int) buffer->size(), col};

}

inline bool Lang::Lexer::is_startof_identifier() {
	char c = peek();
	return isalpha(c) || c == '$' || c == '_';
}

void Lang::Lexer::emit_token(const Lang::Token::Token& token) {
	// std::cout << token << std::endl;
	if (token.type == Token::Type::INVALID) {
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

Lang::Token::Token Lang::Lexer::parse_string() {
	buffer->erase();

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

		buffer->push_back(c);
	}

	if (!is_startof_string()) {
		throw Lexer_Location_Error("Unterminated string literal", start_row, start_col, start_col + 1);
	} else {
		next(); // skip string termination
	}

	return {Token::Type::LIT_STR,
			*buffer, row, col - (int) buffer->size(), col};
}

void Lang::Lexer::lex() {
	try {
		do_lex();
	} catch (Lexer_Location_Error& ex) {
		print_location(text, ex.get_row(), ex.get_start_col(), ex.get_end_col());
		std::cerr << RED << ex.what() << std::endl << RESET;
	} catch (Lexer_Token_Error& ex) {
		print_location(text, ex.get_token().row, ex.get_token().start_char, ex.get_token().end_char);
		std::cerr << RED << ex.what() << std::endl << RESET;
	}
}

Lang::Token::Token Lang::Lexer::parse_number() {
	buffer->clear();
	int start_row = row;
	int start_col = col;

	bool comma_found = false;

	char c;
	while (isdigit((c = peek())) || c == '_' || c == '.') {
		if (!comma_found && c == '.') {
			comma_found = true;
		} else if (comma_found && c == '.') {
			throw Lexer_Location_Error("Invalid float literal", start_row, start_col, col + 1);
		} else if (c == '_' && offset(1) == '_') {
			// Just to make the error message more informative.
			while (peek() == '_') next();
			throw Lexer_Location_Error("Number literals cannot contain multiple adjacent separators", start_row,
									   start_col, col + 1);
		} else if (c == '_') {
			next(); // skip _
		}

		buffer->push_back(next());
	}

	Token::Type type = comma_found
					   ? Token::Type::LIT_FLT
					   : Token::Type::LIT_INT;

	return {type, *buffer, row, start_col, col};
}

char Lang::Lexer::resolve_escape_sequence(char c) {
	switch (c) {
		// @formatter:off
		case 'a':  return '\a';
		case 'b':  return '\b';
		case 'f':  return '\f';
		case 'n':  return '\n';
		case 'r':  return '\r';
		case 't':  return '\t';
		case 'v':  return '\v';
		case '\\': return '\\';
		case '"':  return  '"';
		case '\'':  return  '\'';
		default:
			throw Lexer_Location_Error("Invalid escape sequence", row, col - 1, col);
		// @formatter:on
	}
}

inline bool Lang::Lexer::is_startof_char() {
	return peek() == '\'';
}

Lang::Token::Token Lang::Lexer::parse_char() {
	buffer->clear();

	int start_char = col;
	next(); // skip quote;

	char c;
	if (peek() == '\\') {
		next(); // skip backslash
		c = resolve_escape_sequence(next());
	} else {
		c = next();
	}

	buffer->push_back(c);

	if (peek() != '\'') {
		throw Lexer_Location_Error("Invalid char literal", row, start_char, col + 1);
	} else {
		next(); // skip '
	}

	return {Token::Type::LIT_CHR, *buffer, row, col - 1, col};
}
