#include <iostream>
#include "utils.h"

/************************* Definitions *************************/

std::ostream& operator<< (std::ostream& os, const emp::block& blk) {
  return emp::operator << (os, blk) ;
}

std::ostream& operator<< (std::ostream& os, smalluint su) {
  return os << static_cast<unsigned short>(su) ;
}

std::ostream& operator<< (std::ostream& os, smallint su) {
  return os << static_cast<short>(su) ;
}

/************************* Color enum *************************/

std::ostream& color::operator<< (std::ostream& os, Code code) {
  return os << "\033[" << static_cast<uint>(code) << "m" ;
}

/************************* Others *************************/

smalluint get_bitlength(std::uint64_t maxval) {
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

std::uint64_t width_to_maxval(smalluint width) {
  assert(width <= 64 && "Width cannot be > 64") ;

  if (width == 64)
    return (0ULL - 1ULL) ;
  else
    return (1ULL << width) - 1ULL ;
}

bool check_prime(smalluint p) {
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

