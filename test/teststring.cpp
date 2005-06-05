// ----------------------------------------------------------------------------
//  Description      : String component tests.
// ----------------------------------------------------------------------------
//  (c) Copyright 1998 by iXiONmedia, all rights reserved.
// ----------------------------------------------------------------------------




#include <iostream>
#include <ixlib_string.hpp>
#include <vector>
#include "test.hpp"




using namespace ixion;




BEGIN_TEST
  vector<string> vec;
  vec.push_back("A"); vec.push_back("B"); vec.push_back("C");
  TEST(concat(vec.begin(),vec.end(),"-") == "A-B-C")
  
  // test string replace routines
  std::string weenie = "Gosh. I'm a weenie.";
  weenie = findReplace(weenie,string("Gosh."),"Josh.");
  TEST(weenie == "Josh. I'm a weenie.") 

  weenie = "I'm a helpless helping weenie.";
  weenie = findReplace(weenie,string("help"),"rest");
  TEST(weenie == "I'm a restless resting weenie.") 

  weenie = "I'm a helpless helping weenie.";
  weenie = findReplace(weenie,string("weenie."),"woonie.");
  TEST(weenie == "I'm a helpless helping woonie.")

  // test char * replace routines
  weenie = "Gosh. I'm a weenie.";
  weenie = findReplace(weenie,string("Gosh."),"Josh.");
  TEST(weenie == "Josh. I'm a weenie.") 

  weenie = "I'm a helpless helping weenie.";
  weenie = findReplace(weenie,string("help"),"rest");
  TEST(weenie == "I'm a restless resting weenie.") 

  weenie = "I'm a helpless helping weenie.";
  weenie = findReplace(weenie,string("weenie."),"woonie.");
  TEST(weenie == "I'm a helpless helping woonie.")

  weenie = "I'm a helpless helping weenie.";
  weenie = findReplace(weenie,'e','o');
  TEST(weenie == "I'm a holploss holping woonio.") 
  
  weenie = "       gimme a four-letter word";
  TEST(removeLeading(weenie) == "gimme a four-letter word")
  TEST(removeTrailing(weenie) == "       gimme a four-letter word")
  TEST(removeLeadingTrailing(weenie) == "gimme a four-letter word")
  
  weenie = "gimme a four-letter word       ";
  TEST(removeLeading(weenie) == "gimme a four-letter word       ")
  TEST(removeTrailing(weenie) == "gimme a four-letter word")
  TEST(removeLeadingTrailing(weenie) == "gimme a four-letter word")

  weenie = "       gimme a four-letter word       ";
  TEST(removeLeading(weenie) == "gimme a four-letter word       ")
  TEST(removeTrailing(weenie) == "       gimme a four-letter word")
  TEST(removeLeadingTrailing(weenie) == "gimme a four-letter word")
  
  weenie = "      ";
  TEST(removeLeading(weenie) == "")
  TEST(removeTrailing(weenie) == "")
  TEST(removeLeadingTrailing(weenie) == "")
  
  { string t1 = "Ich bin die uebelste Wurst des gesamten Universums, und ich "
    "werde gleich Base64-kodiert. I am the most evil sausage of the entire "
    "universe, and I'm gonna be Base64-encoded in a few seconds!";
    string base64;
    base64encode(base64,(TByte *) t1.data(),t1.size());
    TByte buffer[getMaxBase64DecodedSize(base64.size())+1];
    TSize size = base64decode(buffer,base64);
    TEST(t1 == string((char *) buffer,size))
    }

  { string t1 = "Ich bin die uebelste Wurst des gesamten Universums, und ich "
    "werde gleich Base64-kodiert. I am the most evil sausage of the entire "
    "universe, and I'm gonna be Base64-encoded in a few seconds!!";
    string base64;
    base64encode(base64,(TByte *) t1.data(),t1.size());
    TByte buffer[getMaxBase64DecodedSize(base64.size())+1];
    TSize size = base64decode(buffer,base64);
    TEST(t1 == string((char *) buffer,size))
    }

  { string t1 = "Ich bin die uebelste Wurst des gesamten Universums, und ich "
    "werde gleich Base64-kodiert. I am the most evil sausage of the entire "
    "universe, and I'm gonna be Base64-encoded in a few seconds!!!";
    string base64;
    base64encode(base64,(TByte *) t1.data(),t1.size());
    TByte buffer[getMaxBase64DecodedSize(base64.size())+1];
    TSize size = base64decode(buffer,base64);
    TEST(t1 == string((char *) buffer,size))
    }
END_TEST
