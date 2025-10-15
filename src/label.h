#ifndef SWITCH_SYSTEMS_LABEL_H
#define SWITCH_SYSTEMS_LABEL_H

#include <iostream>
#include <cassert>
#include <vector>
#include "utils.h"

/************************* Label class *************************/

class Label {
public :
  // General attributes
  meduint lambda ;                        // meduint : scalable, can be > 256 --> Security parameter
  std::uint64_t max_value ;               // uint64_t : full unsigned integer -->  o-1 where o = order of the ring/field the label exists
  smalluint bitlength ;                   // smalluint : less than 256 --> Number of bits required to hold an element of the ring i.e., bitlength = ceil(log_2(max_value+1))
  meduint loss ;                          // meduint : small integer < lambda --> bits of entropy loss

  // Entropy attributes
  meduint entropy_slots ;                 // meduint : <= lambda --> Number of slots for holding entropy
  std::vector<std::uint64_t> slots ;      // vector<uint64_t> --> each slot has a full unsigned integer. list of :entropy_slots: slots
  std::uint64_t color ;                   // uint64_t --> same datatype as entropy slot. Color slots

  /**** Helper constructor functions ****/

  // Initialize all slots to 0ULL
  void initialize_slots(std::uint64_t v=0ULL) {
    this->slots = std::vector<std::uint64_t>(this->entropy_slots, fix_fill(v, this->max_value)) ;
  }

  // Set color
  void set_color(std::uint64_t v=0ULL) {
    this->color = fix_fill(v, this->max_value) ;
  }

  /**** Constructors ****/

  // Default Constructor
  Label() {} ;
  
  // Constructor with security parameter and max value
  Label(meduint l, std::uint64_t mv) {
    // Checking for positive security parameter
    assert(l > 0 && "Label security parameter must be > 0\n") ;
    this->lambda = l ;

    // Checking that order of ring is positive
    assert(mv > 0 && "Ring maximum value must be >= 0\n") ;
    this->max_value = mv ;

    // Compute bitlength efficiently
    this->bitlength = get_bitlength(this->max_value) ;

    // Set loss
    this->loss = 0 ;

    // Set slots
    this->entropy_slots = 0 ;
    this->color = 0ULL ;
  }

  // Constructor with emp::block and reference label
  Label(emp::block blk, Label &other) {
    // Copy attributes
    this->lambda = other.lambda ;
    this->max_value = other.max_value ;
    this->bitlength = other.bitlength ;
    this->loss = other.loss ;

    
   }

  // Constructor with security param, max value, number of slots, color
  Label(meduint l, std::uint64_t mv, std::uint64_t ns, std::uint64_t val=0ULL, std::uint64_t col=0ULL, meduint loss=0ULL) : Label(l, mv) {
    this->entropy_slots = ns ;
    this->initialize_slots(val) ;
    this->color = col ;
    this->loss = loss ;
  }

  // Copy constructor
  Label(const Label &other) {
    // Copy attributes
    this->lambda = other.lambda ;
    this->max_value = other.max_value ;
    this->bitlength = other.bitlength ;
    this->loss = other.loss ;

    // Copy slots
    this->entropy_slots = other.entropy_slots ;
    this->initialize_slots() ;
    for (uint i = 0 ; i < this->entropy_slots ; i++)
      this->slots[i] = other.slots[i] ;
    this->color = other.color ;
  }

  /**** Operators ****/

  Label operator+(const Label &other) ;
  Label operator-(const Label &other) ;
  Label operator*(const Label &other) ;
  Label operator/(const Label &other) ; 

  /**** Methods ****/

  emp::block to_block() ;
} ;

std::ostream& operator<< (std::ostream &os, const Label& lab) ;

/************************* ArithLabel class *************************/

class ArithLabel : public Label {
public :
  // Derived attributes
  smalluint width ;   // width of label

  /**** Constructors ****/

  // Default Constructor
  ArithLabel() : Label() {} ;

  // Constructor with security parameter and width
  ArithLabel(meduint l, std::uint64_t w) : Label(l, width_to_maxval(w)), width(w) {
    // Check width
    assert(w > 0 && w <= 64 && "Width of label must be between 1 and 64") ;
    this->width = w ;

    // An arithmetic label has as many slots as the security parameter - 1 (to account for color bits)
    this->entropy_slots = this->lambda - 1 ;
    this->initialize_slots() ;
    this->color = 0ULL ;
  }

  // Constructor with block and reference label
  ArithLabel(emp::block &blk, ArithLabel &other) { ; }

  // Copy constructor
  ArithLabel(const ArithLabel &other) : Label(other) {
    this->width = other.width ;
  }

  /**** Operators ****/

  ArithLabel operator+(const ArithLabel &other) ;
  ArithLabel operator-(const ArithLabel &other) ;
  ArithLabel operator*(const ArithLabel &other) ;
  ArithLabel operator/(const ArithLabel &other) ;
} ;

/************************* BMRLabel class *************************/

class BMRLabel : public Label {
public :
  // Derived attributes
  smalluint pr ;                // smalluint : prime < 256 --> prime finite field

  /**** Constructors ****/

  // Default Constructor
  BMRLabel() : Label() {} ;

  // Constructor with security parameter and maximum value
  BMRLabel(std::size_t l, smalluint p) : Label(l, p - 1) {
    // Check for prime and initialize Label
    assert(check_prime(p) && "Must be a Z_p finite field\n") ;

    // Number of slots is ceil(lambda / bitlength) - 1 (to account for color bits)
    this->entropy_slots = FLOOR_DIV(this->lambda, this->bitlength) - 1 ;   // Macro usage is valid because numerator is non-zero
    assert(this->entropy_slots > 0 && "BMRLabel has no entropy") ;

    // Compute loss
    this->loss = this->lambda - (this->entropy_slots + 1)*this->bitlength ;   // e = lambda - (n+1)l see PhD notes Oct 06, 2025

    // Fill slots
    this->initialize_slots() ;
    this->color = 0ULL ;
  }

  // Constructor with block and reference label
  BMRLabel(emp::block &blk, BMRLabel &other) { ; }

  // Copy constructor
  BMRLabel(const BMRLabel &other) : Label(other) {
    this->pr = other.pr ;
  }

  /**** Operators ****/

  BMRLabel operator+(const BMRLabel &other) ;
  BMRLabel operator-(const BMRLabel &other) ;
  BMRLabel operator*(const BMRLabel &other) ;
  BMRLabel operator/(const BMRLabel &other) ;
} ;


/************************* Methods *************************/

// Constant label
template <class T>
T const_label(T &other, std::uint64_t val) {
  T retlab(other) ;
  for (uint i = 0 ; i < other.entropy_slots ; i++)
    retlab.slots[i] = val ;
  return retlab ;
}

#endif