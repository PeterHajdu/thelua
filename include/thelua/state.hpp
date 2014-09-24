#pragma once

#include <lua.hpp>

namespace the
{
namespace lua
{

class State final
{
  public:
    State()
      : m_lua_state( luaL_newstate() )
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
  private:
    lua_State* m_lua_state;
};

}
}

