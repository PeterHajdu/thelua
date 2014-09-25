#pragma once

#include <lua.hpp>
#include <string>

namespace the
{
namespace lua
{

class Stack
{
  public:
    Stack( lua_State* lua_state )
      : m_lua_state( lua_state )
    {
    }

    template < typename T >
    void push( const T& value );

    void push( const char* value )
    {
      lua_pushstring( m_lua_state, value );
    }

    template < typename T >
    T pop() const;

  private:
    lua_State* m_lua_state;
};

template<>
inline void Stack::push< std::string >( const std::string& value )
{
  lua_pushlstring( m_lua_state, value.data(), value.size() );
}

template<>
inline void Stack::push< bool >( const bool& value )
{
  lua_pushboolean( m_lua_state, value );
}

template<>
inline void Stack::push< double >( const double& value )
{
  lua_pushnumber( m_lua_state, value );
}

template<>
inline void Stack::push< int >( const int& value )
{
  lua_pushnumber( m_lua_state, value );
}

template <>
inline std::string Stack::pop< std::string >() const
{
  const char* const cstr( lua_tostring( m_lua_state, -1 ) );
  std::string value(
      cstr != nullptr ?
      cstr :
      "" );
  lua_pop( m_lua_state, 1 );
  return value;
}

template <>
inline double Stack::pop< double >() const
{
  double value( lua_tonumber( m_lua_state, -1 ) );
  lua_pop( m_lua_state, 1 );
  return value;
}

template <>
inline int Stack::pop< int >() const
{
  return pop< double >();
}


template <>
inline bool Stack::pop< bool >() const
{
  bool value( lua_toboolean( m_lua_state, -1 ) );
  lua_pop( m_lua_state, 1 );
  return value;
}

template <>
inline void Stack::pop< void >() const
{
}

}
}

