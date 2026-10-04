// University of La Laguna
// School of Engineering and Technology
// Bachelor's Degree in Computer Engineering
// Course: Computational Complexity
// Year: 4th
// Assignment 2: Turing Machine
// Author: Javier Acosta Portocarrero
// Date: 04/10/2026
// File turing_machine_loader.h: declaration file.
// Contains the declaration of the TuringMachineLoader class.

#ifndef TURING_MACHINE_LOADER_H
#define TURING_MACHINE_LOADER_H

#include "../turing_machine.h"
#include "turing_machine_loader_strategy.h"

class TuringMachineLoader {
 public:
  TuringMachineLoader(TuringMachineLoaderStrategy* load_strategy, const std::string& file_path = "") 
      : load_strategy_{load_strategy}, file_path_{file_path} {}

  void SetFilePath(std::string new_path) { file_path_ = new_path;}
  TuringMachine LoadTuringMachine() const;
 private:
  TuringMachineLoaderStrategy* load_strategy_ = nullptr;
  std::string file_path_;
};

#endif