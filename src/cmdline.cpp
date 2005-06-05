 // ----------------------------------------------------------------------------
//  Description      : Command line handling.
// ----------------------------------------------------------------------------
//  (c) Copyright 1997 by iXiONmedia, all rights reserved.
// ----------------------------------------------------------------------------




#include <fstream>
#include <ixlib_textfile.hpp>
#include <ixlib_numeric.hpp>
#include <ixlib_cmdline.hpp>




using namespace std;
using namespace ixion;




// Macros ---------------------------------------------------------------------
#define COMMENTSTART1            ';'
#define COMMENTSTART2            '#'




// command_line ---------------------------------------------------------------
command_line::command_line(int argc,char *argv[])
: Command(argv[0]) {
  for (int i = 1;i < argc;i ++) extend(argv[i]);
  }




void command_line::extend(string const &par) {
  if (isHook(par)) {
    string filename = par.substr(1);

    ifstream stream(filename.c_str());
    text_file file;
    stream >> file;

    string line;
    text_file::iterator first = file.begin(),last = file.end();
    while (first != last) {
      line = removeLeadingTrailing(*first);
      if (line.size() && line[0] != COMMENTSTART1 && line[0] != COMMENTSTART2) 
        extend(line);
      first++;
      }
    }
  else 
    Parameters.push_back(par);
  }




TSize command_line::count(string const &mask) {
  vector<string>::iterator first = Parameters.begin(),last = Parameters.end();

  TSize count = 0;
  while (first != last)
    if (matchMask(mask,*first++)) count++;

  return count;
  }




string command_line::get(string const &mask,TIndex matchno) {
  vector<string>::iterator first = Parameters.begin(),last = Parameters.end();

  while (first != last) {
    if (matchMask(mask,*first)) {
      if (matchno == 0) return first->substr(mask.length());
      matchno--;
      }
    first++;
    }
  EXGEN_THROW(EC_ITEMNOTFOUND)
  }




bool command_line::matchMask(string const &mask,string const &par) {
  TSize minlength = NUM_MIN(mask.size(),par.size());
  return mask.substr(0,minlength) == par.substr(0,minlength);
  }

