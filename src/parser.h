#pragma once

#include <myerror.h>

#include <unordered_map>

namespace token {
class TokenStream;
};

namespace parser {

class ParserError : public error::Error {};

class Parser {
       public:
	using number_t = unsigned;

	Parser(token::TokenStream &ts);

	number_t statement();

       private:
	number_t declaration();
	number_t expression();
	number_t OR();
	number_t XOR();
	number_t AND();
	number_t COMPLEMENT();
	number_t PRIMARY();

	token::TokenStream			   &tokenStream;
	std::unordered_map<std::string, number_t> var_table;
};

}  // namespace parser

#include <token.h>
