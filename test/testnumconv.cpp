// ----------------------------------------------------------------------------
//  Description      : numeric conversion tests.
// ----------------------------------------------------------------------------
//  (c) Copyright 1998 by iXiONmedia, all rights reserved.
// ----------------------------------------------------------------------------




#include <ixlib_numconv.hpp>
#include "test.hpp"




using namespace ixion;




BEGIN_TEST
  TEST(unsigned2dec(239434) == "239434")
  TEST(unsigned2hex(0xAFFE) == "AFFE")
  TEST(signed2bin(-0xAA) == "-10101010")
  TEST(bytes2dec(1024*1024) == "1024 KB")
  TEST(evalUnsigned("0xaffe") == 0xaffe);
  TEST(evalSigned("-1010b") == -0xa);
END_TEST
