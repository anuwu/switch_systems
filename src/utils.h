#ifndef SWITCH_SYSTEMS_UTILS_H
#define SWITCH_SYSTEMS_UTILS_H

#include <ostream>
#include <vector>
#include <unordered_set>
#include "emp-tool/emp-tool.h"

/************************* Definitions *************************/

// Constants
#define LAMBDA 128
#define TABVAL 2
#define all_ones_64t 0xffffffffffffffff

// Macros
#define CEIL_DIV(X, Y) (1 + (((X) - 1)/(Y)))
#define FLOOR_DIV(X, Y) ((X)/(Y))

// Custom type names
typedef unsigned char smalluint ;
typedef char smallint ;
typedef unsigned short meduint ;
typedef short medint ;

// ostream operator for custom type names
std::ostream& operator<< (std::ostream& os, smalluint su) ;
std::ostream& operator<< (std::ostream& os, smallint su) ;

// ostream operator for emp::block
std::ostream& operator<< (std::ostream& os, const emp::block& blk) ;  // Weird, but doesn't work any other way.

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

// Left shift block
inline emp::block left_shift(const emp::block &blk, int shift) {
  uint64_t* data = (uint64_t*)&blk ;

  if (shift > 127)
    return emp::zero_block ;
  else if (shift > 63) {
    uint64_t dat1, dat0 ;
    dat0 = 0ULL ;
    dat1 = data[0] << (shift - 64) ;
    return emp::makeBlock(dat1, dat0) ;
  } else {
    uint64_t dat1, dat0 ;
    uint64_t mask = (1ULL << shift) - 1 ;

    // Copying most significant bits of data[0] that will get erased
    mask = mask << (64 - shift) ;
    mask = mask & data[0] ;
    mask = mask >> (64 - shift) ;

    // Shifting data[1] and pasting from data[0]
    dat1 = data[1] << shift ;
    dat1 = dat1 ^ mask ;

    // Shifting data[0] and return
    dat0 = data[0] << shift ;
    return emp::makeBlock(dat1, dat0) ;
  }
}

// Right shift block
inline emp::block right_shift(const emp::block &blk, int shift) {
  uint64_t* data = (uint64_t*)&blk ;

  if (shift > 127)
    return emp::zero_block ;
  else if (shift > 63) {
    uint64_t dat1, dat0 ;
    dat1 = 0ULL ;
    dat0 = data[1] >> (shift - 64) ;
    return emp::makeBlock(dat1, dat0) ;
  } else {
    uint64_t dat1, dat0 ;
    uint64_t mask = (1ULL << shift) - 1 ;

    // Copying least significant bits of data[1] that will get erased
    mask = mask & data[1] ;

    // Shifting data[0] and pasting from data[1]
    // cout << "This is data[0] = " << hex << setw(16) << setfill('0') << data[0] << "\n" ;
    dat0 = data[0] >> shift ;
    mask = mask << (64 - shift) ;
    dat0 = dat0 ^ mask ;

    // Shifting data[1] and return
    dat1 = data[1] >> shift ;
    return emp::makeBlock(dat1, dat0) ;
  }
}

// XOR array of blocks
inline void xorBlocks_arr(emp::block* res, emp::block* y, int nblocks) {
	const emp::block *dest = nblocks + res ;
	for (; res != dest ;) {
    *res = *res ^ *(y++) ;
    res++ ; 
	}
}

// AND array of blocks in-place
inline void andBlocks_arr(emp::block* res, emp::block* y, int nblocks) {
	const emp::block *dest = nblocks + res ;
	for (; res != dest ;) {
    *res = *res & * (y++) ;
    res++ ;
	}
}

// AND array of blocks
inline void andBlocks_arr(emp::block* res, emp::block* x, emp::block* y, int nblocks) {
	const emp::block *dest = nblocks + res ;
	for (; res != dest ;)
    *(res++) = *(x++) & *(y++) ;
}

/************************* Printing stuff *************************/

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
inline smalluint get_bitlength(std::uint64_t maxval) {
  // Initialize bitlength
  smalluint bl = 0 ;

  // Loop until argument is 0
  do {
    bl += 1 ;
    maxval = maxval >> 1 ; 
  } while (maxval != 0ULL) ; // If this is 0ULL, all bits have been exhausted

  // Return
  return bl ;
}

// Convert width to maximum value
inline std::uint64_t width_to_maxval(smalluint width) {
  assert(width <= 64 && "Width cannot be > 64") ;

  if (width == 64)
    return (0ULL - 1ULL) ;
  else
    return (1ULL << width) - 1ULL ;
}

// Check if prime number
inline bool check_prime(smalluint p) {
  // List of primes
  std::unordered_set<smalluint> primes({
    2, // bitlength 1 
    3, // bitlength 2
    5, 7, // bitlength 3
    11, 13, // bitlength 4
    17, 19, 23, 29, 31, // bitlength 5
    37, 41, 43, 47, 53, 59, 61, // bitlength 6
    67, 71, 73, 79, 83, 89, 97, 101, 103, 107, 109, 113, 127, // bitlength 7
    131, 137, 139, 149, 151, 157, 163, 167, 173, 179, 181, 191, 193, 197, 199, 211, 223, 227, 229, 233, 239, 241, 251 //bitlength 8
  }) ;

  return primes.find(p) != primes.end() ;
}

// Correct value to be filled in a slot
inline std::uint64_t fix_fill(std::uint64_t v, std::uint64_t mv) {
  // Assume filled value is equal to v
  std::uint64_t fill = v ;

  // Fill value doesn't need to change if max value is 0xffff or v == 0. Negate this condition and change it.
  if (mv < all_ones_64t && v)
    fill %= mv + 1 ;

  // Return
  return fill ;
}

#endif