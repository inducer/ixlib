// ----------------------------------------------------------------------------
//  Description      : iXiONmedia XML parser
// ----------------------------------------------------------------------------
//  (c) Copyright 1999 by iXiONmedia, all rights reserved.
// ----------------------------------------------------------------------------




#ifndef IXLIB_XML
#define IXLIB_XML




#include <vector>
#include <map>
#include <ixlib_exbase.hpp>
#include <ixlib_scanner.hpp>




// Error codes ----------------------------------------------------------------
#define ECXML_SYNTAX      	0
#define ECXML_NOTEXTHERE	1
#define ECXML_NOLITHERE		2
#define ECXML_LITEXPECTED	3
#define ECXML_UNEXPECTEDEND	4
#define ECXML_CLOSETAGEXPECTED	5
#define ECXML_CLOSETAGNAME	6
#define ECXML_UNTERMCOMMENT	7




// xml_exception --------------------------------------------------------------
namespace ixion {
  struct xml_exception : public base_exception {
    xml_exception(TErrorCode error,char const *info = NULL,char *module = NULL,
      TIndex line = 0,char *category = NULL)
      : base_exception(error,info,module,line,"XML") {
      }
    xml_exception(TErrorCode error, TIndex line = 0, char const *info = 0);
    virtual char *getText() const;
    };




// Exception throw macro ------------------------------------------------------
#define EXXML_THROW(CODE,TOKEN)\
  throw xml_exception(CODE,(TOKEN).Line,NULL);




// xml_file -------------------------------------------------------------------
  /**
  An Object implementing an XML file parser and writer.
  
  tag::Children and tag::Text use the same indices. Thus, in the following
  piece of XML 
  
  <code>
    <XML>  paff <EXPLOSION/> puff </XML>
    </code>
    
  Text[0] would be "paff", Children[0] would be "EXPLOSION", Text[1] would
  be "puff".
  */
  class xml_file {
    protected:
      typedef scanner::token_list::const_iterator token_iterator;
    
    public:
      class tag {
        protected:
          std::string					Name; 
  
        public:
	  typedef std::map<std::string,std::string>	attribute_map;
	  typedef std::vector<tag *>			children_list;
	  typedef std::vector<std::string>		text_list;
	  
          attribute_map 				Attributes;
          children_list					Children;
          text_list					Text;
	  
	  typedef children_list::iterator 		iterator;
	  typedef children_list::const_iterator 	const_iterator;
  
          tag() {
            Text.push_back("");
            }
          tag(std::string const &name)
            : Name(name) {
            Text.push_back("");
            }
          tag(tag const &source);
          ~tag();
          void appendTag(tag *tag) {
            insertTag(Text.end(),tag);
            }
          void insertTag(children_list::iterator before,tag *tag);
          void insertTag(text_list::iterator before,tag *tag);
          tag *findTag(std::string const &name);
          
          void name(std::string const &name) {
            Name = name;
            }
          std::string name() const {
            return Name;
            }
	  
          iterator begin() {
            return Children.begin();
            }
          const_iterator begin() const {
            return Children.begin();
            }
          iterator end() {
            return Children.end();
            }
          const_iterator end() const {
            return Children.end();
            }
  
	  /// \deprecated use name(n) instead
          void setName(std::string const &n) {
            name(n);
            }
	  /// \deprecated use name() instead
          std::string getName() const {
            return name();
            }

        protected:
          void parse(token_iterator &first, token_iterator const &last);
          void write(std::ostream &ostr, TSize indent);
          
          void setLastText(std::string const &text) {
            Text.back() = text;
            }
  
          friend class xml_file;
        };
      
      friend class tag;
  
    protected:
      tag				*RootTag;
      
    public:  
      xml_file()
        : RootTag(NULL) {
        }
      ~xml_file() {
        if (RootTag) delete RootTag;
        }
        
      void read(std::istream &istr);
      void write(std::ostream &ostr);
      
      tag *rootTag() const {
        return RootTag;
        }
      void rootTag(tag *newroot) {
        if (RootTag) delete RootTag;
        RootTag = newroot;
        }
      void clear() {
        setRootTag(NULL);
        }
        
      /// \deprecated use rootTag() instead
      tag *getRootTag() const {
        return rootTag();
        }
      /// \deprecated use rootTag(t) instead
      void setRootTag(tag *newroot) {
        rootTag(newroot);
        }
    protected:
      void parse(scanner::token_list const &tokenlist);
      
      static void skipComment(token_iterator &first,token_iterator const &last);
    };
  }



#endif
