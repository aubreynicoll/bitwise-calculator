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

	[[nodiscard]] auto what() const noexcept -> char const *;

       private:
	std::string message;
};
}  // namespace error
