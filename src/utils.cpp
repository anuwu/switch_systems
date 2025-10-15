#include <iostream>
#include "utils.h"

/************************* Definitions *************************/

// ostream for smalluint
std::ostream& operator<< (std::ostream& os, smalluint su) {
  return os << static_cast<unsigned short>(su) ;
}

// ostream for smallint
std::ostream& operator<< (std::ostream& os, smallint su) {
  return os << static_cast<short>(su) ;
}

// ostream for block
std::ostream& operator<< (std::ostream& os, const emp::block& blk) {
  return emp::operator << (os, blk) ;
}

/************************* Color enum *************************/

std::ostream& color::operator<< (std::ostream& os, Code code) {
  return os << "\033[" << static_cast<uint>(code) << "m" ;
}