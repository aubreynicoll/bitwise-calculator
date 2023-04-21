#include <myerror.h>

#include <string>

namespace error {

Error::Error(std::string const &s) : message{s} {};

char const *Error::what() const noexcept {
	return this->message.c_str();
}
}  // namespace error
