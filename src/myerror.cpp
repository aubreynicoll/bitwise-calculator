#include <myerror.h>

#include <string>

namespace error {

Error::Error(std::string const &s) : message{s} {};

auto Error::what() const noexcept -> char const * {
	return this->message.c_str();
}
}  // namespace error
