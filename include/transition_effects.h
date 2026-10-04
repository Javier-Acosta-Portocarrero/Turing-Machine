// University of La Laguna
// School of Engineering and Technology
// Bachelor's Degree in Computer Engineering
// Course: Computational Complexity
// Year: 4th
// Assignment 2: Turing Machine
// Author: Javier Acosta Portocarrero
// Date: 04/10/2026
// File transition_effects.h: declaration file.
// Contains the declaration of the TransitionEffects class.

#ifndef TRANSITION_EFFECT_H
#define TRANSITION_EFFECT_H

#include "string_movements.h"

#include <string>
#include <vector>

using Symbol = char;

class TransitionEffects {
 public:
  TransitionEffects(const std::string& destiny_state, const std::vector<Symbol>& symbols_to_write, const std::vector<StringMovements>& head_movement) 
      : destiny_state_{destiny_state}, symbols_to_write_{symbols_to_write}, head_movements_{head_movement} {}

  const std::string& GetDestinyState() const { return destiny_state_;}
  const std::vector<Symbol>& GetSymbolToWrite() const { return symbols_to_write_;}
  const std::vector<StringMovements>& GetHeadMovement() const { return head_movements_;}

 private:
  const std::string destiny_state_;
  const std::vector<Symbol> symbols_to_write_;
  const std::vector<StringMovements> head_movements_;

};

#endif