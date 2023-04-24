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

	auto statement() -> number_t;

       private:
	auto declaration() -> number_t;
	auto expression() -> number_t;
	auto OR() -> number_t;
	auto XOR() -> number_t;
	auto AND() -> number_t;
	auto COMPLEMENT() -> number_t;
	auto PRIMARY() -> number_t;

	token::TokenStream			 &tokenStream;
	std::unordered_map<std::string, number_t> var_table;
};

}  // namespace parser

#include <token.h>
