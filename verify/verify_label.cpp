#include <iostream>
#include "utils.h"
#include "label.h"

// Verify Label
void verify_label(bool verbose = false) {
  // Setup verification subcases
  smalluint failed = 0 ;  // smalluint : number of cases less than 256 --> number of test subcases that failed
  std::vector<smalluint> failed_checks ; // list of subcase numbers that failed
  std::string failed_msg = "" ; // failure message

  // Print verification message
  print_verification(1) ;

  // List of maximum values in the ring i.e., order - 1
  std::vector<uint64_t> max_vals = {
    1,                        // 1.1
    2,                        // 1.2
    3,                        // 1.3
    4,                        // 1.4
    7,                        // 1.5
    8,                        // 1.6
    13,                       // 1.7
    16,                       // 1.8
    32,                       // 1.9
    64,                       // 1.10
    127,                      // 1.11 
    128,                      // 1.12
    1024,                     // 1.13
    (1ULL<<32) - 1,           // 1.14
    0xffffffff,               // 1.15
    (1ULL<<63) - 1,           // 1.16
    1ULL<<63,                 // 1.17
    (1ULL<<63) + 1,           // 1.18
    0xffffffffffffffff        // 1.19
  } ;

  // Creating ArithLabel objects. Using polymorphism. 
  std::vector<Label> labs ;
  for (auto mv : max_vals)
    labs.push_back(Label(LAMBDA, mv)) ;

  // Expected bitlengths
  std::vector<smalluint> expected_bitlengths = {
    1,        // 1.1
    2,        // 1.2
    2,        // 1.3
    3,        // 1.4
    3,        // 1.5
    4,        // 1.6
    4,        // 1.7
    5,        // 1.8
    6,        // 1.9
    7,        // 1.10
    7,        // 1.11
    8,        // 1.12
    11,       // 1.13
    32,       // 1.14
    32,       // 1.15
    63,       // 1.16
    64,       // 1.17
    64,       // 1.18
    64,       // 1.19
  } ;

  // Checking ArithLabel objects. smalluint : verification cases less than 256.
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

// Verify ArithLabel
void verify_arithlabel(bool verbose = false) {
  // Setup verification subcases
  smalluint failed = 0 ; // smalluint : number of cases less than 256 --> number of test subcases that failed
  std::vector<smalluint> failed_checks ; // list of subcase numbers that failed
  std::string failed_msg = "" ; // failure message

  // Print verification message
  print_verification(2) ;

  // List of maximum values in the ring i.e., order - 1
  std::vector<smalluint> widths = {
    1,                        // 1.1
    8,                        // 1.2
    16,                       // 1.3
    32,                       // 1.4
    64                        // 1.5
  } ;

  // BMRLabel objects
  std::vector<ArithLabel> labs ;
  for (auto w : widths)
    labs.push_back(ArithLabel(LAMBDA, w)) ;

  // Expected number of slots
  std::vector<smalluint> expected_bl = {
    1,          // 1.1
    8,          // 1.2
    16,         // 1.3
    32,         // 1.4
    64          // 1.5
  } ;

  // Checking BMRLabel objects. smalluint : verification cases less than 256.
  for (smalluint vc = 0 ; vc < (smalluint)labs.size() ; vc++) {
    if (verbose) print_check(vc+1) ;
    if (expected_bl[vc] == labs[vc].bitlength) {
      if (verbose) pass_check() ;
    }
    else {
      if (verbose) fail_check() ;
      if (verbose) print_tabs(3) ;
      if (verbose)
        std::cout << "- Bitlength " << color::FG_BLUE << expected_bl[vc] << color::FG_DEFAULT << ", got " << color::FG_BLUE << labs[vc].bitlength << color::FG_DEFAULT << "\n" ;
      failed++ ;
      failed_checks.push_back(vc+1) ;
    }
  }

  if (failed == 0)
    pass_verify(labs.size()) ;
  else
    fail_verify(labs.size(), failed_checks) ;
}

// Verify BMRlabel
void verify_bmrlabel(bool verbose = false) {
  // Setup verification subcases
  smalluint failed = 0 ; // smalluint : number of cases less than 256 --> number of test subcases that failed
  std::vector<smalluint> failed_checks ; // list of subcase numbers that failed
  std::string failed_msg = "" ; // failure message

  // Print verification message
  print_verification(3) ;

  // List of primes
  std::vector<uint64_t> primes = {
    2,                      // 1.1
    3,                      // 1.2
    5,                      // 1.3 
    11,                     // 1.4
    17,                     // 1.5
    53,                     // 1.6
    71,                     // 1.7
    173                     // 1.8
  } ;

  // BMRLabel objects
  std::vector<BMRLabel> labs ;
  for (auto p : primes)
    labs.push_back(BMRLabel(LAMBDA, p)) ;

  // Expected bitlengths
  std::vector<smalluint> expected_bl = {
    1,                      // 1.1 -> bitlength = 1
    2,                      // 1.2 -> bitlength = 2
    3,                      // 1.3 -> bitlength = 3
    4,                      // 1.4 -> bitlength = 4
    5,                      // 1.5 -> bitlength = 5
    6,                      // 1.6 -> bitlength = 6
    7,                      // 1.7 -> bitlength = 7
    8                       // 1.8 -> bitlength = 8
  } ;

  // Expected useless bits. e = h - bitlength
  std::vector<meduint> expected_loss = {
    0,                      // 1.1 -> h = 1, bl = 1, e = 0
    0,                      // 1.2 -> h = 2, bl = 2, e = 0
    2,                      // 1.3 -> h = 5, bl = 3, e = 2
    0,                      // 1.4 -> h = 4, bl = 4, e = 0
    3,                      // 1.5 -> h = 8, bl = 5, e = 3
    2,                      // 1.6 -> h = 8, bl = 6, e = 2
    2,                      // 1.7 -> h = 9, bl = 7, e = 2
    0                       // 1.8 -> h = 8, bl = 8, e = 0
  } ;

  // Checking BMRLabel objects. smalluint : verification cases less than 256.
  for (smalluint vc = 0 ; vc < (smalluint)labs.size() ; vc++) {
    if (verbose) print_check(vc+1) ;
    if (expected_bl[vc] == labs[vc].bitlength && expected_loss[vc] == labs[vc].loss) {
      if (verbose) pass_check() ;
    }
    else {
      if (verbose) fail_check() ;
      if (verbose) print_tabs(3) ;
      if (verbose) {
        if (expected_bl[vc] != labs[vc].bitlength)
          std::cout << "- Expected bitlength " << color::FG_BLUE << expected_bl[vc] << color::FG_DEFAULT << ", got " << color::FG_BLUE << labs[vc].bitlength << color::FG_DEFAULT << "\n" ;
        if (expected_loss[vc] != labs[vc].loss)
          std::cout << "- Expected loss " << color::FG_BLUE << expected_loss[vc] << color::FG_DEFAULT << ", got " << color::FG_BLUE << labs[vc].loss << color::FG_DEFAULT << "\n" ;
      }
        
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
  smalluint ver_no = atoi(argv[1]) ;  // smalluint : test cases less than 10 --> switch value to call verification function
  bool verbose = false ;  // if verbose, detailed messages, else short messages
  if (argc == 3)
      verbose = atoi(argv[2]) == 1 ;

  // Enumerate verification cases
  switch (ver_no) {

  // All verification cases
  case 0 : ;

  // Verify bitlength computation from max_value
  case 1 :
    verify_label(verbose) ;
    if (ver_no > 0) break ;

  // Verify slot numbers
  case 2 :
    verify_arithlabel(verbose) ;
    if (ver_no > 0) break ;   
  
  // Verify loss number in BMR label
  case 3 :
    verify_bmrlabel(verbose) ;
    break ; // Compulsory break in the last case

  // Default case
  default :
    std::cerr << "Invalid verification case\n" ;
    exit(EXIT_FAILURE) ;
  }

  return 0 ;
}