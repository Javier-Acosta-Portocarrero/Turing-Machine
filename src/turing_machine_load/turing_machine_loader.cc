// University of La Laguna
// School of Engineering and Technology
// Bachelor's Degree in Computer Engineering
// Course: Computational Complexity
// Year: 4th
// Assignment 2: Turing Machine
// Author: Javier Acosta Portocarrero
// Date: 04/10/2026
// File turing_machine_loader.cc: implementation file.
// Contains the implementation of the TuringMachineLoader class.

#include "../../include/turing_machine_load/turing_machine_loader.h"
#include "../../include/exceptions/input_exception.h"

/**
 * @brief Loads a Turing machine using the provided loading strategy.
 * 
 * @return The loaded Turing machine.
 * @throws InputException If no loading strategy or configuration file is provided.
 */
TuringMachine TuringMachineLoader::LoadTuringMachine() const {
  if (load_strategy_ == nullptr) {
    throw InputException("No loading strategy was provided.");
  }
  if (file_path_.empty()) {
    throw InputException("No configuration file was provided.");
  }
  return load_strategy_->LoadTuringMachine(file_path_);
}