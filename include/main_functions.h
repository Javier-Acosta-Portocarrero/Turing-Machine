// University of La Laguna
// School of Engineering and Technology
// Bachelor's Degree in Computer Engineering
// Course: Computational Complexity
// Year: 4th
// Assignment 2: Turing Machine
// Author: Javier Acosta Portocarrero
// Date: 04/10/2026
// File main_functions.h: declaration file.
// Contains the declaration of the turing machine program functions.

#ifndef TURING_MACHINE_PROGRAM_H
#define TURING_MACHINE_PROGRAM_H

#include "turing_machine.h"

#include <string>

void ReadProgramArguments(int argc, char* argv[], std::string& config_file, std::string& input_file, bool& parameter_error);
void ExecuteInputFile(TuringMachine& turing_machine, const std::string& input_file);
void ExecuteKeyboardInput(TuringMachine& turing_machine);
void PrintTapes(const TuringMachine& turing_machine);

#endif