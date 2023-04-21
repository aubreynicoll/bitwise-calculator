#include <cmakevars.h>
#include <parser.h>
#include <token.h>

#include <iostream>

int main() {
	std::cout << "bitwise calculator v" << MAJOR_VERSION << "."
		  << MINOR_VERSION << " by Aubrey Nicoll"
		  << "\n";

	token::TokenStream	 ts{std::cin};
	parser::Parser		 p{ts};
	parser::Parser::number_t result{};

	while (true) {
		token::Token t{ts.get()};

		switch (t.type) {
			case ';':
				std::cout << "= " << std::hex << result << "\n";
				continue;
			case 'q':
				goto exit_program;
			default:
				ts.putback(t);
				result = p.expression();
		}
	}

exit_program:
	return 0;
}
