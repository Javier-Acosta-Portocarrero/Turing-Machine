// University of La Laguna
// School of Engineering and Technology
// Bachelor's Degree in Computer Engineering
// Course: Computational Complexity
// Year: 4th
// Assignment 2: Turing Machine
// Author: Javier Acosta Portocarrero
// Date: 04/10/2026
// File instantaneous_description.h: declaration file.
// Contains the declaration of the InstantaneousDescription struct.

#ifndef INSTANTANEOUS_DESCRIPTION_H
#define INSTANTANEOUS_DESCRIPTION_H

#include <string>

using Symbol = char;

struct InstantaneousDescription {
  InstantaneousDescription(const std::string& state, const std::string& entry_symbols) 
      : state_{state}, entry_symbols_{entry_symbols} {}
  
  const std::string& state_;
  // Not a reference because it is built only to be stored here. 
  const std::string entry_symbols_;  // One symbol per string.  
};

#endif