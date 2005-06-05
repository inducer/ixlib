/* -------- definitions ------- */

%option c++ yylineno debug noyywrap prefix="xml" outfile="lex.xml.cpp" batch

%{
#include <ixlib_xml.hpp>
#include <ixlib_token_xml.hpp>




using namespace std;
%}

WHITESPACE      [ \t\n\r]
DIGIT           [0-9]
NONDIGIT        [_a-zA-Z\:\_]
ID_COMPONENT    [_a-zA-Z0-9\.\-\_\:]
IDENTIFIER      {NONDIGIT}{ID_COMPONENT}*


%x Attribute
%x Comment

/* -------- rules -------- */
%%

\<{IDENTIFIER}					BEGIN(Attribute); return TT_XML_BEGIN_TAG;
<Attribute>\>					BEGIN(INITIAL); return TT_XML_END_TAG;
<Attribute>\/\>					BEGIN(INITIAL); return TT_XML_END_SHORT_TAG;
<Attribute>{IDENTIFIER}\=			return TT_XML_ATTRIBUTE_WITH_VALUE;
<Attribute>{IDENTIFIER}				return TT_XML_ATTRIBUTE;
<Attribute>\"[^\"]*\"				return TT_XML_STRINGLITERAL;
<Attribute>\'[^\']*\'				return TT_XML_STRINGLITERAL;

\<\!\-\-					BEGIN(Comment);
<Comment>\-\-\>					BEGIN(INITIAL);
<Comment>.					/* nothing */
<Comment><<EOF>>				EX_THROW(xml,ECXML_UNTERMCOMMENT)

\<\/{IDENTIFIER}\>				return TT_XML_CLOSE_TAG;
[^\< \t\n]+					return TT_XML_TEXT;

<INITIAL,Attribute,Comment>{WHITESPACE}+	/* nothing */
<INITIAL,Attribute,Comment>.    		return TT_UNKNOWN;
<INITIAL,Attribute><<EOF>>    			return TT_EOF;
