// ----------------------------------------------------------------------------
//  Description      : geometry tests
// ----------------------------------------------------------------------------
//  (c) Copyright 1998 by iXiONmedia, all rights reserved.
// ----------------------------------------------------------------------------




#include <iostream>
#include <ixlib_geometry.hpp>
#include <ixlib_geometry_impl.hpp>
#include <ixlib_exbase.hpp>
#include "test.hpp"




using namespace ixion;




template rectangle<float>;
template region<float>;




BEGIN_TEST
  coord_vector<int> vec1(1,2,3);
  coord_vector<double,2> vec2;
  coord_vector<int,3> vec3(1,2,3);
  
  vec2 = vec1;
  vec2[0] = 3;
  vec1[0] = vec3[2];
  TEST(vec1==vec2)
  
  vec1 = vec1+vec1;
  
  rectangle<float> rect(3,4,5,6);
  rectangle<int> rect2(rect);
  rect = rect2;
  
  rect += vec2;
  
  region<float> reg;
  reg.add(rect);
  reg.subtract(rect2);
END_TEST
