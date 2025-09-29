#include <iostream>
#include "utils.h"
#include "label.h"

// Label constructor
void verify1(bool verbose = false) {
  // Setup verification subcases
  smalluint failed = 0 ;
  std::vector<smalluint> failed_checks ;
  std::string failed_msg = "" ;

  // Print verification message
  print_verification(1) ;

  // List of maximum values in the ring i.e., order - 1
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

  // List of label objects
  std::vector<Label> labs ;
  for (auto mv : max_vals) {
    labs.push_back(Label(LAMBDA, mv)) ;
  }

  // Expected bitlengths
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

  // Checking Label objects
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

  // Final message
  if (failed == 0)
    pass_verify(labs.size()) ;
  else
    fail_verify(labs.size(), failed_checks) ;
}

// ArithLabel constructor
void verify2(bool verbose = false) {
  // Setup verification subcases
  smalluint failed = 0 ;
  std::vector<smalluint> failed_checks ;
  std::string failed_msg = "" ;

  // Print verification message
  print_verification(2) ;

  // List of maximum values in the ring i.e., order - 1
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

  // Creating ArithLabel objects. Using polymorphism. 
  std::vector<Label> labs ;
  for (auto mv : max_vals) {
    labs.push_back(ArithLabel(LAMBDA, mv)) ;
  }

  // Expected bitlengths
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

  // Checking ArithLabel objects
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

  // Final message
  if (failed == 0)
    pass_verify(labs.size()) ;
  else
    fail_verify(labs.size(), failed_checks) ;
}

// BMRLabel constructor
void verify3(bool verbose = false) {
  // Setup verification subcases
  smalluint failed = 0 ;
  std::vector<smalluint> failed_checks ;
  std::string failed_msg = "" ;

  // Print verification message
  print_verification(3) ;

  // List of maximum values in the ring i.e., order - 1
  std::vector<uint64_t> max_vals = {
    31,                        // 1.1
    13,                        // 1.2
    65535,                     // 1.3
    1,                         // 1.4
  } ;

  // List of security parameters
  std::vector<uint> lambdas = {
    128,      // 1.1
    128,      // 1.2
    16,       // 1.3
    16        // 1.4
  } ;

  // BMRLabel objects
  std::vector<Label> labs ;
  for (smalluint i = 0 ; i < (smalluint)max_vals.size() ; i++) {
    labs.push_back(BMRLabel(lambdas[i], max_vals[i])) ;
  }

  // Expected number of slots
  std::vector<std::size_t> expected_slots = {
    26,        // 1.1
    32,        // 1.2
    1,         // 1.3
    16         // 1.4
  } ;

  // Checking BMRLabel objects
  for (smalluint vc = 0 ; vc < (smalluint)labs.size() ; vc++) {
    if (verbose) print_check(vc+1) ;
    if (expected_slots[vc] == labs[vc].num_slots) {
      if (verbose) pass_check() ;
    }
    else {
      if (verbose) fail_check() ;
      if (verbose) print_tabs(3) ;
      if (verbose) {}
        std::cout << "- Number of slots " << color::FG_BLUE << expected_slots[vc] << color::FG_DEFAULT << ", got " << color::FG_BLUE << labs[vc].num_slots << color::FG_DEFAULT << "\n" ;
      failed++ ;
      failed_checks.push_back(vc+1) ;
    }
  }

  if (failed == 0)
    pass_verify(labs.size()) ;
  else
    fail_verify(labs.size(), failed_checks) ;
}

int main (int argc, char** argv) {
  // Help message
  if (argc < 2) {
    std::cerr << "Usage : " << argv[0] << " <verification_no> <opt:verbose> \n" ;
    exit(EXIT_FAILURE) ;
  }

  // Extract verification number
  smalluint ver_no = atoi(argv[1]) ;
  bool verbose = false ;
  if (argc == 3)
      verbose = atoi(argv[2]) == 1 ;

  // Enumerate verification cases
  switch (ver_no) {

  // All verification cases
  case 0 : ;

  // Verify bitlength in Label
  case 1 :
    verify1(verbose) ;
    if (ver_no > 0) break ;

  // Verify bitlength in ArithLabel
  case 2 :
    verify2(verbose) ;
    if (ver_no > 0) break ;

  // Verify bitlength and slots in BMRLabel
  case 3 :
    verify3(verbose) ;
    break ;   // Compulsory break in the last case

  // Default case
  default :
    std::cerr << "Invalid verification case\n" ;
    exit(EXIT_FAILURE) ;
  }

  return 0 ;
}