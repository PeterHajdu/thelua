#include <thelua/state.hpp>
#include <lua.hpp>

#include <igloo/igloo_alt.h>
using namespace igloo;

namespace
{

bool lua_c_function_was_called = false;
int lua_c_function( lua_State* )
{
  lua_c_function_was_called = true;
  return 0;
}

}

Describe( function_export )
{
  void SetUp()
  {
    state.reset( new the::lua::State() );
  }

  It( can_export_a_function_with_lua_c_function_syntax )
  {
    state->export_function( "lua_c_function", lua_c_function );
    state->load_string( "lua_c_function()" );
    AssertThat( lua_c_function_was_called, Equals( true ) );
  }

  std::unique_ptr< the::lua::State > state;
};

