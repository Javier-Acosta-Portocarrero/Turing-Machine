// University of La Laguna
// School of Engineering and Technology
// Bachelor's Degree in Computer Engineering
// Course: Computational Complexity
// Year: 4th
// Assignment 2: Turing Machine
// Author: Javier Acosta Portocarrero
// Date: 04/10/2026
// File main_functions.cc: implementation file.
// Contains the implementation of the turing machine program functions.

#include "../include/main_functions.h"
#include "../include/exceptions/input_exception.h"

#include <fstream>
#include <iostream>

/**
 * 
 */
void ReadProgramArguments(int argc, char* argv[], std::string& config_file, std::string& input_file, bool& parameter_error) {
  for (int i = 1; i < argc; ++i) {
    const std::string argument = argv[i];
    if (argument == "-config") {
      if (i + 1 >= argc) {
        parameter_error = true;
        throw InputException("Missing file after -config.");
      }
      config_file = argv[++i];

    } else if (argument == "-in") {
      if (i + 1 >= argc) {
        parameter_error = true;
        throw InputException("Missing file after -in.");
      }
      input_file = argv[++i];

    } else {
      parameter_error = true;
      throw InputException("Unknown option '" + argument + "'.");
    }
  }
  if (config_file.empty()) {
    parameter_error = true;
    throw InputException("Missing -config option.");
  }
}

/**
 * 
 */
void PrintTapes(const TuringMachine& turing_machine) {
  const std::vector<std::string> strings_representations = turing_machine.GetStringsRepresentations();
  for (size_t i = 0; i < strings_representations.size(); ++i) {
    std::cout << "Tape " << i + 1 << ": " << strings_representations[i] << std::endl;
  }
}

/**
 * 
 */
void ExecuteInputFile(TuringMachine& turing_machine, const std::string& input_file) {
  std::ifstream words_file{input_file};
  if (!words_file.is_open()) {
    throw InputException("Could not open input file '" + input_file + "'.");
  }
  std::string input_word;
  while (std::getline(words_file, input_word)) {
    if (!input_word.empty() && input_word.back() == '\r') {
      input_word.pop_back();
    }
    const bool accepted = turing_machine.AcceptsWord(input_word);
    std::cout << input_word << ": " << (accepted ? "\nAccepted" : "\nRejected") << std::endl;
    PrintTapes(turing_machine);
  }
}

/**
 * 
 */
void ExecuteKeyboardInput(TuringMachine& turing_machine) {
  std::string input_word;
  while (true) {
    std::cout << "\nInput word (type exit to finish): ";
    std::cin >> input_word;
    if (input_word == "exit") {
      break;
    }
    const bool accepted = turing_machine.AcceptsWord(input_word);
    std::cout << (accepted ? "\nAccepted" : "\nRejected") << std::endl;
    PrintTapes(turing_machine);
  }
}