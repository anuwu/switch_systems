#include <iostream>
#include "utils.h"
#include "label.h"

// Test label class
void test1(int argc, char **argv) {
  // Abort message
  const auto abort = [&] {
    std::cerr << "Usage : " << argv[0] << " 1 <lambda> <maxval>\n" ;
    exit(EXIT_FAILURE) ;
  } ;
  if (argc != 4)
    abort() ;

  // Read arguments
  meduint lambda = atoi(argv[2]) ; // meduint : from attribute
  std::uint64_t maxval = atoi(argv[3]) ; // unint64_t : from attribute

  // Print stuff
  Label lab = Label(lambda, maxval) ;
  std::cout << "For maxval " << maxval << ", the bitlength = " << lab.bitlength << "\n" ;
}

// Test ArithLabel class
void test2(int argc, char **argv) {
  // Abort message
  const auto abort = [&] {
    std::cerr << "Usage : " << argv[0] << " 2 <lambda> <width>\n" ;
    exit(EXIT_FAILURE) ;
  } ;
  if (argc != 4)
    abort() ;

  // Read arguments
  meduint lambda = atoi(argv[2]) ; // meduint : from attribute
  smalluint width = atoi(argv[3]) ; // unint64_t : from attribute

  // Print stuff
  ArithLabel lab = ArithLabel(lambda, width) ;
  std::cout << "For width = " << width << ", the bitlength = " << lab.bitlength << ", and maxval = " << lab.max_value <<  "\n" ;
}

// Test BMRLabel class
void test3(int argc, char **argv) {
  // Abort message
  const auto abort = [&] {
    std::cerr << "Usage : " << argv[0] << " 3 <lambda> <prime>\n" ;
    exit(EXIT_FAILURE) ;
  } ;
  if (argc != 4)
    abort() ;

  // Read arguments
  meduint lambda = atoi(argv[2]) ; // meduint : from attribute
  smalluint pr = atoi(argv[3]) ; // smalluint : from attribute

  // Print stuff
  BMRLabel lab = BMRLabel(lambda, pr) ;
  std::cout << "For prime " << pr << ", the bitlength = " << lab.bitlength << ", maxval = " << lab.max_value << ", number of slots = " << lab.entropy_slots << ", and loss = " << lab.loss << "\n" ;
}

// Checking copy constructors
void test4(int argc, char **argv) {
  // Abort message
  const auto abort = [&] {
    std::cerr << "Usage : " << argv[0] << " 4 <lambda> <maxval>\n" ;
    exit(EXIT_FAILURE) ;
  } ;
  if (argc != 4)
    abort() ;

  /**** Checking ArithLabel ****/

  // Print stuff
  std::cout << "Copy constructor of ArithLabel --- \n" ;

  // Read arguments
  meduint lambda = atoi(argv[2]) ; // meduint : from attribute
  std::uint64_t maxval = atoi(argv[3]) ; // unint64_t : from attribute

  // Initialize constant label
  ArithLabel arith_lab1(lambda, maxval) ;
  arith_lab1 = const_label<ArithLabel>(arith_lab1, 1ULL) ;

  // Use copy constructor
  ArithLabel arith_lab2 = arith_lab1 ;
  std::cout << "slot[0] of arith_lab1 = " << arith_lab1.slots[0] << ", slot[0] of arith_lab2 = " << arith_lab2.slots[0] << "\n" ;

  /**** Checking BMRLabel ****/

  // Print stuff
  std::cout << "\nCopy constructor of BMRLabel --- \n\n" ;

  // Initialize constant label
  BMRLabel bmr_lab1(lambda, maxval) ;
  bmr_lab1 = const_label<BMRLabel>(bmr_lab1, 1ULL) ;

  // Use copy constructor
  BMRLabel bmr_lab2 = bmr_lab1 ;
  std::cout << "slot[0] of bmr_lab1 = " << bmr_lab1.slots[0] << ", slot[0] of bmr_lab2 = " << bmr_lab2.slots[0] << "\n" ;
}

