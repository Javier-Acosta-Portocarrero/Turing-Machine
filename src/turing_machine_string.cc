// University of La Laguna
// School of Engineering and Technology
// Bachelor's Degree in Computer Engineering
// Course: Computational Complexity
// Year: 4th
// Assignment 2: Turing Machine
// Author: Javier Acosta Portocarrero
// Date: 04/10/2026
// File turing_machine_string.cc: implementation file.
// Contains the implementation of the TuringMachineString class.

#include "../include/turing_machine_string.h"
#include "../include/exceptions/turing_machine_string_exception.h"

#include <stdexcept>

const char WHITE_SYMBOL = '&';

/**
 * @brief Default constructor for the TuringMachineString class.
 * 
 * @param
 * @param
 */
TuringMachineString::TuringMachineString(const std::set<Symbol>& input_alphabet, const std::set<Symbol>& string_alphabet) 
    : input_alphabet_{input_alphabet}, string_alphabet_{string_alphabet} {
  inner_string_.emplace_back(WHITE_SYMBOL);
  head_position_ = 0;
  head_ = inner_string_.begin();
}

/**
 * @brief Constructor for the TuringMachineString class with an input word.
 * @param input_word Input word to be processed.
 * @param input_alphabet Set of symbols that form the input alphabet.
 * @param
 */
TuringMachineString::TuringMachineString(const std::string& input_word, const std::set<Symbol>& input_alphabet, const std::set<Symbol>& string_alphabet) 
    : input_alphabet_{input_alphabet}, string_alphabet_{string_alphabet} {
  if (!CheckIfWholeInputWordIsInAlphabet(input_word)) {
    throw TuringMachineStringException("The input word contains symbols that are not in the input alphabet.");
  }
  if (input_word == "") {
    inner_string_.emplace_back(WHITE_SYMBOL); 
  } else {
    for (const Symbol& element : input_word) {
      inner_string_.emplace_back(element); 
    }
  }
  head_position_ = 0;
  head_ = inner_string_.begin();
}

/**
 * @brief Sets a new input word.
 *
 * @param input_word New input word.
 */
void TuringMachineString::IntroduceNewInputWord(const std::string& input_word) {
  if (!CheckIfWholeInputWordIsInAlphabet(input_word)) {
    throw TuringMachineStringException("The input word contains symbols that are not in the input alphabet.");
  }
  inner_string_.clear();
  for (const Symbol& element : input_word) {
    inner_string_.emplace_back(element); 
  }
  head_position_ = 0;
  head_ = inner_string_.begin();
}

/**
 * @brief Returns the symbol where the head is.
 *
 * @return The symbol.
 */
Symbol TuringMachineString::GetCurrentSymbol() const {
  return *head_;
}

/**
 * 
 */
void TuringMachineString::MoveHead(StringMovements movement) {
  switch (movement) {
    case right:
    ++head_;
      ++head_position_;
      if (head_ == inner_string_.end()) {
        inner_string_.emplace_back(WHITE_SYMBOL);
      }
      break;
    case left:
      if (head_ == inner_string_.begin()) {
        inner_string_.emplace_front(WHITE_SYMBOL);
      }
      --head_;
      --head_position_;
      break;
    case stop:
      break;
    default:
      throw TuringMachineStringException("Invalid head movement used.");
  }
}

/**
 * 
 */
void TuringMachineString::Write(Symbol new_symbol) {
  if (!string_alphabet_.contains(symbol)) {
    throw TuringMachineStringException("Can't write a symbol that doesn't belong to the string alphabet.");
  }
  *head_ = new_symbol;
}

/**
 * @brief Checks if the entire input word is composed of symbols from the input alphabet.
 * @param input_word Input word to be checked.
 * @return true if the input word is valid, false otherwise.
 */
bool TuringMachineString::CheckIfWholeInputWordIsInAlphabet(const std::string& input_word) const {
  for (const Symbol& symbol : input_word) {
    if (!input_alphabet_.contains(symbol)) {
      return false;
    }
  }
  return true;
}