// University of La Laguna
// School of Engineering and Technology
// Bachelor's Degree in Computer Engineering
// Course: Computational Complexity
// Year: 4th
// Assignment 2: Turing Machine
// Author: Javier Acosta Portocarrero
// Date: 04/10/2026
// File turing_machine_string.h: declaration file.
// Contains the declaration of the TuringMachineString class.

#ifndef INPUT_STRING_H
#define INPUT_STRING_H

#include <string>
#include <set>
#include <list>

using Symbol = char;

enum StringMovements {
  right,
  left,
  stop
};

class TuringMachineString {
 public:
  TuringMachineString(const std::set<Symbol>& input_alphabet, const std::set<Symbol>& string_alphabet, Symbol white_symbol);
  TuringMachineString(const std::string& input_word, const std::set<Symbol>& input_alphabet, const std::set<Symbol>& string_alphabet, Symbol white_symbol);

  Symbol GetCurrentSymbol() const;
  const std::string& GetStringRepresentation() const;
  unsigned GetCurrentHeadIndex() const { return head_position_;}

  void MoveHead(StringMovements movement);
  void Write(Symbol new_symbol);

  void IntroduceNewInputWord(const std::string& input_word);
 private:
  std::list<Symbol> inner_string_;
  unsigned head_position_ = 0;
  std::list<Symbol>::iterator head_;
  // Reference to the original alphabet from the turing machine.
  const std::set<Symbol>& input_alphabet_;
  const std::set<Symbol>& string_alphabet_;

  Symbol white_symbol_;

  bool CheckIfWholeInputWordIsInAlphabet(const std::string& input_word) const;
};

#endif