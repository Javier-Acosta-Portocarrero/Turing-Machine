// University of La Laguna
// School of Engineering and Technology
// Bachelor's Degree in Computer Engineering
// Course: Computational Complexity
// Year: 4th
// Assignment 2: Turing Machine
// Author: Javier Acosta Portocarrero
// Date: 04/10/2026
// File turing_machine.h: declaration file.
// Contains the declaration of the TuringMachine class.

#ifndef TURING_MACHINE_H
#define TURING_MACHINE_H

#include "transition_function.h"
#include "turing_machine_string.h"
#include "instantaneous_description.h"

#include <vector>

using Symbol = char;

// Empty stack version of a pushdown automaton
class TuringMachine {
 public:
  TuringMachine(const TransitionFunction& inner_transition_function, const std::set<Symbol>& input_alphabet, 
    const std::set<Symbol>& strings_alphabet, const std::set<std::string>& automaton_states, const std::string& start_state, 
    unsigned amount_of_strings, Symbol white_symbol, const std::set<std::string>& acceptance_automaton_states);

  bool AcceptsWord(const std::string& input_word);
  std::vector<std::string> GetStringsRepresentations() const;
      
 private:
  const TransitionFunction inner_transition_function_;
  const std::set<std::string> turing_machines_states_;
  const std::set<std::string> acceptance_automaton_states_;
  const std::set<Symbol> strings_alphabet_;
  const std::set<Symbol> input_alphabet_;
  const std::string start_state_;
  unsigned amount_of_strings_;
  std::vector<TuringMachineString> inner_strings_;
  Symbol white_symbol_;
  std::string current_state_;

  InstantaneousDescription BuildInstantaneousDescription() const;
  void Reset();
};

#endif