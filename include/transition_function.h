// University of La Laguna
// School of Engineering and Technology
// Bachelor's Degree in Computer Engineering
// Course: Computational Complexity
// Year: 4th
// Assignment 2: Turing Machine
// Author: Javier Acosta Portocarrero
// Date: 04/10/2026
// File transition_function.h: declaration file.
// Contains the declaration of the TransitionFunction class.

#ifndef TRANSITION_FUNCTION_H
#define TRANSITION_FUNCTION_H

#include "transition_effects.h"
#include "instantaneous_description.h"

#include <map>
#include <set>

using Symbol = char;

class TransitionFunction {
 public:
  TransitionFunction() = default;
  TransitionFunction(const std::map<InstantaneousDescription, TransitionEffects> transition_table) 
      :  inner_transition_table_{transition_table} {}

  const TransitionEffects* GetPossibleTransition(const InstantaneousDescription& requirements) const;
  void AddNewTransition(const InstantaneousDescription& requirements, const TransitionEffects& output);
 private:
  std::map<InstantaneousDescription, TransitionEffects> inner_transition_table_;
};

#endif