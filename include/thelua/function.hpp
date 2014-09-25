#pragma once

#include <thelua/stack.hpp>
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
      , m_stack( m_lua_state )
      , m_name( name )
    {
    }

    template < typename...Args >
    void operator()( Args&&...args )
    {
      lua_getglobal( m_lua_state, m_name.data() );
      call( 0, std::forward< Args >( args )... );
    }

  private:
    template < typename Head, typename...Tail >
    void call( int number_of_arguments, Head&& head, Tail&&...tail )
    {
      m_stack.push( head );
      call( number_of_arguments + 1, std::forward< Tail >( tail )... );
    }

    void call( int number_of_arguments )
    {
      lua_pcall( m_lua_state, number_of_arguments, 0, 0 );
    }

    lua_State* m_lua_state;
    Stack m_stack;
    const std::string m_name;
};

}
}

