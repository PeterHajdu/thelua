#include <thelua/state.hpp>
#include <lua.hpp>

#include <igloo/igloo_alt.h>
using namespace igloo;

Describe( a_lua_state )
{
  void SetUp()
  {
    state.reset( new the::lua::State() );
  }

  It( implicitly_converts_to_lua_state )
  {
    lua_State *L( *state );
    AssertThat( L != nullptr, Equals( true ) );
  }

  It( executes_lua_code )
  {
    state->load_string( "a_number = 10" );
  }

  It( can_return_global_lua_objects )
  {
    state->load_string( "a_number = 10\na_string=\"dog\"" );
    AssertThat( state->get_global< int >( "a_number" ), Equals( 10 ) );
    AssertThat( state->get_global< std::string >( "a_string" ), Equals( "dog" ) );
  }

  std::unique_ptr< the::lua::State > state;
};

