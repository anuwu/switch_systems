#ifndef SWITCH_SYSTEMS_LABEL_H
#define SWITCH_SYSTEMS_LABEL_H

#include <iostream>
#include <cassert>
#include <vector>
#include "utils.h"

/************************* Label class *************************/

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

  Label(uint l, std::uint64_t mv, std::uint64_t nsm, std::uint64_t val=0ULL) : Label(l, mv) {
    this->num_slots = 0 ;
    for (uint i = 0 ; i < this->num_slots ; i++)
      this->slots[i] = val ;
  }

  // Copy constructor
  Label(const Label &other) {
    this->lambda = other.lambda ;
    this->max_value = other.max_value ;
    this->bitlength = other.bitlength ;
    this->num_slots = other.num_slots ;
    this->slots = std::vector<std::uint64_t>(this->num_slots, 0ULL) ;
    for (uint i = 0 ; i < this->num_slots ; i++)
      this->slots[i] = other.slots[i] ;
  }

  // Operators for labels
  Label operator+(const Label &other) ;
  Label operator-(const Label &other) ;
  Label operator*(const Label &other) ;
  Label operator/(const Label &other) ;
} ;

std::ostream operator<<(std::ostream &os, const Label& lab) ;

/************************* ArithLabel class *************************/

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

  // Copy constructor
  ArithLabel(const ArithLabel &other) : Label(other) {}

  // // Operators for labels
  ArithLabel operator+(const ArithLabel &other) ;
  ArithLabel operator-(const ArithLabel &other) ;
  ArithLabel operator*(const ArithLabel &other) ;
  ArithLabel operator/(const ArithLabel &other) ;
} ;

/************************* BMRLabel class *************************/

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

  // Copy constructor
  BMRLabel(const BMRLabel &other) : Label(other) {}

  // Operators for labels
  BMRLabel operator+(const BMRLabel &other) ;
  BMRLabel operator-(const BMRLabel &other) ;
  BMRLabel operator*(const BMRLabel &other) ;
  BMRLabel operator/(const BMRLabel &other) ;
} ;

// Constant label
template <class T>
T const_label(T &other, std::uint64_t val) {
  std::cout << "In this template function" << "\n" ;
  T retlab(other) ;
  for (uint i = 0 ; i < other.num_slots ; i++)
    retlab.slots[i] = val ;
  return retlab ;
}

#endif