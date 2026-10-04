// University of La Laguna
// School of Engineering and Technology
// Bachelor's Degree in Computer Engineering
// Course: Computational Complexity
// Year: 4th
// Assignment 2: Turing Machine
// Author: Javier Acosta Portocarrero
// Date: 04/10/2026
// File turing_machine_loader_strategy.h: declaration file.
// Contains the declaration of the TuringMachineLoaderStrategy class.

#ifndef TURING_MACHINE_LOADER_STRATEGY_H
#define TURING_MACHINE_LOADER_STRATEGY_H

#include "../turing_machine.h"

class TuringMachineLoaderStrategy {
 public:
  virtual ~TuringMachineLoaderStrategy() = default;

  virtual TuringMachine LoadTuringMachine(const std::string& file_path) const = 0;
};

#endif
