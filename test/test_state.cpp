#include <thelua/state.hpp>
#include <lua.hpp>

#include <igloo/igloo_alt.h>
using namespace igloo;

Describe( a_lua_state )
{

  It( implicitly_converts_to_lua_state )
  {
    the::lua::State lua_state;
    lua_State *L( lua_state );
    AssertThat( L != nullptr, Equals( true ) );
  }

};

