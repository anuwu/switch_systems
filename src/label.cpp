#include <iostream>
#include <bitset>
#include "utils.h"
#include "label.h"

/************* Label class *************/

// Label addition operator
Label Label::operator+(const Label &other) {
  // Checks
  assert(this->lambda == other.lambda && "Unequal security parameter in label operator +") ;
  assert(this->max_value == other.max_value && "Unequal max_value in label operator +") ;
  assert(this->entropy_slots == other.entropy_slots && "Unequal number of slots in label operator +") ;

  // Create return object
  Label retlab(other) ;
  for (uint i = 0 ; i < this->entropy_slots ; i++)
    retlab.slots[i] = (this->slots[i] + other.slots[i]) % this->max_value ;

  // Return
  return retlab ;
}

// Label subtraction operator
Label Label::operator-(const Label &other) {
  // Checks
  assert(this->lambda == other.lambda && "Unequal security parameter in label operator -") ;
  assert(this->max_value == other.max_value && "Unequal max_value in label operator -") ;
  assert(this->entropy_slots == other.entropy_slots && "Unequal number of slots in label operator -") ;

  // Create return object
  Label retlab(other) ;
  std::uint64_t tmp ;
  for (uint i = 0 ; i < this->entropy_slots ; i++) {
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

// Label multiplication operator
Label Label::operator*(const Label &other) {
  // Checks
  assert(this->lambda == other.lambda && "Unequal security parameter in label operator *") ;
  assert(this->max_value == other.max_value && "Unequal max_value in label operator *") ;
  assert(this->entropy_slots == other.entropy_slots && "Unequal number of slots in label operator *") ;

  // Create return object
  Label retlab(other) ;
  for (uint i = 0 ; i < this->entropy_slots ; i++)
    retlab.slots[i] = (this->slots[i] * other.slots[i]) % this->max_value ;

  // Return
  return retlab ;
}

// Label division operator
Label Label::operator/(const Label &other) {
  // Checks
  assert(this->lambda == other.lambda && "Unequal security parameter in label operator +") ;
  assert(this->max_value == other.max_value && "Unequal max_value in label operator +") ;
  assert(this->entropy_slots == other.entropy_slots && "Unequal number of slots in label operator +") ;

  // Create return object
  Label retlab(other) ;
  for (uint i = 0 ; i < this->entropy_slots ; i++) {
    if (other.slots[i] == 0) {
      std::cerr << "Divide by zero error in Label division\n" ;
      exit(EXIT_FAILURE) ;
    }
    retlab.slots[i] = this->slots[i] / other.slots[i] ;
  }

  // Return
  return retlab ;
}

// Label to block
emp::block Label::to_block() {
  // Iinitialize block to be return
  emp::block ret_blk = emp::zero_block ;

  emp::block slot_blk ;
  for (meduint i = 0 ; i < this->entropy_slots ; i++) {
    // Make block out of a slot. Put slot value in LSB. 
    slot_blk = emp::makeBlock(0ULL, this->slots[i]) ;

    // Shift slot to the right place
    slot_blk = left_shift(slot_blk, i*this->bitlength) ;

    // Accumulate slot into return block
    xorBlocks_arr(&ret_blk, &slot_blk, 1) ;
  }

  // Accumulate color lot into block
  slot_blk = emp::makeBlock(0ULL, this->color) ;
  slot_blk = left_shift(slot_blk, this->bitlength*this->entropy_slots) ;
  xorBlocks_arr(&ret_blk, &slot_blk, 1) ;

  // Return
  return ret_blk ;
}

// Label ostream
std::ostream& operator<< (std::ostream &os, const Label& lab) {
  // Scratch variable for processing
  string st ;

  // Dashed lines
  string bigdash = string(lab.bitlength + 32, '=') ;
  string smalldash = string(lab.bitlength + 32, '-') ;
  os << bigdash << "\n" ;
  
  // Print entropy slots
  os << "E - \t" ;
  st = std::bitset<64>(lab.slots[0]).to_string().substr(64 - lab.bitlength, lab.bitlength) ;
  os << st << " --> " << lab.slots[0] << "\n" ;
  for (meduint i = 1 ; i < lab.entropy_slots ; i++) {
    st = std::bitset<64>(lab.slots[i]).to_string().substr(64 - lab.bitlength, lab.bitlength) ;
    os << "\t" << st << " --> " << lab.slots[i] << "\n" ;
  }
  os << smalldash << "\n" ;

  // Print color bit
  os << "C - \t" ;
  st = std::bitset<64>(lab.color).to_string().substr(64 - lab.bitlength, lab.bitlength) ;
  os << st << " --> " << lab.color << "\n" ;

  // Print useless bits
  os << smalldash << "\n" ;
  os << "U - \t" ;
  st = string(lab.loss, 'x') ; 
  os << st << "\n" ;

  // Print dashes again
  os << bigdash << "\n" ;

  return os ;
}


/************* ArithLabel *************/

// ArithLabel addition operator
ArithLabel ArithLabel::operator+(const ArithLabel &other) {
  Label ret_label = static_cast<Label&>(*this).operator+(other) ;
  return static_cast<ArithLabel&>(ret_label) ;
}

// ArithLabel subtraction operator
ArithLabel ArithLabel::operator-(const ArithLabel &other) {
  Label ret_label = static_cast<Label&>(*this).operator-(other) ;
  return static_cast<ArithLabel&>(ret_label) ;
}

// ArithLabel multiplication operator
ArithLabel ArithLabel::operator*(const ArithLabel &other) {
  Label ret_label = static_cast<Label&>(*this).operator*(other) ;
  return static_cast<ArithLabel&>(ret_label) ;
}

// ArithLabel division operator
ArithLabel ArithLabel::operator/(const ArithLabel &other) {
  Label ret_label = static_cast<Label&>(*this).operator/(other) ;
  return static_cast<ArithLabel&>(ret_label) ;
}


/************* BMRLabel *************/

// BMRLabel addition operator
BMRLabel BMRLabel::operator+(const BMRLabel &other) {
  Label ret_label = static_cast<Label&>(*this).operator+(other) ;
  return static_cast<BMRLabel&>(ret_label) ;
}

// BMRLabel subtraction operator
BMRLabel BMRLabel::operator-(const BMRLabel &other) {
  Label ret_label = static_cast<Label&>(*this).operator-(other) ;
  return static_cast<BMRLabel&>(ret_label) ;
}

// BMRLabel multiplication operator
BMRLabel BMRLabel::operator*(const BMRLabel &other) {
  Label ret_label = static_cast<Label&>(*this).operator*(other) ;
  return static_cast<BMRLabel&>(ret_label) ;
}

// BMRLabel division operator
BMRLabel BMRLabel::operator/(const BMRLabel &other) {
  Label ret_label = static_cast<Label&>(*this).operator/(other) ;
  return static_cast<BMRLabel&>(ret_label) ;
}