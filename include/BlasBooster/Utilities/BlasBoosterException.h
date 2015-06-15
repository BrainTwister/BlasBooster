#ifndef BLASBOOSTEREXCEPTION_H_
#define BLASBOOSTEREXCEPTION_H_

#include <stdexcept>

struct BlasBoosterException : public std::runtime_error {
    BlasBoosterException(const std::string &msg) : std::runtime_error(msg) {}
};

#endif /* BLASBOOSTEREXCEPTION_H_ */
