// University of La Laguna
// School of Engineering and Technology
// Bachelor's Degree in Computer Engineering
// Course: Computational Complexity
// Year: 4th
// Assignment 2: Turing Machine
// Author: Javier Acosta Portocarrero
// Date: 04/10/2026
// File main.cc: main program file.
// Contains the main function of the turing machine simulator.

#include "../include/turing_machine_load/turing_machine_loader.h"
#include "../include/turing_machine_load/turing_machine_loader_plain_text_strategy.h"
#include "../include/main_functions.h"

#include <iostream>
#include <stdexcept>
#include <string>

/**
 * @brief Main function of the turing machine simulator.
 */
int main(int argc, char* argv[]) {
  bool parameter_error = false;

  try {
    std::string config_file;
    std::string input_file;
    ReadProgramArguments(argc, argv, config_file, input_file, parameter_error);

    TuringMachineLoaderPlainTextStrategy plain_text_strategy;
    TuringMachineLoader loader{&plain_text_strategy, config_file};
    TuringMachine turing_machine = loader.LoadTuringMachine();

    if (!input_file.empty()) {
      ExecuteInputFile(turing_machine, input_file);
    } else {
      ExecuteKeyboardInput(turing_machine);
    }
    return 0;

  } catch (const std::exception& exception) {
    std::cerr << "Error: " << exception.what() << std::endl;
    if (parameter_error) {
      std::cerr << "\nUsage:\n";
      std::cerr << "  " << argv[0] << " -config <file> [-in <file>]\n";
    }
    return 1;
  }
}