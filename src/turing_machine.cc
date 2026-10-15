// University of La Laguna
// School of Engineering and Technology
// Bachelor's Degree in Computer Engineering
// Course: Computational Complexity
// Year: 4th
// Assignment 2: Turing Machine
// Author: Javier Acosta Portocarrero
// Date: 04/10/2026
// File turing_machine.cc: implementation file.
// Contains the implementation of the TuringMachine class.

#include "../include/turing_machine.h"
#include "../include/exceptions/turing_machine_exception.h"

/**
 * @brief Constructs a Turing machine with the given parameters.
 * 
 * @param inner_transition_function The transition function of the Turing machine.
 * @param input_alphabet Set of symbols that form the input alphabet.
 * @param strings_alphabet Set of symbols that form the string alphabet.
 * @param automaton_states Set of valid states in the Turing machine.
 * @param start_state The initial state of the Turing machine.
 * @param amount_of_strings Number of strings in the Turing machine.
 * @param white_symbol Symbol representing the blank symbol in the Turing machine.
 * @param acceptance_automaton_states Set of acceptance states in the Turing machine.
 * @throws TuringMachineException If the amount of strings is not positive or if there are inconsistencies in the transition function.
 */
TuringMachine::TuringMachine(const TransitionFunction& inner_transition_function, 
    const std::set<Symbol>& input_alphabet, const std::set<Symbol>& strings_alphabet, 
    const std::set<std::string>& automaton_states, const std::string& start_state, 
    unsigned amount_of_strings, Symbol white_symbol, const std::set<std::string>& acceptance_automaton_states)
      : inner_transition_function_{inner_transition_function}, input_alphabet_{input_alphabet}, 
      strings_alphabet_{strings_alphabet}, turing_machines_states_{automaton_states}, acceptance_automaton_states_{acceptance_automaton_states},
      start_state_{start_state}, amount_of_strings_{amount_of_strings}, white_symbol_{white_symbol} {

  if (amount_of_strings <= 0) {
    throw TuringMachineException("A Turing Machine must have at least 1 tape.");
  }
  for (unsigned i = 0; i < amount_of_strings_; ++i) {
    inner_strings_.emplace_back(TuringMachineTape(input_alphabet_, strings_alphabet_, white_symbol_));
  }
  current_state_ = start_state_;
}

/**
 * @brief Resets the Turing machine to its initial state, clearing all strings and setting the current state to the start state.
 */
void TuringMachine::Reset() {
  current_state_ = start_state_;
  for (TuringMachineTape& string : inner_strings_) {
    string.Reset();
  }
}

/**
 * @brief Builds the instantaneous description for the current state of the Turing machine.
 * 
 * @return The instantaneous description.
 */
InstantaneousDescription TuringMachine::BuildInstantaneousDescription() const {
  std::string entry_symbols = "";
  for (const TuringMachineTape& string : inner_strings_) {
    entry_symbols += string.GetCurrentSymbol();
  }

  return InstantaneousDescription(current_state_, entry_symbols);
}

/**
 * @brief Returns the string representations of all strings in the Turing machine.
 * 
 * @return A vector containing the string representations.
 */
std::vector<std::string> TuringMachine::GetStringsRepresentations() const {
  std::vector<std::string> representations;
  for (size_t i{0}; i < amount_of_strings_; ++i) {
    representations.emplace_back(inner_strings_[i].GetStringRepresentation());
  }

  return representations;
}

/**
 * @brief Checks if the pushdown automaton accepts the given input word.
 * 
 * @param input_word Input word to check.
 * @return true if the automaton accepts the word or false if not.
 */
bool TuringMachine::AcceptsWord(const std::string& input_word) {
  Reset();
  inner_strings_[0].IntroduceNewInputWord(input_word);

  const TransitionEffects* next_transition = inner_transition_function_.GetPossibleTransition(BuildInstantaneousDescription());
  while (next_transition != nullptr) {
    const std::string& next_state = next_transition->GetDestinyState();
    if (!turing_machines_states_.contains(next_state)) {
      throw TuringMachineException("Transition function contains a state that doesn't belong to turing machine possible states.");
    }
    if (next_transition->GetSymbolsToWrite().size() != inner_strings_.size() || 
      next_transition->GetHeadMovements().size() != inner_strings_.size()) {
      throw TuringMachineException("Transition function effects don't match the amount of strings.");
    }

    // Main logic
    for (size_t i{0}; i < inner_strings_.size(); ++i) {
      inner_strings_[i].Write(next_transition->GetSymbolsToWrite()[i]);
      inner_strings_[i].MoveHead(next_transition->GetHeadMovements()[i]);
    }
    current_state_ = next_state;
    next_transition = inner_transition_function_.GetPossibleTransition(BuildInstantaneousDescription());
  }

  return acceptance_automaton_states_.contains(current_state_);
}