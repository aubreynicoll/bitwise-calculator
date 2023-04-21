#pragma once

#include <myerror.h>

namespace token {
class TokenStream;
};

namespace parser {

class ParserError {};

class Parser {
       public:
	using number_t = unsigned;

	Parser(token::TokenStream &ts);

	number_t expression();

       private:
	number_t OR();
	number_t XOR();
	number_t AND();
	number_t COMPLEMENT();
	number_t PRIMARY();

	token::TokenStream &tokenStream;
};

}  // namespace parser

#include <token.h>
