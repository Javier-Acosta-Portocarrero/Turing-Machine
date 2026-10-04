// University of La Laguna
// School of Engineering and Technology
// Bachelor's Degree in Computer Engineering
// Course: Computational Complexity
// Year: 4th
// Assignment 1: Pushdown Automaton
// Author: Javier Acosta Portocarrero
// Date: 01/10/2026
// File input_string_exception.h: declaration file.
// Contains the declaration of the InputStringException class.

#ifndef INPUT_STRING_EXCEPTION_H
#define INPUT_STRING_EXCEPTION_H

#include <stdexcept>

class TuringMachineStringException : public std::runtime_error {
 public:
  explicit TuringMachineStringException(const std::string& message) : std::runtime_error(message) {}
};

#endif