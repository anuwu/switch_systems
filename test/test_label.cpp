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

  ArithLabel lab = ArithLabel(lambda, maxval) ;
  std::cout << "For maxval " << maxval << ", the bitlength = " << lab.bitlength << "\n" ;
}

// Test BMRLabel class
void test3(int argc, char **argv) {
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

  BMRLabel lab = BMRLabel(lambda, maxval) ;
  std::cout << "For maxval " << maxval << ", the bitlength = " << lab.bitlength << ", number of slots = " << lab.num_slots << "\n" ;
}

// // Checking copy constructors
// void test4(int argc, char **argv) {
//   // Testing arithmetic label
//   ArithLabel lab1(LAMBDA, 65535) ;
//   lab1.slots[0] = 1 ;
//   ArithLabel lab2 = lab1 ;
//   std::cout << "slot[0] of lab1 = " << lab1.slot[0] << ", slot[0] of lab1 = " << lab2.slots[0] << "\n" ;

// }

// Checking operators
void test5(int argc, char **argv) {

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

  // Default case
  default :
    std::cerr << "Invalid test case\n" ;
    exit(EXIT_FAILURE) ;
  }

  return 0 ;
}