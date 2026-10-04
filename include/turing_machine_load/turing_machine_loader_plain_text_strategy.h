// University of La Laguna
// School of Engineering and Technology
// Bachelor's Degree in Computer Engineering
// Course: Computational Complexity
// Year: 4th
// Assignment 2: Turing Machine
// Author: Javier Acosta Portocarrero
// Date: 04/10/2026
// File turing_machine_loader_plain_text_strategy.h: declaration file.
// Contains the declaration of the TuringMachineLoaderPlainTextStrategy class.

#ifndef TURING_MACHINE_LOADER_PLAIN_TEXT_STRATEGY_H
#define TURING_MACHINE_LOADER_PLAIN_TEXT_STRATEGY_H

#include "turing_machine_loader_strategy.h"

#include <fstream>

class TuringMachineLoaderPlainTextStrategy : public TuringMachineLoaderStrategy {
 public:
  TuringMachineLoaderPlainTextStrategy() = default;
  ~TuringMachineLoaderPlainTextStrategy() = default;

  TuringMachine LoadTuringMachine(const std::string& file_path) const override;
 private:
  std::string GetNextContentLine(std::ifstream& input_file, unsigned& line_number, const std::string& expected_content) const;
  std::string RemoveCommentsAndWhitespace(const std::string& line) const;
  std::set<std::string> ReadStates(const std::string& line, unsigned line_number) const;
  std::set<Symbol> ReadAlphabet(const std::string& line, unsigned line_number, const std::string& alphabet_name) const;
  std::string ReadSingleElement(const std::string& line, unsigned line_number, const std::string& element_name) const;
  unsigned ReadAmountOfStrings(const std::string& line, unsigned line_number) const;

  void ReadTransition(const std::string& line, unsigned line_number, unsigned transition_identifier,
      unsigned amount_of_strings, const std::set<std::string>& automaton_states, 
      const std::set<Symbol>& strings_alphabet, TransitionFunction& transition_function) const;
};

#endif
