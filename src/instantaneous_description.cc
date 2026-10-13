// University of La Laguna
// School of Engineering and Technology
// Bachelor's Degree in Computer Engineering
// Course: Computational Complexity
// Year: 4th
// Assignment 2: Turing Machine
// Author: Javier Acosta Portocarrero
// Date: 04/10/2026
// File instantaneous_description.cc: implementation file.
// Contains the implementation of the InstantaneousDescription struct.

#include "../include/instantaneous_description.h"

/**
 * @brief Compares two InstantaneousDescription objects for ordering.
 * 
 * @param other_description The other InstantaneousDescription to compare with.
 * @return true if this InstantaneousDescription is less than the other, false otherwise, 
 *         based on lexicographical order of state and entry_symbols.
 */
bool InstantaneousDescription::operator<(const InstantaneousDescription& other_description) const {
  if (state_ != other_description.state_) {
    return state_ < other_description.state_;
  }
  return entry_symbols_ < other_description.entry_symbols_;
}
  


