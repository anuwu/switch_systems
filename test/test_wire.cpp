#include <iostream>
#include "utils.h"
#include "wire.h"
#include "emp-tool/emp-tool.h"

// Test CCRH
void test1(int argc, char **argv) {
  // Abort message
  const auto abort = [&] {
    std::cerr << "Usage : " << argv[0] << " 1\n" ;
    exit(EXIT_FAILURE) ;
  } ;
  if (argc != 2)
    abort() ;

  // Single block CCRH test
  std::cout << "Testing CCRH function for one block\n" ;
  emp::CCRH ccrh = emp::CCRH() ;
  emp::block aob = emp::all_one_block ;
  emp::block out = ccrh.H(aob) ;
  std::cout << "Input block = " << aob << "\n" ;
  std::cout << "Output block 1 = " << out << "\n" ;

  // Zero block
  emp::block zero_block = emp::makeBlock(0ULL, 0ULL) ;
  std::cout << "CCRH on 00 --- \n" ;
  std::cout << "00 block looks like = " << zero_block << "\n" ;
  std::cout << "CCRH on 00 block = " << ccrh.H(zero_block) << "\n" ;

  // One block
  emp::block one_block = emp::makeBlock(0ULL, 1ULL) ;
  std::cout << "CCRH on 01 --- \n" ;
  std::cout << "01 block looks like = " << one_block << "\n" ;
  std::cout << "CCRH on 01 block = " << ccrh.H(one_block) << "\n" ;

  // Multi block CCRH test
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

  // Whatever test
  case 1 :
    test1(argc, argv) ;
    break ;

  // Default case
  default :
    std::cerr << "Invalid test case\n" ;
    exit(EXIT_FAILURE) ;
  }

  return 0 ;
}