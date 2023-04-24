#pragma once

#include <myerror.h>
#include <parser.h>

#include <iostream>

namespace token {
const std::string DECLKEY = "let";
enum Constants {
	PRINT = ';',
	QUIT = 'q',
	NUMBER = '0',
	LET = '1',
	NAME = '2',
};

class TokenStreamError : public error::Error {};

class Token {
       public:
	using type_t = char;
	using value_t = parser::Parser::number_t;

	type_t	    type{};
	value_t	    value{};
	std::string name{};

	Token();
	Token(type_t type);
	Token(type_t type, value_t value);
	Token(type_t type, std::string name);
};

class TokenStream {
       public:
	TokenStream(std::istream &is);

	auto get() -> Token;
	auto putback(Token const &t) -> void;
	auto ignore(char c) -> void;

       private:
	std::istream &inputStream;
	Token	      buffer;
	bool	      isBufferFull{false};
};

}  // namespace token
