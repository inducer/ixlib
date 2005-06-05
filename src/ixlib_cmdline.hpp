// ----------------------------------------------------------------------------
//  Description      : Command line handling.
// ----------------------------------------------------------------------------
//  (c) Copyright 1997 by iXiONmedia, all rights reserved.
// ----------------------------------------------------------------------------




#ifndef IXLIB_CMDLINE
#define IXLIB_CMDLINE




#include <vector>
#include <ixlib_string.hpp>




namespace ixion {
  class command_line {
    std::vector<std::string>	Parameters;
    std::string			Command;
  
    public:
    command_line(int argc = 0,char *argv[] = NULL);
  
    void extend(std::string const &par);
  
    TSize operator~() const
      { return Parameters.size(); }
    std::string operator[](TIndex no) const
      { return Parameters[no]; }
  
    std::string getCommand() const
      { return Command; }
  
    TSize count(std::string const &mask);
    std::string get(std::string const &mask,TIndex matchno = 0);
  
    private:
    static bool isHook(std::string const &text)
      { return text[0] == '@'; }
    static bool matchMask(std::string const &mask,std::string const &par);
    };
  }



#endif
