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

using Symbol = char;

class TransitionEffects {
 public:
  TransitionEffects(const std::string& destiny_state, Symbol symbol_to_write, StringMovements head_movement) 
      : destiny_state_{destiny_state}, symbol_to_write_{symbol_to_write}, head_movement_{head_movement} {}

  const std::string& GetDestinyState() const { return destiny_state_;}
  Symbol GetSymbolToWrite() const { return symbol_to_write_;}
  StringMovements GetHeadMovement() const { return head_movement_;}

 private:
  const std::string destiny_state_;
  const Symbol symbol_to_write_;
  const StringMovements head_movement_;

};

#endif