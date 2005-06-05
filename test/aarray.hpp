#include <ixlib_javascript.hpp>
#include <iostream>

namespace ixion {

  namespace javascript {

    /* 
       The class is very similar to Array, but
       allows using various values as the index.

       it's very similar to arrays in PHP

       there is an example script: aarray.js
    */

    class AArray : public value_with_methods {
      private:

	typedef value_with_methods super;

      protected:

	// structure that holds a key and value as javascript::value 
	struct pair {
	  ref<value> first;
	  ref<value> second;

	  pair( ref<value> a, ref<value> b )
	    : first( a ), second( b )
	  {}

	  pair( ref<value> a )
	    : first( a )
	  {}

	  // compare function
	  bool equal( ref<value> v )
	  {
	    if( first->getType() != v->getType() )
	      return false;

	    return (first->operatorBinary( OP_EQUAL, v ))->toBoolean();	
	  }
	};

	typedef std::vector< pair* >  value_array;

	mutable value_array array;

      public:

	AArray() {}
	AArray( const AArray &aarray );

	~AArray() { clear_array(); }


	value_type getType() const { return VT_BUILTIN; }

	ref<value> duplicate() { return new AArray( *this ); }


	// indexing a["foo"]
	ref<value> subscript( value const &index );

	// length value
	ref<value> lookup( std::string const &identifier );

	std::string stringify() const;

	// number indexing a(1)
	ref<value> call( parameter_list const &param );

	// reverse, key and clear
	ref<value> callMethod( std::string const &identifier, parameter_list const &param );

      private:

	// frees all pair pointers
	void clear_array();
    };
    
    class AArrayConstructor : public value
    {
    public:
      
      value_type getType() const { return VT_TYPE; }
      ref<value> duplicate(){ return this; }
      ref<value> construct( parameter_list const &parameters );
    };


   } // namespace javascript

} // namespace ixion
