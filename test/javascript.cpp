// ----------------------------------------------------------------------------
//  Description      : javascript interpreter
// ----------------------------------------------------------------------------
//  (c) Copyright 2000 by iXiONmedia, all rights reserved.
// ----------------------------------------------------------------------------




#include <fstream>
#include <iostream>
#include <locale.h>
#include <ixlib_config.hpp>
#include <ixlib_javascript.hpp>

#include "aarray.hpp"


using namespace std;
using namespace ixion;
using namespace javascript;




// complex call-in example ----------------------------------------------------
class callIn : public value {
    value_type getType() const { 
      return VT_FUNCTION; 
      } 
    ref<value> call(parameter_list const &parameters);
  };




ref<value> callIn::call(parameter_list const &parameters) 
{
  if (parameters.size() != 1) 
    {
      cout << "callIn needs exactly one parameter" << endl;
      return makeNull();
    }
  if (parameters[0]->getType() == VT_NULL) 
    {
      cout << "got null" << endl;
      return makeNull();
    }
  else if (parameters[0]->getType() == VT_INTEGER) 
    {
      cout << "got an int:" << parameters[0]->toInt() << endl;
      return makeNull();
    }
  else if (parameters[0]->getType() == VT_FLOATING_POINT) 
    {
      cout << "got a float:" << parameters[0]->toFloat() << endl;
      return makeNull();
    }
  else if (parameters[0]->getType() == VT_STRING) 
    {
      cout << "got a string:" << parameters[0]->toString() << endl;
      return makeConstant(17);
    }
  cout << "got something else" << endl;
  return makeNull();
}
// end complex call-in example ------------------------------------------------




// simple call-in example -----------------------------------------------------
IXLIB_JS_DECLARE_FUNCTION(writeStr) 
{
  FOREACH_CONST(first,parameters,parameter_list)
    cout << (*first)->toString();
  return makeNull();
}
// end simple call-in example -------------------------------------------------




// simple call-in example -----------------------------------------------------
IXLIB_JS_DECLARE_FUNCTION(writeLn) 
{
  FOREACH_CONST(first,parameters,parameter_list)
    cout << (*first)->toString();
  cout << endl;
  return makeNull();
}
// end simple call-in example -------------------------------------------------




int main(int argc,char **argv) {
  try {
    ixlibInitI18n();
    
    interpreter ip;
    addStandardLibrary(ip);

    // complex call-in example ------------------------------------------------
    ref<value> ev = new callIn;
    ip.RootScope->addMember("callIn",ev);
    // end complex call-in example --------------------------------------------
    
    // simple call-in example -------------------------------------------------
    ev = new writeStr;
    ip.RootScope->addMember("write",ev);
    // end simple call-in example ---------------------------------------------

    // simple call-in example -------------------------------------------------
    ev = new writeLn;
    ip.RootScope->addMember("writeLn",ev);
    // end simple call-in example ---------------------------------------------
    
    // AArray example
    ev = new AArrayConstructor;
    ip.RootScope->addMember( "AArray", ev);

    if (argc > 1) {
      for (int i = 1;i < argc;i++) {
        ifstream file(argv[i]);
	if (file.bad()) {
	  cerr << "not found: " << argv[i];
	  return 1;
	  }
	ip.execute(file);
	}
      }
    else {
      string command = "";
      while (!cin.eof()) {
        char buffer[1024];
        if (command.size() == 0)
          cout << ">> ";
        else
          cout << "... ";
        cin.getline(buffer,1024);
        command += buffer;
        try {
          try {
            ref<javascript::value> value = ip.execute(command);
            if (value.get() && value->getType() != value::VT_NULL)
              cout << value->stringify() << endl;
            command = "";
            }
          EX_CATCHCODE(javascript,ECJS_UNEXPECTED_EOF,)
          }
        catch (exception &ex) { 
          cerr << ex.what() << endl; 
          command = "";
          } 
        }
      cout << endl;
      }
    }
  catch (exception &ex) { 
    cerr << ex.what() << endl; 
    return 1; 
    }
  }
