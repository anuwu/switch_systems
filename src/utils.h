#ifndef SWITCH_SYSTEMS_UTILS_H
#define SWITCH_SYSTEMS_UTILS_H

#include <ostream>
#include <vector>
#include "emp-tool/emp-tool.h"

/************************* Definitions *************************/

#define LAMBDA 128
#define TABVAL 2
#define CEIL_DIV(X, Y) (1 + (((X) - 1)/(Y)))
typedef unsigned char smalluint ;

std::ostream& operator<< (std::ostream& os, smalluint su) ;
std::ostream& operator<<(std::ostream& out, const emp::block& blk) ;  // Weird, but doesn't work any other way.

/************************* Color enum *************************/

// Color modifiers during verification
namespace color {
  enum Code {
    FG_DEFAULT        = 39, 
    FG_BLACK          = 30, 
    FG_RED            = 31, 
    FG_GREEN          = 32, 
    FG_YELLOW         = 33, 
    FG_BLUE           = 34, 
    FG_MAGENTA        = 35, 
    FG_CYAN           = 36, 
    FG_LIGHT_GRAY     = 37, 
    FG_DARK_GRAY      = 90, 
    FG_LIGHT_RED      = 91, 
    FG_LIGHT_GREEN    = 92, 
    FG_LIGHT_YELLOW   = 93, 
    FG_LIGHT_BLUE     = 94, 
    FG_LIGHT_MAGENTA  = 95, 
    FG_LIGHT_CYAN     = 96, 
    FG_WHITE          = 97, 
    BG_RED            = 41, 
    BG_GREEN          = 42, 
    BG_BLUE           = 44, 
    BG_DEFAULT        = 49
  } ;

  std::ostream& operator<< (std::ostream& os, Code code) ;
}

/************************* Block manipulation *************************/

// Printing tabs
inline void print_tabs(smalluint no_tabs) {
  for (smalluint i = 0 ; i < no_tabs ; i++) {
    for (smalluint j = 0 ; j < TABVAL ; j++)
      std::cout << " " ;
  }
}

// Starting message of a verification function
inline void print_verification(smalluint ver_no, smalluint tabs=0) {
  print_tabs(tabs) ;
  std::cout << "Running verification " << color::FG_BLUE << ver_no << color::FG_DEFAULT << " ---\n" ;
}

// Message for checks in a verification
inline void print_check(smalluint check_no, smalluint tabs=2) {
  print_tabs(tabs) ;
  std::cout << "Check " << color::FG_BLUE <<  "1."  << check_no << color::FG_DEFAULT << " --> " ;
}

// If check passes
inline void pass_check(smalluint tabs=1) {
  std::cout << color::FG_GREEN << "Passed!" << color::FG_DEFAULT << "\n" ;
}

// If check fails
inline void fail_check(smalluint tabs=1) {
  std::cout << color::FG_RED << "Failed!" << color::FG_DEFAULT << "\n" ;
}

// If verification function passes
inline void pass_verify(int no_checks, smalluint tabs=1) {
  print_tabs(tabs) ;
  std::cout << color::FG_GREEN << "Passed all " << color::FG_BLUE << no_checks << color::FG_GREEN << " checks " << color::FG_DEFAULT << "\n" ;
}

// If verification function fails
inline void fail_verify(int no_checks, std::vector<smalluint> failed_checks, smalluint tabs=1) {
  print_tabs(tabs) ;
  std::cout << color::FG_RED << "Failed " << color::FG_BLUE << (failed_checks.size()) << color::FG_RED << " out of " << color::FG_BLUE << no_checks << color::FG_RED << " checks. " << color::FG_DEFAULT << "\n" ;
  print_tabs(tabs) ;
  std::cout << "Failed checks - " << color::FG_BLUE << failed_checks[0] << color::FG_DEFAULT ;
  for (auto it = failed_checks.begin() + 1; it != failed_checks.end() ; it++)
    std::cout << ", " << color::FG_BLUE << (*it) << color::FG_DEFAULT ;
  std::cout << "\n" ;
}

/************************* Others *************************/

// Get bitlength required to hold a maximum value
int get_bitlength(std::uint64_t maxval) ;

#endif