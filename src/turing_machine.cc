// University of La Laguna
// School of Engineering and Technology
// Bachelor's Degree in Computer Engineering
// Course: Computational Complexity
// Year: 4th
// Assignment 1: Pushdown Automaton
// Author: Javier Acosta Portocarrero
// Date: 24/09/2026
// File pushdown_automaton.cc: implementation file.
// Contains the implementation of the TuringMachine class.

#include "../include/turing_machine.h"
#include "../include/exceptions/turing_machine_exception.h"

/**
 * 
 */
TuringMachine::TuringMachine(const TransitionFunction& inner_transition_function, 
    const std::set<Symbol>& input_alphabet, const std::set<Symbol>& strings_alphabet, 
    const std::set<std::string>& automaton_states, const std::string& start_state, 
    unsigned amount_of_strings, Symbol white_symbol, const std::set<std::string>& acceptance_automaton_states)
      : inner_transition_function_{inner_transition_function}, input_alphabet_{input_alphabet}, 
      strings_alphabet_{strings_alphabet}, turing_machines_states_{automaton_states}, acceptance_automaton_states_{acceptance_automaton_states},
      start_state_{start_state}, amount_of_strings_{amount_of_strings}, white_symbol_{white_symbol} {

  if (amount_of_strings <= 0) {
    throw TuringMachineException("A Turing Machine must have at least 1 string.");
  }
  for (unsigned i = 0; i < amount_of_strings_; ++i) {
    inner_strings_.emplace_back(TuringMachineString(input_alphabet_, strings_alphabet_, white_symbol_));
  }
  current_state_ = start_state_;
}

/**
 * 
 */
void TuringMachine::Reset() {
  current_state_ = start_state_;
  for (TuringMachineString& string : inner_strings_) {
    string.Reset();
  }
}

/**
 * 
 */
InstantaneousDescription TuringMachine::BuildInstantaneousDescription() const {
  std::string entry_symbols = "";
  for (const TuringMachineString& string : inner_strings_) {
    entry_symbols += string.GetCurrentSymbol();
  }

  return InstantaneousDescription(current_state_, entry_symbols);
}

/**
 * @brief Checks if the pushdown automaton accepts the given input word.
 * @param input_word Input word to check.
 * @return true if the automaton accepts the word or false if not.
 */
bool TuringMachine::AcceptsWord(const std::string& input_word) {
  Reset();
  inner_strings_[0].IntroduceNewInputWord(input_word);

  const TransitionEffects* next_transition = inner_transition_function_.GetPossibleTransition(BuildInstantaneousDescription());
  while (next_transition != nullptr) {
    std::string next_state = next_transition->GetDestinyState();
    if (!turing_machines_states_.contains(next_state)) {
      throw TuringMachineException("Transition function contains a state that doesn't belong to turing machine possible states.");
    }
    for (size_t i{0}; i < inner_strings_.size(); ++i) {
      inner_strings_[i].Write(next_transition->GetSymbolsToWrite()[i]);
      inner_strings_[i].MoveHead(next_transition->GetHeadMovements()[i]);
    }
    current_state_ = next_state;
    next_transition = inner_transition_function_.GetPossibleTransition(BuildInstantaneousDescription());
  }

  return acceptance_automaton_states_.contains(current_state_);
}