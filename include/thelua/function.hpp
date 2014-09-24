#pragma once

#include <lua.hpp>
#include <string>

namespace the
{
namespace lua
{

class Function
{
  public:
    Function( lua_State* lua_state, const std::string& name )
      : m_lua_state( lua_state )
      , m_name( name )
    {
    }

    void operator()()
    {
      lua_getglobal( m_lua_state, m_name.data() );
      lua_pcall( m_lua_state, 0, 0, 0 );
    }

  private:
    lua_State* m_lua_state;
    const std::string m_name;
};

}
}

