#include <iostream>
#include "utils.h"

/************************* Definitions *************************/

std::ostream& color::operator<< (std::ostream& os, Code code) {
  return os << "\033[" << static_cast<int>(code) << "m" ;
}

std::ostream& operator<<(std::ostream& out, const emp::block& blk) {
  emp::operator << (out, blk) ;
  return out ;
}

/************************* Color enum *************************/

std::ostream& operator<< (std::ostream& os, smalluint su) {
  return os << static_cast<int>(su) ;
}

/************************* Others *************************/

int get_bitlength(std::uint64_t maxval) {
  std::uint64_t ret = 0 ;
  do {
    ret += 1 ;
    maxval = maxval >> 1 ;
  } while (maxval != 0) ;

  return ret ;
}