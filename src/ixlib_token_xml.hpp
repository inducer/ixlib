// ----------------------------------------------------------------------------
//  Description      : Token definitions for XML scanner
// ----------------------------------------------------------------------------
//  (c) Copyright 2000 by iXiONmedia, all rights reserved.
// ----------------------------------------------------------------------------




#ifndef IXLIB_TOKENXML
#define IXLIB_TOKENXML




#include <ixlib_token_lex.hpp>




#define TT_XML_BEGIN_TAG		(TT_USER+0)
#define TT_XML_END_TAG			(TT_USER+1)
#define TT_XML_END_SHORT_TAG		(TT_USER+2)
#define TT_XML_CLOSE_TAG		(TT_USER+3)
#define TT_XML_ATTRIBUTE		(TT_USER+4)
#define TT_XML_ATTRIBUTE_WITH_VALUE	(TT_USER+5)
#define TT_XML_STRINGLITERAL		(TT_USER+6)
#define TT_XML_TEXT			(TT_USER+7)




#endif
