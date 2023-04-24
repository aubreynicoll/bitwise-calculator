#include <token.h>

#include <cctype>
#include <iostream>
#include <limits>
#include <string>

namespace token {

Token::Token(){};
Token::Token(type_t type) : type{type} {};
Token::Token(type_t type, value_t value) : type{type}, value{value} {};
Token::Token(type_t type, std::string name) : type{type}, name{name} {};

TokenStream::TokenStream(std::istream &is) : inputStream{is} {
	this->inputStream.unsetf(std::ios::dec);
	this->inputStream.unsetf(std::ios::oct);
	this->inputStream.unsetf(std::ios::hex);
};

Token TokenStream::get() {
	if (this->isBufferFull) {
		this->isBufferFull = false;
		return this->buffer;
	}

	char c;
	this->inputStream >> c;

	switch (c) {
		case '|':
		case '^':
		case '&':
		case '~':
		case '(':
		case ')':
		case token::PRINT:
		case token::QUIT:
		case '=':
			return Token{c};
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
		case '-': {
			this->inputStream.putback(c);
			Token::value_t i;
			this->inputStream >> i;
			if (!this->inputStream) {
				throw TokenStreamError{
				    std::string{"bad input"}};
			}
			return Token{NUMBER, i};
		}
		default:
			if (isalpha(c)) {
				this->inputStream.putback(c);

				std::string s{};
				char	    c{};

				while (this->inputStream.get(c) &&
				       std::isalnum(c)) {
					s += c;
				}

				this->inputStream.putback(c);

				if (s == DECLKEY) {
					return Token{LET};
				}

				return Token{NAME, s};
			}

			throw TokenStreamError{std::string{"bad input"}};
	}
}

void TokenStream::putback(Token const &t) {
	if (this->isBufferFull) {
		throw TokenStreamError{std::string{"buffer full"}};
	}

	this->buffer = t;
	this->isBufferFull = true;
}

void TokenStream::ignore(char c) {
	if (this->isBufferFull && this->buffer.type == c) {
		this->isBufferFull = false;
		return;
	}

	this->isBufferFull = false;

	constexpr auto max_size = std::numeric_limits<std::streamsize>::max();
	this->inputStream.ignore(max_size, c);
}
}  // namespace token
