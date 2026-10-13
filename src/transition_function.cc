// University of La Laguna
// School of Engineering and Technology
// Bachelor's Degree in Computer Engineering
// Course: Computational Complexity
// Year: 4th
// Assignment 2: Turing Machine
// Author: Javier Acosta Portocarrero
// Date: 04/10/2026
// File transition_function.cc: implementation file.
// Contains the implementation of the TransitionFunction class.

#include "../include/transition_function.h"


/**
 * @brief Gets the possible transition for the given requirements.
 * 
 * @param requirements The instantaneous description representing the requirements.
 * @return A pointer to the transition effects if a transition is found, nullptr otherwise.
 */
const TransitionEffects* TransitionFunction::GetPossibleTransition(const InstantaneousDescription& requirements) const {
  auto description = inner_transition_table_.find(requirements);
  if (description == inner_transition_table_.end()) {
    return nullptr;
  }

  return &(description->second);
}

/**
 * @brief Adds a new transition to the function.
 * 
 * @param requirements The instantaneous description representing the requirements.
 * @param output The transition effects to add.
 */
void TransitionFunction::AddNewTransition(const InstantaneousDescription& requirements, const TransitionEffects& output) {
  inner_transition_table_.insert(std::make_pair(requirements, output)); 
}