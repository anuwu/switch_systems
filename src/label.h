#ifndef SWITCH_SYSTEMS_LABEL_H
#define SWITCH_SYSTEMS_LABEL_H

#include <iostream>
#include <cassert>
#include <vector>
#include "utils.h"

class Label {
public :
  // Attributes
  uint lambda ;                       // Security parameter
  std::uint64_t max_value ;           // Order of the ring/field the label exists in
  smalluint bitlength ;               // Number of bits required to hold an element of the ring i.e., bitlength = ceil(log_2(max_value+1))
  std::uint64_t num_slots ;           // Number of slots for holding entropy
  std::vector<std::uint64_t> slots ;  // Vector of slots

  // Default Constructor
  Label() {} ;
  
  // Constructor with security parameter and max value
  Label(uint l, std::uint64_t mv) : lambda(l), max_value(mv) {
    // Checking for positive security parameter
    assert(this->lambda > 0 && "Label security parameter must be > 0\n") ;

    // Checking that order of ring is positive
    assert(this->lambda > 0 && "Ring maximum value must be >= 0\n") ;

    // Compute bitlength efficiently
    this->bitlength = get_bitlength(this->max_value) ;

    // Set slots
    this->num_slots = 0 ;
  }
} ;

class ArithLabel : public Label {
public :
  // Default Constructor
  ArithLabel() {} ;

  // Constructor with security parameter and max value
  ArithLabel(uint l, std::uint64_t mv) : Label(l, mv) {
    // An arithmetic label has as many slots as the security parameter
    this->num_slots = this->lambda ;
    this->slots = std::vector<std::uint64_t>(this->lambda, 0ULL) ;
  }
} ;

class BMRLabel : public Label {
public :
  // Default Constructor
  BMRLabel() {} ;

  // Constructor with security parameter and maximum value
  BMRLabel(std::size_t l, std::uint64_t mv) : Label(l, mv) {
    // Number of slots is ceil(lambda / bitlength).
    this->num_slots = CEIL_DIV(this->lambda, this->bitlength) ;   // Macro usage is valid because numerator is non-zero

    // Fill slots
    this->slots = std::vector<std::uint64_t>(this->num_slots, 0ULL) ;
  }
} ;

#endif