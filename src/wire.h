#ifndef SWITCH_SYSTEMS_WIRE_H
#define SWITCH_SYSTEMS_WIRE_H

#include <iostream>
#include <vector>
#include "utils.h"
#include "label.h"

// Enum class to denote if a wire has been set
typedef enum {
  UNSET, SET
} wirestat ;

/************************* Wire class *************************/

class Gate ;

class Wire {
public :
  wirestat stat = UNSET ;           // Wire is initially unset 
  smalluint num_labs ;              // smalluint : CRT moduli < 256 --> size of the bundle of labels
  meduint num_conns ;               // meduint : assuming number of connections to a wire < 2^16 --> number of gates a wire connects to
  std::vector<Label> labs ;         // list of :num_labs: labels
  std::vector<Gate*> conns ;        // list of :num_conns: gates

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
  static uint max_gateid ;            // uint : bigger than (Wire::num_conns):meduint --> Maximum gateid of a gate in a circuit. Common to all Gate objects.
  uint gateid ;                       // uint : following max_gateid --> Gate identification number for this gate
  meduint num_inputs ;                // meduint : following (Wire::num_conns):meduint --> Number of inputs to the gate
  meduint num_outputs ;               // meduint : following :num_inputs: --> Number of outputs of the gate
  std::vector<Wire*> input_wires ;    // List of :num_inputs: wires
  std::vector<Wire*> output_wires ;   // List of :num_outputs: wires

  // Default Constructor
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
  std::vector<Wire> wires ;           // list of wires in the circuit
  std::vector<Gate> gates ;           // list of all gates in the circuit

  Circuit() {}
} ;

/************************* Garbler class *************************/

class Garbler {
public :
  Circuit circ ;                          // Circuit to be garbled
  meduint lambda ;                        // meduint : scalable, can be > 256 --> Security parameter
  smalluint bitlength ;                   // smalluint : less than 256 --> Number of bits required to hold an element of the ring i.e., bitlength = ceil(log_2(max_value+1))

  Garbler() {}
} ;

class ArithGarbler : public Garbler {
public :
  smalluint max_width ;               // smalluint : width of wires < 256 --> maximum width of any wire in the circuit
  Label delta ;                       // Global correlation

  ArithGarbler() : Garbler() {}
} ;

class BMRGarbler : public Garbler {
public :
  std::vector<std::uint64_t> maxvals ;    // uint64_t : 2^width, thus full unsigned integer --> plays a role similar to max_width in ArithGarbler 
  std::vector<Label> deltas ;             // List of global correlations for each modulus

  BMRGarbler() : Garbler () {}
} ;


/************************* Evaluator class *************************/

class Evaluator {
public :
  Circuit circ ;                      // Circuit to be evaluated
  std::vector<Wire> input_wires ;     // Input wires to start evaluation

  Evaluator() {}

  void evaluate() ;
} ;


#endif