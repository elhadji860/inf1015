#pragma once
#include <iostream>
#include <exception>

class InvalidValueException : public std::logic_error {
public:
	using logic_error::logic_error;
};