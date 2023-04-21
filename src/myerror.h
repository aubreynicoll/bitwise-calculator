#pragma once

#include <string>

namespace error {
/**
 * Generic exception type class, inherited by other, more-specific, exception
 * classes
 */
class Error {
       public:
	Error(std::string const &s);

	char const *what() const noexcept;

       private:
	std::string const &message;
};
}  // namespace error
