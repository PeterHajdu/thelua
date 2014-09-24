#pragma once

#include <lua.hpp>
#include <string>
#include <thelua/stack.hpp>

namespace the
{
namespace lua
{

class State final
{
  public:
    State()
      : m_lua_state( luaL_newstate() )
      , m_stack( m_lua_state )
    {
      luaL_openlibs( m_lua_state );
    }

    ~State()
    {
      lua_close( m_lua_state );
    }

    State( const State& ) = delete;
    State& operator=( const State& ) = delete;

    inline operator lua_State*()
    {
      return m_lua_state;
    }

    void load_string( const std::string& lua )
    {
      luaL_dostring( m_lua_state, lua.data() );
    }

    template < typename T >
    T get_global( const std::string& name )
    {
      lua_getglobal( m_lua_state, name.data() );
      return m_stack.pop< T >();
    }

  private:
    lua_State* m_lua_state;
    Stack m_stack;
};

}
}

