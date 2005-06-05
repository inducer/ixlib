// ----------------------------------------------------------------------------
//  Description      : Regular expressions tests.
// ----------------------------------------------------------------------------
//  (c) Copyright 1998 by iXiONmedia, all rights reserved.
// ----------------------------------------------------------------------------




#include <ixlib_garbage.hpp>
#include "test.hpp"




using namespace ixion;




void f(ref<int> x) {
  *x *= 5;
  }




BEGIN_TEST
  ref<int> x = new int(5);
  *x *= 2;
  ref<int> y = x;
  *y = 7;
  f(x);
  TEST(*x == 35)
END_TEST




IXLIB_GARBAGE_DECLARE_MANAGER(int)