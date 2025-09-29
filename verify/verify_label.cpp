#include <iostream>
#include "utils.h"
#include "label.h"

#define LAMBDA 128

// Label constructor
void verify1(bool verbose = false) {
  // Setup verification subcases
  smalluint failed = 0 ;
  std::vector<smalluint> failed_checks ;
  std::string failed_msg = "" ;

  // Print verification message
  print_verification(1) ;

  // Holding subcase data
  std::vector<uint64_t> max_vals = {
    0,                        // 1.1
    1,                        // 1.2
    2,                        // 1.3
    3,                        // 1.4
    4,                        // 1.5
    7,                        // 1.6
    8,                        // 1.7
    13,                       // 1.8
    16,                       // 1.9
    32,                       // 1.10
    64,                       // 1.11
    127,                      // 1.12 
    128,                      // 1.13
    1024,                     // 1.14
    (1ULL<<32) - 1,           // 1.15
    0xffffffff,               // 1.16
    (1ULL<<63) - 1,           // 1.17
    1ULL<<63,                 // 1.18
    (1ULL<<63) + 1,           // 1.19
    0xffffffffffffffff        // 1.20
  } ;

  std::vector<Label> labs ;
  for (auto mv : max_vals) {
    labs.push_back(Label(LAMBDA, mv)) ;
  }
  std::vector<std::size_t> expected_bitlengths = {
    1,        // 1.1
    1,        // 1.2
    2,        // 1.3
    2,        // 1.4
    3,        // 1.5
    3,        // 1.6
    4,        // 1.7
    4,        // 1.8
    5,        // 1.9
    6,        // 1.10
    7,        // 1.11
    7,        // 1.12
    8,        // 1.13
    11,       // 1.14
    32,       // 1.15
    32,       // 1.16
    63,       // 1.17
    64,       // 1.18
    64,       // 1.19
    64,       // 1.20
  } ;

  for (smalluint vc = 0 ; vc < (smalluint)labs.size() ; vc++) {
    if (verbose) print_check(vc+1) ;
    if (expected_bitlengths[vc] == labs[vc].bitlength) {
      if (verbose) pass_check() ;
    }
    else {
      if (verbose) fail_check() ;
      if (verbose) print_tabs(3) ;
      if (verbose)
        std::cout << "- Expected bitlength " << color::FG_BLUE << expected_bitlengths[vc] << color::FG_DEFAULT << ", got " << color::FG_BLUE << labs[vc].bitlength << color::FG_DEFAULT << "\n" ;
      failed++ ;
      failed_checks.push_back(vc+1) ;
    }
  }

  if (failed == 0)
    pass_verify(labs.size()) ;
  else
    fail_verify(labs.size(), failed_checks) ;
}


// ArithLabel constructor
void verify2(bool verbose = false) {
  ;
}

// BMRLabel constructor
void verify3(bool verbose = false) {
  ;
}

int main (int argc, char** argv) {
  // Help message
  if (argc < 3) {
    std::cerr << "Usage : " << argv[0] << " <verification_no> <verbose> \n" ;
    exit(EXIT_FAILURE) ;
  }

  // Extract verification number
  smalluint ver_no = atoi(argv[1]) ;
  bool verbose = atoi(argv[2]) == 1 ;

  // Enumerate verification cases
  switch (ver_no) {

  // All verification cases
  case 0 : ;

  // Verify bitlength
  case 1 :
    verify1(verbose) ;
    if (ver_no > 0) break ;

  // ArithLabel constructor
  default :
    std::cerr << "Invalid verification case\n" ;
    exit(EXIT_FAILURE) ;
  }

  return 0 ;
}