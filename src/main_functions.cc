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
#include <sstream>
#include <iostream>

/**
 * @brief Reads the program arguments and sets the configuration and input file paths.
 * 
 * @param argc Argument count.
 * @param argv Argument vector.
 * @param config_file Reference to the string where the configuration file path will be stored.
 * @param input_file Reference to the string where the input file path will be stored.
 * @param parameter_error Reference to a boolean that will be set to true if there is a parameter error.
 * @throws InputException If there are missing or unknown options in the arguments.
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
 * @brief Prints the tapes of the Turing machine.
 * 
 * @param turing_machine The Turing machine whose tapes will be printed.
 */
void PrintTapes(const TuringMachine& turing_machine) {
  const std::vector<std::string> strings_representations = turing_machine.GetStringsRepresentations();
  for (size_t i = 0; i < strings_representations.size(); ++i) {
    std::cout << "Tape " << i + 1 << ": " << strings_representations[i] << std::endl;
  }
}

/**
 * @brief Executes the Turing machine on input words from a file.
 * 
 * @param turing_machine The Turing machine to execute.
 * @param input_file Path to the file containing input words.
 * @throws InputException If the input file cannot be opened.
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
 * @brief Executes the Turing machine on input words from the keyboard.
 * 
 * @param turing_machine The Turing machine to execute.
 */
void ExecuteKeyboardInput(TuringMachine& turing_machine) {
  std::string input_word;
  while (true) {
    std::cout << "\nInput word (type exit to finish): ";
    std::getline(std::cin, input_word);
    if (input_word == "exit") {
      break;
    }
    const bool accepted = turing_machine.AcceptsWord(input_word);
    std::cout << (accepted ? "\nAccepted" : "\nRejected") << std::endl;
    PrintTapes(turing_machine);
  }
}