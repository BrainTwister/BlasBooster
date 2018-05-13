#pragma once

#include <stdexcept>

struct BlasBoosterException : public std::runtime_error {
    BlasBoosterException(const std::string &msg) : std::runtime_error(msg) {}
};
