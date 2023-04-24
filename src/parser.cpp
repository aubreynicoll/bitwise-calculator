#include <parser.h>

#include <string>

namespace parser {

Parser::Parser(token::TokenStream &ts) : tokenStream{ts} {}

auto Parser::statement() -> Parser::number_t {
	token::Token t = this->tokenStream.get();

	switch (t.type) {
		case token::LET:
			return declaration();
		default:
			this->tokenStream.putback(t);
			return expression();
	}
}

auto Parser::declaration() -> Parser::number_t {
	token::Token t = this->tokenStream.get();

	if (t.type != token::NAME) {
		throw ParserError{std::string{"expected name in declaration"}};
	}

	if ((this->tokenStream.get()).type != '=') {
		throw ParserError{std::string{"missing '=' from declaration"}};
	}

	number_t d = this->expression();
	this->var_table[t.name] = d;
	return d;
}

auto Parser::expression() -> Parser::number_t {
	return this->OR();
}

auto Parser::OR() -> Parser::number_t {
	number_t     lval = this->XOR();
	token::Token t;

	while ((t = this->tokenStream.get()).type == '|') {
		lval |= this->XOR();
	}

	this->tokenStream.putback(t);
	return lval;
}

auto Parser::XOR() -> Parser::number_t {
	number_t     lval = this->AND();
	token::Token t;

	while ((t = this->tokenStream.get()).type == '^') {
		lval ^= this->AND();
	}

	this->tokenStream.putback(t);
	return lval;
}

auto Parser::AND() -> Parser::number_t {
	number_t     lval = this->COMPLEMENT();
	token::Token t;

	while ((t = this->tokenStream.get()).type == '&') {
		lval &= this->COMPLEMENT();
	}

	this->tokenStream.putback(t);
	return lval;
}

auto Parser::COMPLEMENT() -> Parser::number_t {
	number_t     mask = 0;
	token::Token t;

	while ((t = this->tokenStream.get()).type == '~') {
		mask = ~mask;
	}

	this->tokenStream.putback(t);
	return mask ^ this->PRIMARY();
}

auto Parser::PRIMARY() -> Parser::number_t {
	token::Token t = this->tokenStream.get();

	switch (t.type) {
		case '(': {
			number_t     exp = this->expression();
			token::Token next = this->tokenStream.get();
			if (next.type != ')') {
				throw ParserError{std::string{"expected ')'"}};
			}
			return exp;
		}
		case token::NAME:
			if (!this->var_table.count(t.name)) {
				throw ParserError{
				    std::string{"unknown identifier"}};
			}
			return this->var_table[t.name];
		case token::NUMBER:
			return t.value;
		default:
			throw ParserError{std::string{"expected primary"}};
	}
}
}  // namespace parser
