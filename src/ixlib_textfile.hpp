// ----------------------------------------------------------------------------
//  Description      : Reading and writing text files
// ----------------------------------------------------------------------------
//  (c) Copyright 1999 by iXiONmedia, all rights reserved.
// ----------------------------------------------------------------------------




#ifndef IXLIB_TEXTFILE
#define IXLIB_TEXTFILE




#include <vector>
#include <string>
#include <iostream>




namespace ixion {
  class text_file : public std::vector<std::string> {
    public:
    void read(std::istream &stream);
    void write(std::ostream &stream) const;
    };
  
  
  
  
  inline std::istream &operator>>(std::istream &istr,text_file &conf) {
    conf.read(istr);
    return istr;
    }
  
  
  
  
  inline std::ostream &operator<<(std::ostream &ostr,text_file const &conf) {
    conf.write(ostr);
    return ostr;
    }
  }
  
  
  

#endif
