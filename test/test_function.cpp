#include <thelua/function.hpp>
#include <thelua/stack.hpp>
#include <thelua/state.hpp>
#include <lua.hpp>

#include <igloo/igloo_alt.h>
using namespace igloo;

namespace
{

const std::string lua_script(
"    function a_function( text )"
"      a_function_was_called = true"
"      a_function_was_called_with_parameter = text"
"    end " );

}

Describe( a_lua_function )
{
  void SetUp()
  {
    state.reset( new the::lua::State() );
    state->load_string( lua_script );
  }


  It( can_call_a_lua_function_without_parameters_and_return_value )
  {
    state->function( "a_function" )();
    AssertThat( state->get_global< bool >( "a_function_was_called" ), Equals( true ) );
  }

  It( can_call_a_lua_function_with_a_parameter_and_no_return_value )
  {
    state->function( "a_function" )( "hello" );
    AssertThat(
        state->get_global< std::string >( "a_function_was_called_with_parameter" ),
        Equals( "hello" ) );
  }

  std::unique_ptr< the::lua::State > state;
};

