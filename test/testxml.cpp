// ----------------------------------------------------------------------------
//  Description      : XML parsing tests.
// ----------------------------------------------------------------------------
//  (c) Copyright 1999 by iXiONmedia, all rights reserved.
// ----------------------------------------------------------------------------




#include <fstream>
#include <iostream>
#include <vector>
#include <ixlib_xml.hpp>
#include <ixlib_string.hpp>
#include "test.hpp"




using namespace ixion;




BEGIN_TEST
  { ifstream istr("test-big.xml");
  
    xml_file xml;
    xml.read(istr);
  
    ofstream ostr("test.xml.new");
    xml.write(ostr);
    }

  { ifstream istr("test-structure.xml");
  
    xml_file xml;
    xml.read(istr);
  
    ofstream ostr("test.xml.out");
    xml.write(ostr);
    }
END_TEST
