#include <parser.h>

#include <string>

namespace parser {

Parser::Parser(token::TokenStream &ts) : tokenStream{ts} {}

Parser::number_t Parser::statement() {
	token::Token t = this->tokenStream.get();

	switch (t.type) {
		case token::LET:
			return declaration();
		default:
			this->tokenStream.putback(t);
			return expression();
	}
}

Parser::number_t Parser::declaration() {
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

Parser::number_t Parser::expression() {
	return this->OR();
}

Parser::number_t Parser::OR() {
	number_t     lval = this->XOR();
	token::Token t;

	while ((t = this->tokenStream.get()).type == '|') {
		lval |= this->XOR();
	}

	this->tokenStream.putback(t);
	return lval;
}

Parser::number_t Parser::XOR() {
	number_t     lval = this->AND();
	token::Token t;

	while ((t = this->tokenStream.get()).type == '^') {
		lval ^= this->AND();
	}

	this->tokenStream.putback(t);
	return lval;
}

Parser::number_t Parser::AND() {
	number_t     lval = this->COMPLEMENT();
	token::Token t;

	while ((t = this->tokenStream.get()).type == '&') {
		lval &= this->COMPLEMENT();
	}

	this->tokenStream.putback(t);
	return lval;
}

Parser::number_t Parser::COMPLEMENT() {
	number_t     mask = 0;
	token::Token t;

	while ((t = this->tokenStream.get()).type == '~') {
		mask = ~mask;
	}

	this->tokenStream.putback(t);
	return mask ^ this->PRIMARY();
}

Parser::number_t Parser::PRIMARY() {
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
