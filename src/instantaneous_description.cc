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
 * 
 */
bool InstantaneousDescription::operator<(const InstantaneousDescription& other_description) const {
    return state_ < other_description.state_ || entry_symbols_ < other_description.entry_symbols_;
}
  


