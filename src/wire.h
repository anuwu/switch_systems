#ifndef SWITCH_SYSTEMS_WIRE_H
#define SWITCH_SYSTEMS_WIRE_H

#include <iostream>
#include "utils.h"
#include "label.h"

class Wire {
public :
  uint lambda ;
  std::uint64_t max_value ;
  string label_type ;
  std::uint64_t val ;
  Label lab ;

  Wire(uint l, std::uint64_t mv, string lt, std::uint64_t v) : max_value(mv), label_type(lt), val(v) {
    if (label_type == "arith") {
      this->lab = ArithLabel(this->lambda, this->max_value) ;
    } else if (label_type == "label") {
      this->lab = BMRLabel(this->lambda, this->max_value) ;
    }
  }
} ;

// class CRTWire ;

#endif