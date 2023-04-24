#include <cmakevars.h>
#include <myerror.h>
#include <parser.h>
#include <token.h>

#include <iostream>

auto main() -> int {
	std::cout << "bitwise calculator v" << MAJOR_VERSION << "."
		  << MINOR_VERSION << " by Aubrey Nicoll"
		  << "\n";

	token::TokenStream	 ts{std::cin};
	parser::Parser		 p{ts};
	parser::Parser::number_t result{};

	while (true) {
		try {
			token::Token t{ts.get()};

			switch (t.type) {
				case token::PRINT:
					std::cout << "= " << std::hex << result
						  << "\n";
					continue;
				case token::QUIT:
					return 0;
				default:
					ts.putback(t);
					result = p.statement();
			}
		} catch (error::Error const &e) {
			std::cerr << "Error: " << e.what() << std::endl;
			ts.ignore('\n');
		}
	}
}
