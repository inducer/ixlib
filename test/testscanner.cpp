// ----------------------------------------------------------------------------
//  Description      : Scanner tests.
// ----------------------------------------------------------------------------
//  (c) Copyright 1998 by iXiONmedia, all rights reserved.
// ----------------------------------------------------------------------------




#include <iostream>
#include <fstream>
#include <ixlib_textfile.hpp>
#include <ixlib_scanner.hpp>
#include "test.hpp"




using namespace ixion;




void printToken(scanner::token token)
{
  cout << "Type: " << token.Type << endl;
  cout << "Line: " << token.Line << endl;
  cout << "Col : " << token.Column << endl;
  cout << "Text: " << token.Text << endl << endl;
}




BEGIN_TEST
  try {
    ifstream input("src.txt");
    text_file textfile;
    input >> textfile;
    scanner::token_rule_table tokenrules;
    scanner::token_rule	rule[7];
    rule[0].Type=100;
    rule[0].Rule="$";
    rule[1].Type=0;
    rule[1].Rule="[a-zA-Z]+";
    rule[2].Type=1;
    rule[2].Rule="[ 	]+";
    rule[3].Type=2;
    rule[3].Rule="[.,():;_-+*/=#<>]+"; // [] dazu!!!!
    rule[4].Type=3;
    rule[4].Rule="\".*\"";
    rule[5].Type=4;
    rule[5].Rule="[0-9]+";
    rule[6].Type=5;
    rule[6].Rule="//.*$";
    tokenrules.push_back(rule[6]);
    tokenrules.push_back(rule[5]);
    tokenrules.push_back(rule[4]);
    tokenrules.push_back(rule[3]);
    tokenrules.push_back(rule[2]);
    tokenrules.push_back(rule[1]);
    tokenrules.push_back(rule[0]);
    xScanner scanner(textfile, tokenrules);

    while (!scanner.reachedEOF()) printToken(scanner.getNextToken());
  }
  catch (xBaseException &ex)
  {
    char buffer[256];
    cout << endl << ex.getDescription(buffer) << endl;
    TEST(0);
  }
  TEST(1);
END_TEST
