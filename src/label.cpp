#include <iostream>
#include "utils.h"
#include "label.h"

/************* Label operators *************/

Label Label::operator+(const Label &other) {
  // Checks
  assert(this->lambda == other.lambda && "Unequal security parameter in label operator +") ;
  assert(this->max_value == other.max_value && "Unequal max_value in label operator +") ;
  assert(this->num_slots == other.num_slots && "Unequal number of slots in label operator +") ;

  // Create return object
  Label retlab(other) ;
  for (uint i = 0 ; i < this->num_slots ; i++)
    retlab.slots[i] = (this->slots[i] + other.slots[i]) % this->max_value ;

  // Return
  return retlab ;
}

Label Label::operator-(const Label &other) {
  // Checks
  assert(this->lambda == other.lambda && "Unequal security parameter in label operator -") ;
  assert(this->max_value == other.max_value && "Unequal max_value in label operator -") ;
  assert(this->num_slots == other.num_slots && "Unequal number of slots in label operator -") ;

  // Create return object
  Label retlab(other) ;
  std::uint64_t tmp ;
  for (uint i = 0 ; i < this->num_slots ; i++) {
    tmp = other.slots[i] ; // Assuming a > b by default
    if (tmp > this->slots[i]) { // If b > a
      tmp = this->max_value - 1 - other.slots[i] ;
      retlab.slots[i] = this->slots[i] + tmp ;
    } else // Normal case
      retlab.slots[i] = this->slots[i] - tmp ;
  }

  // Return
  return retlab ;
}

Label Label::operator*(const Label &other) {
  // Checks
  assert(this->lambda == other.lambda && "Unequal security parameter in label operator *") ;
  assert(this->max_value == other.max_value && "Unequal max_value in label operator *") ;
  assert(this->num_slots == other.num_slots && "Unequal number of slots in label operator *") ;

  // Create return object
  Label retlab(other) ;
  for (uint i = 0 ; i < this->num_slots ; i++)
    retlab.slots[i] = (this->slots[i] * other.slots[i]) % this->max_value ;

  // Return
  return retlab ;
}

Label Label::operator/(const Label &other) {
  // Checks
  assert(this->lambda == other.lambda && "Unequal security parameter in label operator +") ;
  assert(this->max_value == other.max_value && "Unequal max_value in label operator +") ;
  assert(this->num_slots == other.num_slots && "Unequal number of slots in label operator +") ;

  // Create return object
  Label retlab(other) ;
  for (uint i = 0 ; i < this->num_slots ; i++) {
    if (other.slots[i] == 0) {
      std::cerr << "Divide by zero error in Label division\n" ;
      exit(EXIT_FAILURE) ;
    }
    retlab.slots[i] = this->slots[i] / other.slots[i] ;
  }

  // Return
  return retlab ;
}


/************* ArithLabel operators *************/

ArithLabel ArithLabel::operator+(const ArithLabel &other) {
  Label ret_label = static_cast<Label&>(*this).operator+(other) ;
  return static_cast<ArithLabel&>(ret_label) ;
}

ArithLabel ArithLabel::operator-(const ArithLabel &other) {
  Label ret_label = static_cast<Label&>(*this).operator-(other) ;
  return static_cast<ArithLabel&>(ret_label) ;
}

ArithLabel ArithLabel::operator*(const ArithLabel &other) {
  Label ret_label = static_cast<Label&>(*this).operator*(other) ;
  return static_cast<ArithLabel&>(ret_label) ;
}

ArithLabel ArithLabel::operator/(const ArithLabel &other) {
  Label ret_label = static_cast<Label&>(*this).operator/(other) ;
  return static_cast<ArithLabel&>(ret_label) ;
}


/************* BMRLabel operators *************/

BMRLabel BMRLabel::operator+(const BMRLabel &other) {
  Label ret_label = static_cast<Label&>(*this).operator+(other) ;
  return static_cast<BMRLabel&>(ret_label) ;
}

BMRLabel BMRLabel::operator-(const BMRLabel &other) {
  Label ret_label = static_cast<Label&>(*this).operator-(other) ;
  return static_cast<BMRLabel&>(ret_label) ;
}

BMRLabel BMRLabel::operator*(const BMRLabel &other) {
  Label ret_label = static_cast<Label&>(*this).operator*(other) ;
  return static_cast<BMRLabel&>(ret_label) ;
}

BMRLabel BMRLabel::operator/(const BMRLabel &other) {
  Label ret_label = static_cast<Label&>(*this).operator/(other) ;
  return static_cast<BMRLabel&>(ret_label) ;
}


std::ostream operator<<(std::ostream &os, const Label& lab) {
  // TODO
}