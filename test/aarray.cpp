#include "aarray.hpp"

using namespace ixion;
using namespace javascript;

AArray::AArray( const AArray &a ) {
  // copies all key - value pairs
  for( value_array::iterator it = a.array.begin(); it != a.array.end(); ++it )
    array.push_back( new pair( (*it)->first->duplicate(), (*it)->second->duplicate() ) );
  }

ref<value> AArray::subscript( value const &index ) {
  value *v = const_cast<value*>(&index);
  
  ref<value> r = v->duplicate();

  //searches for the index, and if not found
  
  for( value_array::iterator it = array.begin(); it != array.end(); ++it )
    if( (*it)->equal( r ) )
      return (*it)->second;
  
  // creates a new pair
  /*
    you have to use makeLValue for the value,
    and if you wan't to change the key too, 
    you have to do the same with the key
  */
  array.push_back( new pair( makeLValue(r), makeLValue( makeNull() ) ) );
  
  // retuns the last element of the array
  return (*array.rbegin())->second;
  }

ref<value> AArray::lookup( std::string const &id ) {
  if( id  == "length" )
    return makeConstant( array.size() );

  return super::lookup( id );
  }

ref<value> AArray::callMethod( std::string const &id, parameter_list const &param ) {
  if( id == "reverse" && param.size() == 0 ) {
    reverse( array.begin(), array.end() );
    return this;
    }

  if( id == "clear" && param.size() == 0 ) {
    clear_array();
    return this;
    }

  // returns the key
  if( id == "key" && param.size() == 1 ) {
    value_array::size_type index = param[0]->toInt();

    if( index < 0 || index >= array.size() )
      return makeNull();

    return array[index]->first;
    }

  EXJS_THROWINFO(ECJS_UNKNOWN_IDENTIFIER,("AArray."+id).c_str())  
  }




std::string AArray::stringify() const {
  value_array::iterator first( array.begin() ), 
                        last( array.end() );

  std::string result = "{ ";

  bool at_first = true;

  while( first != last ) {
    if( !at_first ) 
      result += ',';
    else
      at_first = false;

    result += (*first)->first->stringify() + " => " + (*first)->second->stringify();

    ++first;
    }
  
  return result + " }";
  }




// index mode
ref<value> AArray::call( parameter_list const &param ) {
  if( param.size() == 1 ) {
    value_array::size_type index = param[0]->toInt();

    if( index < 0 || index >= array.size() )
      return makeNull();

    return array[index]->second;
    }

  return makeNull();
  }

void AArray::clear_array() {
  for( value_array::iterator it = array.begin(); it != array.end(); ++it )
    delete *it;

  array.clear();
  }


ref<value> AArrayConstructor::construct( parameter_list const &par )
{
  if( par.size() == 0 )
    return new AArray();

  if( par.size() == 1 ) {
    // try copying from a given AArray

    ref<value> v = par[0]->eliminateWrappers();

    AArray *array  = dynamic_cast<AArray*>( v.get() );

    if( array )
      // yes value is an AArray
      return new AArray( *array );
    else
      EXJS_THROWINFO(ECJS_CANNOT_CONVERT,( (valueType2string(par[0]->getType()) + " to AArray" ).c_str()) );  
    }

  EXJS_THROWINFO(ECJS_UNKNOWN_IDENTIFIER,"invalid number of args");
  }
