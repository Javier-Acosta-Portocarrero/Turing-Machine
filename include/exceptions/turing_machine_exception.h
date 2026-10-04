// University of La Laguna
// School of Engineering and Technology
// Bachelor's Degree in Computer Engineering
// Course: Computational Complexity
// Year: 4th
// Assignment 2: Turing Machine
// Author: Javier Acosta Portocarrero
// Date: 04/10/2026
// File turing_machine_exception.h: declaration file.
// Contains the declaration of the TuringMachineException class.

#ifndef TURING_MACHINE_EXCEPTION_H
#define TURING_MACHINE_EXCEPTION_H

#include <stdexcept>

class TuringMachineException : public std::runtime_error {
 public:
  explicit TuringMachineException(const std::string& message) : std::runtime_error(message) {}
};

#endif