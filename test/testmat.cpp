// ----------------------------------------------------------------------------
//  Description      : matrix tests
// ----------------------------------------------------------------------------
//  (c) Copyright 2000 by iXiONmedia, all rights reserved.
// ----------------------------------------------------------------------------




#include <iostream>
#include <iomanip>
#include <ixlib_matrix_impl.hpp>
#include "test.hpp"




using namespace ixion;




typedef matrix<double> mat;
template mat;




void item_formatter(ostream &os,bool first,bool last) {
  os << setw(10) << setprecision(4);
  }





BEGIN_TEST
  double u[] = { 9,-7,2,-7,11,-3,2,-3,4 };

  mat A(3,3,u);
  mat cholesky = A.cholesky();
  mat B = cholesky*cholesky.transposed();
  mat diff = A - B;
  TEST(diff.norm() < 1e-5)
END_TEST
