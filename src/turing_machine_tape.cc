// University of La Laguna
// School of Engineering and Technology
// Bachelor's Degree in Computer Engineering
// Course: Computational Complexity
// Year: 4th
// Assignment 2: Turing Machine
// Author: Javier Acosta Portocarrero
// Date: 04/10/2026
// File turing_machine_tape.cc: implementation file.
// Contains the implementation of the TuringMachineTape class.

#include "../include/turing_machine_tape.h"
#include "../include/exceptions/turing_machine_tape_exception.h"

#include <stdexcept>

/**
 * @brief Default constructor for the TuringMachineTape class.
 * @param input_alphabet Set of symbols that form the input alphabet.
 * @param string_alphabet Set of symbols that form the string alphabet.
 * @param white_symbol Symbol representing the blank symbol in the Turing machine.
 */
TuringMachineTape::TuringMachineTape(const std::set<Symbol>& input_alphabet, const std::set<Symbol>& string_alphabet, Symbol white_symbol) 
    : input_alphabet_{input_alphabet}, string_alphabet_{string_alphabet}, white_symbol_{white_symbol} {
  inner_string_.emplace_back(white_symbol_);
  head_position_ = 0;
  head_ = inner_string_.begin();
}

/**
 * @brief Constructor for the TuringMachineTape class with an input word.
 * @param input_word Input word to be processed.
 * @param input_alphabet Set of symbols that form the input alphabet.
 * @param string_alphabet Set of symbols that form the string alphabet.
 * @param white_symbol Symbol representing the blank symbol in the Turing machine.
 */
TuringMachineTape::TuringMachineTape(const std::string& input_word, const std::set<Symbol>& input_alphabet, const std::set<Symbol>& string_alphabet, Symbol white_symbol) 
    : input_alphabet_{input_alphabet}, string_alphabet_{string_alphabet}, white_symbol_{white_symbol} {
  if (!CheckIfWholeInputWordIsInAlphabet(input_word)) {
    throw TuringMachineStringTape("The input word contains symbols that are not in the input alphabet.");
  }
  if (input_word == "") {
    inner_string_.emplace_back(white_symbol_); 
  } else {
    for (const Symbol& element : input_word) {
      inner_string_.emplace_back(element); 
    }
  }
  head_position_ = 0;
  head_ = inner_string_.begin();
}

/**
 * @brief Introduces a new input word.
 * 
 * @param input_word New input word.
 */
void TuringMachineTape::IntroduceNewInputWord(const std::string& input_word) {
  if (!CheckIfWholeInputWordIsInAlphabet(input_word)) {
    throw TuringMachineStringTape("The input word contains symbols that are not in the input alphabet.");
  }
  inner_string_.clear();
  if (input_word == "") {
    inner_string_.emplace_back(white_symbol_); 
  } else {
    for (const Symbol& element : input_word) {
      inner_string_.emplace_back(element); 
    }
  }
  head_position_ = 0;
  head_ = inner_string_.begin();
}

/**
 * @brief Returns the symbol where the head is.
 *
 * @return The symbol at the current head position.
 */
Symbol TuringMachineTape::GetCurrentSymbol() const {
  return *head_;
}

/**
 * @brief Moves the head of the Turing machine string.
 * 
 * @param movement The direction to move the head.
 */
void TuringMachineTape::MoveHead(StringMovements movement) {
  switch (movement) {
    case right:
      ++head_;
      ++head_position_;
      if (head_ == inner_string_.end()) {
        inner_string_.emplace_back(white_symbol_);
        head_ = --inner_string_.end();
      }
      break;
    case left:
      if (head_ == inner_string_.begin()) {
        inner_string_.emplace_front(white_symbol_);
      } else {
        --head_position_;
      }
      --head_;
      break;
    case stop:
      break;
    default:
      throw TuringMachineStringTape("Invalid head movement used.");
  }
}

/**
 * @brief Writes a new symbol at the current head position.
 * 
 * @param new_symbol The symbol to write.
 */
void TuringMachineTape::Write(Symbol new_symbol) {
  if (!string_alphabet_.contains(new_symbol)) {
    throw TuringMachineStringTape("Can't write a symbol that doesn't belong to the string alphabet.");
  }
  *head_ = new_symbol;
}

/**
 * @brief Checks if the entire input word is composed of symbols from the input alphabet.
 * 
 * @param input_word Input word to be checked.
 * @return true if the input word is valid, false otherwise.
 */
bool TuringMachineTape::CheckIfWholeInputWordIsInAlphabet(const std::string& input_word) const {
  for (const Symbol& symbol : input_word) {
    if (!input_alphabet_.contains(symbol)) {
      return false;
    }
  }
  return true;
}

/**
 * @brief Returns the string representation of the Turing machine string,
 *        consisting of the symbols in the string with the current head position marked by brackets.
 * 
 * @return The string representation.
 */
const std::string TuringMachineTape::GetStringRepresentation() const {
  std::string representation = "";
  unsigned iterator = 0;
  for (const Symbol& element : inner_string_) {
    if (iterator++ == head_position_) {
      representation += '[';
      representation += element;
      representation += ']';
    } else {
      representation += element;
    }
  }

  return representation;
}

/**
 * @brief Resets the Turing machine string to its initial state, clearing the string and setting the head position to the beginning.
 */
void TuringMachineTape::Reset() {
  inner_string_.clear();
  inner_string_.emplace_back(white_symbol_); 
  head_position_ = 0;
  head_ = inner_string_.begin();
}