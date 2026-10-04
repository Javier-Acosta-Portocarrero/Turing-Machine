// University of La Laguna
// School of Engineering and Technology
// Bachelor's Degree in Computer Engineering
// Course: Computational Complexity
// Year: 4th
// Assignment 1: Pushdown Automaton
// Author: Javier Acosta Portocarrero
// Date: 24/09/2026
// File transition_function.cc: implementation file.
// Contains the implementation of the TransitionFunction class.

#include "../include/transition_function.h"


/**
 * 
 */
const TransitionEffects* TransitionFunction::GetPossibleTransition(const InstantaneousDescription& requirements) const {
  auto description = inner_transition_table_.find(requirements);
  if (description == inner_transition_table_.end()) {
    return nullptr;
  }

  return &(description->second);
}

/**
 * 
 */
void TransitionFunction::AddNewTransition(const InstantaneousDescription& requirements, const TransitionEffects& output) {
  inner_transition_table_.insert(std::make_pair(requirements, output)); 
}