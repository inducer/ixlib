// ----------------------------------------------------------------------------
//  Description      : Regular expressions tests.
// ----------------------------------------------------------------------------
//  (c) Copyright 1998 by iXiONmedia, all rights reserved.
// ----------------------------------------------------------------------------




#include <ixlib_re.hpp>
#include "test.hpp"




using namespace ixion;




string duplicate(string const &src,TSize count) {
  string result;
  result.reserve(count*src.size());
  while (count--) result += src;
  return result;
  }




BEGIN_TEST
  regex_string re,orig;

  orig.parse("duh");
  re = orig;
  TEST(re.match("Duh dah duh doh"))
  TEST(re.match("Duh dah doh duh"))
  TEST(re.match("duh dah doh deh"))
  TEST(!re.match("Duh dah deh doh"))
  
  orig.parse("d\\.h");
  re = orig;
  TEST(!re.match("dih doh"))
  TEST(re.match("dih d.h doh"))

  orig.parse("du*h");
  re = orig;
  TEST(re.match("dihpph daaah dh doh"))
  TEST(re.match("dihpph daaah duuuuuuuuuuuuh doh"))

  orig.parse("du+h");
  re = orig;
  TEST(!re.match("dihpph daaah dh doh"))
  TEST(re.match("dihpph daaah duuuuuuuuuuuuh doh"))
  TEST(re.match(duplicate("dihpph daaah duuuuuuuuuuuuh doh",10)))
  TEST(re.getMatch() == "duuuuuuuuuuuuh")

  orig.parse("du+?");
  re = orig;
  TEST(re.match("dihpph daaah duuuuuu doh"))
  TEST(re.getMatch() == "du")
  
  orig.parse("du{11}h");
  re = orig;
  TEST(!re.match("duuuuuuuuuuh"));
  TEST(re.match("duuuuuuuuuuuh"));
  TEST(!re.match("duuuuuuuuuuuuh") );
  
  orig.parse("du{11,}h");
  re = orig;
  TEST(!re.match("duuuuuuuuuuh"));
  TEST(re.match("duuuuuuuuuuuh"));
  TEST(re.match("duuuuuuuuuuuuh") );
  TEST(re.match("duuuuuuuuuuuuuuuuuuuuh") );

  orig.parse("du{11,13}h");
  re = orig;
  TEST(!re.match("duuuuuuuuuuh"));
  TEST(re.match("duuuuuuuuuuuh"));
  TEST(re.match("duuuuuuuuuuuuuh") );
  TEST(!re.match("duuuuuuuuuuuuuuuuuuuuh") );

  orig.parse("d(u+)");
  re = orig;
  TEST(re.match("dihpph daaah duuuuuu doh"))
  TEST(re.getBackref(0) == "uuuuuu")

  orig.parse("d(a*|e+)gblad");
  re = orig;
  TEST(re.match("de allgemein daaagblad"))
  TEST(re.match("de allgemein deegblad"))
  TEST(!re.match("de allgemein duugblad"))
  
  orig.parse("diz([^a-z]*)ba");
  re = orig;
  TEST(!re.match("cadiz123bou"))
  TEST(re.match("cadiz1945battle"))
  TEST(re.getBackref(0) == "1945")
  
  orig.parse("^cadiz$");
  re = orig;
  TEST(!re.match("whatcadiz"))
  TEST(!re.match("cadizwhat"))
  TEST(re.match("cadiz"))
    
  orig.parse("du+h");
  re = orig;
  TEST(re.match(duplicate("dihpph daaah duuuuuuuuuuuuh doh",90000)))

  orig.parse("1(\\D*)2+");
  re = orig;
  TEST(re.replaceAll("1i222 1aaa2 1uuuuuuuuuuuu2 1o2","2\\01")
    == "2i1 2aaa1 2uuuuuuuuuuuu1 2o1");

  orig.parse("ver(gess|scheiss|acht|knall)+en");
  re = orig;
  TEST(re.match("verknallen"))
  TEST(re.match("verknallscheissen"))
  TEST(re.match("verknallgessscheissen"))
  TEST(!re.match("veren"))
  TEST(!re.match("vergesserachten"))
  
  orig.parse("gun((\\d)+down(\\d)+)?jimbo");
  re = orig;
  TEST(re.match("gun123down456jimbo"))
  TEST(re.countBackrefs() == 7)
  TEST(re.match("gunjimbo"))
  
  orig.parse("^([^ \t]*)[ \t]+(.+)$");
  re = orig;
  TEST(re.match("lctrl alt delete"))
  TEST(re.getBackref(0) == "lctrl")
  TEST(re.getBackref(1) == "alt delete")
  
  // this used to hang
  orig.parse(".*\\.so$");
  re = orig;
  TEST(!re.match("glunko"))
END_TEST
