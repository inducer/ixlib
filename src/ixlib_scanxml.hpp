// ----------------------------------------------------------------------------
//  Description      : XML scanner
// ----------------------------------------------------------------------------
//  (c) Copyright 2000 by iXiONmedia, all rights reserved.
// ----------------------------------------------------------------------------




#ifndef IXLIB_SCANXML
#define IXLIB_SCANXML




#undef yyFlexLexer
#define yyFlexLexer xmlFlexLexer
#include <FlexLexer.h>
#undef yyFlexLexer




#endif
