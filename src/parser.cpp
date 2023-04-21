#include <parser.h>

#include <string>

namespace parser {

Parser::Parser(token::TokenStream &ts) : tokenStream{ts} {}

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
				throw ParserError{};
			}
			return exp;
		}
		case 'i':
			return t.value;
		default:
			throw ParserError{};
	}
}
}  // namespace parser
