#pragma once

#include <myerror.h>
#include <parser.h>

#include <iostream>

namespace token {

class TokenStreamError : public error::Error {};

class Token {
       public:
	using type_t = char;
	using value_t = parser::Parser::number_t;

	type_t	type;
	value_t value;
};

class TokenStream {
       public:
	TokenStream(std::istream &is);

	Token get();
	void  putback(Token const &t);

       private:
	std::istream &inputStream;
	Token	      buffer;
	bool	      isBufferFull{false};
};

}  // namespace token
