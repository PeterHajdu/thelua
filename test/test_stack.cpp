#include <thelua/stack.hpp>
#include <thelua/state.hpp>
#include <lua.hpp>

#include <igloo/igloo_alt.h>
using namespace igloo;

Describe( a_lua_stack )
{
  void SetUp()
  {
    state.reset( new the::lua::State() );
    stack.reset( new the::lua::Stack( *state ) );
  }

  It( can_push_and_pop_int_values_from_the_stack )
  {
    stack->push( 10 );
    AssertThat( stack->pop<double>(), Equals( 10 ) );
    AssertThat( stack->pop<double>(), Equals( 0 ) );
  }

  It( can_push_and_pop_boolean_values_from_the_stack )
  {
    stack->push( true );
    AssertThat( stack->pop<bool>(), Equals( true ) );
    AssertThat( stack->pop<bool>(), Equals( false ) );
  }

  It( can_push_and_pop_string_values_from_the_stack )
  {
    stack->push( std::string( "dog" ) );
    AssertThat( stack->pop<std::string>(), Equals( "dog" ) );
    AssertThat( stack->pop<std::string>(), Equals( "" ) );
  }

  It( can_push_cstring_value_to_the_stack )
  {
    stack->push( "dog" );
    AssertThat( stack->pop<std::string>(), Equals( "dog" ) );
  }

  It( can_push_many_values )
  {
    stack->push( "dog", 10, true );
    AssertThat( stack->pop< bool >(), Equals( true ) );
    AssertThat( stack->pop< int >(), Equals( 10 ) );
    AssertThat( stack->pop< std::string >(), Equals( "dog" ) );
  }

  std::unique_ptr< the::lua::State > state;
  std::unique_ptr< the::lua::Stack > stack;
};

