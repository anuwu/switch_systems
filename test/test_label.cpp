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
  std::size_t lambda = atoi(argv[2]) ;
  std::uint64_t maxval = atoi(argv[3]) ;

  Label lab = Label(lambda, maxval) ;
  std::cout << "For maxval " << maxval << ", the bitlength = " << lab.bitlength << "\n" ;
}

// Test ArithLabel class
void test2(int argc, char **argv) {
  // Abort message
  const auto abort = [&] {
    std::cerr << "Usage : " << argv[0] << " 2 <lambda> <maxval>\n" ;
    exit(EXIT_FAILURE) ;
  } ;
  if (argc != 4)
    abort() ;

  // Read arguments
  std::size_t lambda = atoi(argv[2]) ;
  std::uint64_t maxval = atoi(argv[3]) ;

  // Print stuff
  ArithLabel lab = ArithLabel(lambda, maxval) ;
  std::cout << "For maxval " << maxval << ", the bitlength = " << lab.bitlength << "\n" ;
}

// Test BMRLabel class
void test3(int argc, char **argv) {
  // Abort message
  const auto abort = [&] {
    std::cerr << "Usage : " << argv[0] << " 3 <lambda> <maxval>\n" ;
    exit(EXIT_FAILURE) ;
  } ;
  if (argc != 4)
    abort() ;

  // Read arguments
  std::size_t lambda = atoi(argv[2]) ;
  std::uint64_t maxval = atoi(argv[3]) ;

  // Print stuff
  BMRLabel lab = BMRLabel(lambda, maxval) ;
  std::cout << "For maxval " << maxval << ", the bitlength = " << lab.bitlength << ", number of slots = " << lab.num_slots << "\n" ;
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
  std::size_t lambda = atoi(argv[2]) ;
  std::uint64_t maxval = atoi(argv[3]) ;

  // Initialize constant label
  ArithLabel arith_lab1(lambda, maxval) ;
  arith_lab1 = const_label<ArithLabel>(arith_lab1, 1ULL) ;

  // Use copy constructor
  ArithLabel arith_lab2 = arith_lab1 ;
  std::cout << "slot[0] of arith_lab1 = " << arith_lab1.slots[0] << ", slot[0] of arith_lab2 = " << arith_lab2.slots[0] << "\n" ;

  /**** Checking BMRLabel ****/

  // Print stuff
  std::cout << "\nCopy constructor of BMRLabel --- \n" ;

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
  std::size_t lambda = atoi(argv[2]) ;
  std::uint64_t maxval = atoi(argv[3]) ;
  std::uint64_t op1 = atoi(argv[4]) ;
  std::uint64_t op2 = atoi(argv[5]) ;

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
  int test_no = atoi(argv[1]) ;

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

  case 4 :
    test4(argc, argv) ;
    break ;

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