// ----------------------------------------------------------------------------
//  Description      : Reading and writing text files
// ----------------------------------------------------------------------------
//  (c) Copyright 1999 by iXiONmedia, all rights reserved.
// ----------------------------------------------------------------------------




#include <ixlib_textfile.hpp>




using namespace std;
using namespace ixion;




void text_file::read(istream &stream)
{
  char buf[1024];
  string result;
  
  while (!stream.eof()) {
    result.resize(0);
    do {
      stream.clear(stream.rdstate() & ~ios::failbit);
      stream.getline(buf,1024);
      result += buf;
      } while (stream.gcount() && stream.fail() && !stream.eof());
    push_back(result);
    }
}




void text_file::write(ostream &stream) const
{
  const_iterator first = begin(),last = end();
  while (first != last) {
    stream << *first++ << endl;
    }
}
