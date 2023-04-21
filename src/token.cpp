#include <token.h>

#include <iostream>
#include <string>

namespace token {

TokenStream::TokenStream(std::istream &is) : inputStream{is} {};

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
		case ';':
		case 'q':
			return Token{c, 0};
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9': {
			this->inputStream.putback(c);
			Token::value_t i;
			this->inputStream >> i;
			return Token{'i', i};
		}
		default:
			throw TokenStreamError{};
	}
}

void TokenStream::putback(Token const &t) {
	if (this->isBufferFull) {
		throw TokenStreamError{};
	}

	this->buffer = t;
	this->isBufferFull = true;
}
}  // namespace token
