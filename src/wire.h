#ifndef SWITCH_SYSTEMS_WIRE_H
#define SWITCH_SYSTEMS_WIRE_H

#include <iostream>
#include "utils.h"
#include "label.h"

typedef enum {
  UNSET, SET
} wirestat ;

/************************* Wire class *************************/

class Gate ;

class Wire {
public :
  wirestat stat = UNSET ;
  uint num_labs ;
  uint num_conns ;
  std::vector<Label> labs ;
  std::vector<Gate*> conns ;

  Wire() {}

  Wire (Wire &other) {
    this->stat = other.stat ;
    this->num_labs = other.num_labs ;
    for (uint i = 0 ; i < this->num_labs ; i++)
      this->labs[i] = other.labs[i] ;
  }
} ;

/************************* Gate class *************************/

class Gate {
public :
  static std::uint64_t max_gateid ;
  std::uint64_t gateid ;
  uint num_inputs ;
  uint num_outputs ;
  std::vector<Wire*> input_wires ;
  std::vector<Wire*> output_wires ;

  Gate() {
    this->gateid = max_gateid + 1 ;
    max_gateid++ ;
  }

  Gate (Gate &other) : Gate() {
    this->num_inputs = other.num_inputs ;
    this->num_outputs = other.num_outputs ;
    for (uint i = 0 ; i < this->num_inputs ; i++) 
      this->input_wires[i] = other.input_wires[i] ;
    for (uint i = 0 ; i < this->num_outputs ; i++)
      this->output_wires[i] = other.output_wires[i] ;
  }
} ;

void initialize_gateid() ;

/************************* Circuit class *************************/

class Circuit {
public :
  std::vector<Wire> wires ;
  std::vector<Gate> gates ;

  Circuit() {}
} ;

/************************* Garbler class *************************/

class Garbler {
public :
  Circuit circ ;
  uint lambda ;                       // Security parameter
  std::uint64_t delta ;               // Order of the ring/field the label exists in
  smalluint bitlength ;               // Number of bits required to hold an element of the ring i.e., bitlength = ceil(log_2(max_value+1))

  Garbler() {}
} ;

/************************* Evaluator class *************************/

class Evaluator {
public :
  Circuit circ ;
  std::vector<Wire> input_wires ;

  Evaluator() {}

  void evaluate() ;
} ;


#endif