// Checking operators
void test5(int argc, char **argv) {
  // Abort message
  const auto abort = [&] {
    std::cerr << "Usage : " << argv[0] << " 5 <lambda> <maxval> <op1> <op2>\n" ;
    exit(EXIT_FAILURE) ;
  } ;
  if (argc != 6)
    abort() ;

  // Read arguments
  meduint lambda = atoi(argv[2]) ; // meduint : from attribute
  std::uint64_t maxval = atoi(argv[3]) ; // unint64_t : from attribute
  std::uint64_t op1 = atoi(argv[4]) ; // unint64_t : from attribute
  std::uint64_t op2 = atoi(argv[5]) ; // unint64_t : from attribute

  /**** Operating on ArithLabel ****/

  // Print stuff
  std::cout << "Operations on ArithLabel --- \n\n" ;

  // Initialize constant labels
  ArithLabel arith_lab1(lambda, maxval) ;
  arith_lab1 = const_label<ArithLabel>(arith_lab1, op1) ;
  ArithLabel arith_lab2 = const_label<ArithLabel>(arith_lab1, op2) ;

  // Define labels for each operation
  ArithLabel arith_lab_sum, arith_lab_diff1, arith_lab_diff2, arith_lab_prod, arith_lab_quo ;

  // Addition operator
  arith_lab_sum = arith_lab1 + arith_lab2 ;
  arith_lab_diff1 = arith_lab1 - arith_lab2 ;
  arith_lab_diff2 = arith_lab2 - arith_lab1 ;
  arith_lab_prod = arith_lab1 * arith_lab2 ;
  arith_lab_quo = arith_lab2 / arith_lab1 ;

  // Print stuff
  std::cout << "slot[0] of arith_lab1 = " << arith_lab1.slots[0] << ", slot[0] of arith_lab2 = " << arith_lab2.slots[0] << ", slots[0] of arith_lab_sum = " << arith_lab_sum.slots[0] << "\n" ;
  std::cout << "slot[0] of arith_lab1 = " << arith_lab1.slots[0] << ", slot[0] of arith_lab2 = " << arith_lab2.slots[0] << ", slots[0] of arith_lab_diff1 = " << arith_lab_diff1.slots[0] << "\n" ;
  std::cout << "slot[0] of arith_lab1 = " << arith_lab1.slots[0] << ", slot[0] of arith_lab2 = " << arith_lab2.slots[0] << ", slots[0] of arith_lab_diff2 = " << arith_lab_diff2.slots[0] << "\n" ;
  std::cout << "slot[0] of arith_lab1 = " << arith_lab1.slots[0] << ", slot[0] of arith_lab2 = " << arith_lab2.slots[0] << ", slots[0] of arith_lab_prod = " << arith_lab_prod.slots[0] << "\n" ;
  std::cout << "slot[0] of arith_lab1 = " << arith_lab1.slots[0] << ", slot[0] of arith_lab2 = " << arith_lab2.slots[0] << ", slots[0] of arith_lab_quo = " << arith_lab_quo.slots[0] << "\n" ;

  /**** Operating on BMRLabel ****/

  // Print stuff
  std::cout << "\nOperations on BMRLabel --- \n\n" ;

  // Initialize constant labels
  BMRLabel bmr_lab1(lambda, maxval) ;
  bmr_lab1 = const_label<BMRLabel>(bmr_lab1, op1) ;
  BMRLabel bmr_lab2 = const_label<BMRLabel>(bmr_lab1, op2) ;

  // Define labels for each operation
  BMRLabel bmr_lab_sum, bmr_lab_diff1, bmr_lab_diff2, bmr_lab_prod, bmr_lab_quo ;

  // Addition operator
  bmr_lab_sum = bmr_lab1 + bmr_lab2 ;
  bmr_lab_diff1 = bmr_lab1 - bmr_lab2 ;
  bmr_lab_diff2 = bmr_lab2 - bmr_lab1 ;
  bmr_lab_prod = bmr_lab1 * bmr_lab2 ;
  bmr_lab_quo = bmr_lab2 / bmr_lab1 ;
  
  // Print stuff
  std::cout << "slot[0] of bmr_lab1 = " << bmr_lab1.slots[0] << ", slot[0] of bmr_lab2 = " << bmr_lab2.slots[0] << ", slots[0] of bmr_lab_sum = " << bmr_lab_sum.slots[0] << "\n" ;
  std::cout << "slot[0] of bmr_lab1 = " << bmr_lab1.slots[0] << ", slot[0] of bmr_lab2 = " << bmr_lab2.slots[0] << ", slots[0] of bmr_lab_diff1 = " << bmr_lab_diff1.slots[0] << "\n" ;
  std::cout << "slot[0] of bmr_lab1 = " << bmr_lab1.slots[0] << ", slot[0] of bmr_lab2 = " << bmr_lab2.slots[0] << ", slots[0] of bmr_lab_diff2 = " << bmr_lab_diff2.slots[0] << "\n" ;
  std::cout << "slot[0] of bmr_lab1 = " << bmr_lab1.slots[0] << ", slot[0] of bmr_lab2 = " << bmr_lab2.slots[0] << ", slots[0] of bmr_lab_prod = " << bmr_lab_prod.slots[0] << "\n" ;
  std::cout << "slot[0] of bmr_lab1 = " << bmr_lab1.slots[0] << ", slot[0] of bmr_lab2 = " << bmr_lab2.slots[0] << ", slots[0] of bmr_lab_quo = " << bmr_lab_quo.slots[0] << "\n" ;
}

int main (int argc, char** argv) {
  if (argc < 2) {
    std::cerr << "To view help : " << argv[0] << " <test_no> \n" ;
    exit(EXIT_FAILURE) ;
  }

  // Extract test number
  smalluint test_no = atoi(argv[1]) ;   // smalluint : test cases < 256

  // Enumerate test cases
  switch (test_no) {

  // Label constructor
  case 1 :
    test1(argc, argv) ;
    break ;

  // ArithLabel constructor
  case 2 :
    test2(argc, argv) ;
    break ;

  // BMRLabel constructor
  case 3 :
    test3(argc, argv) ;
    break ;

  // Checking copy constructors
  case 4 :
    test4(argc, argv) ;
    break ;

  // Checking operators
  case 5 :
    test5(argc, argv) ;
    break ;

  // Default case
  default :
    std::cerr << "Invalid test case\n" ;
    exit(EXIT_FAILURE) ;
  }

  return 0 ;
}