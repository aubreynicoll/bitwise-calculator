#include <token.h>

#include <iostream>
#include <string>

namespace token {

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
		case '9':
		case '-': {
			this->inputStream.putback(c);
			Token::value_t i;
			this->inputStream >> i;
			if (!this->inputStream) {
				throw TokenStreamError{
				    std::string{"bad input"}};
			}
			return Token{'i', i};
		}
		default:
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
}  // namespace token
