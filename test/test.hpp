// ----------------------------------------------------------------------------
//  Description      : Cheap testing framework
// ----------------------------------------------------------------------------
//  (c) Copyright 1998 by iXiONmedia, all rights reserved.
// ----------------------------------------------------------------------------




#ifndef IXLIB_TEST
#define IXLIB_TEST




#include <iostream>
#include <ixlib_exbase.hpp>




using namespace std;




#define BEGIN_TEST \
int main() {\
  try { \
    TSize errcount = 0,testcount = 0; 

#define END_TEST \
  if (errcount) \
    cout << errcount << " out of " << testcount \
      << " test(s) failed." << endl; \
  else \
    cout << "all " << testcount << " tests passed." << endl; \
  return errcount; \
  } \
  catch (exception &e) { \
    cerr << "*** exception exit. bad." << endl; \
    cerr << "*** " << e.what() << endl; \
    return 1; \
    } \
  catch (...) { \
    cerr << "*** exception exit. bad." << endl; \
    return 1; \
    } \
}

#define PASSED { testcount++; }

#define FAILED { testcount++; errcount++; \
  cerr << "*** Test " << testcount << " failed." << endl; }

#define FAILEDEX { testcount++; errcount++; \
  cerr << "*** Test " << testcount << " failed due to an exception." << endl; }
  
#define TEST(INVARIANT) \
  try { \
    if (INVARIANT) PASSED else { \
      FAILED \
      cerr << "*** " << #INVARIANT << endl; \
      }\
    } \
  catch (exception &e) { \
    FAILEDEX \
    cerr << "*** " << e.what() << endl; \
    }




#endif
