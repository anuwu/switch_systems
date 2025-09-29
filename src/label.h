#ifndef SWITCH_SYSTEMS_LABEL_H
#define SWITCH_SYSTEMS_LABEL_H

#include <iostream>
#include <vector>
#include "utils.h"

class Label {
public :
  uint lambda ;                       // Security parameter
  std::uint64_t max_value ;           // Order of the ring/field the label exists in
  smalluint bitlength ;               // Number of bits required to hold an element of the ring i.e., bitlength = ceil(log_2(max_value+1))

  // Default Constructor
  Label() {} ;
  
  // Constructor with security parameter and max value
  Label(uint l, std::uint64_t mv) : lambda(l), max_value(mv) {
    // Checking for positive security parameter
    if (this->lambda <= 0) {
      std::cerr << "Label security parameter must be > 0\n" ; 
      exit(EXIT_FAILURE) ;
    }

    // Checking that order of ring is positive
    if (this->max_value < 0) {
      std::cerr << "Ring maximum value must be >= 0\n" ;
      exit(EXIT_FAILURE) ;
    }

    // Compute bitlength efficiently
    this->bitlength = get_bitlength(this->max_value) ;
  }
} ;

class ArithLabel : public Label {
public :
  std::uint64_t num_slots ;
  std::vector<std::uint64_t> slots ;

  // Default Constructor
  ArithLabel() {} ;

  // Constructor with security parameter and max value
  ArithLabel(uint l, std::uint64_t mv) : Label(l, mv), num_slots(lambda) {
    // An arithmetic label has as many slots as the security parameter
    this->slots = std::vector<std::uint64_t>(this->lambda, 0ULL) ;
  }
} ;

class BMRLabel : public Label {
public :
  std::uint64_t num_slots ;
  std::vector<std::uint64_t> slots ;

  // Default Constructor
  BMRLabel() {} ;

  // Constructor with security parameter and maximum value
  BMRLabel(std::size_t l, std::uint64_t mv) : Label(l, mv) {
    // Number of slots is ceil(lambda / bitlength)
    this->num_slots = this->lambda / this->bitlength ;
    if (this->lambda % this->bitlength)
      this->num_slots += 1 ;

    // Fill slots
    this->slots = std::vector<std::uint64_t>(this->num_slots, 0ULL) ;
  }
} ;

#endif