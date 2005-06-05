// ----------------------------------------------------------------------------
//  Description      : javascript tests
// ----------------------------------------------------------------------------
//  (c) Copyright 2000 by iXiONmedia, all rights reserved.
// ----------------------------------------------------------------------------




#include <iostream>
#include <fstream>
#include <iomanip>
#include <ixlib_javascript.hpp>
#include "test.hpp"




using namespace ixion;
using namespace javascript;




BEGIN_TEST
  interpreter ip;
  addStandardLibrary(ip);
  
  ifstream infile("test.js");
  ref<javascript::value> value = ip.execute(infile);
  TEST(value.get())
  if (value.get()) {
    bool success = value->toString().substr(0,2) == "OK";
    TEST(success)
    if (!success) cout << value->toString() << endl;
    }
END_TEST
