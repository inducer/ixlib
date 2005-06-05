// ----------------------------------------------------------------------------
//  Description      : Command line parsing tests.
// ----------------------------------------------------------------------------
//  (c) Copyright 1998 by iXiONmedia, all rights reserved.
// ----------------------------------------------------------------------------




#include <ixlib_cmdline.hpp>
#include "test.hpp"




using namespace ixion;




BEGIN_TEST
  char *myargv[] = { "frobnitz", "sucker.cc", "--quick-frob", 
    "--traditional","--style=sloppy","--style=quick","@frobnitz.par" };
  command_line cmdline(7,myargv);
  TEST(~cmdline == 6)
  TEST(cmdline[2] == "--traditional")
  TEST(cmdline.getCommand() == "frobnitz");
  TEST(cmdline.count("--style=") == 3);
  TEST(cmdline.get("--style=",0) == "sloppy");
  TEST(cmdline.get("--style=",2) == "dumb");
END_TEST

