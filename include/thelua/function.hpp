#pragma once

#include <thelua/stack.hpp>
#include <lua.hpp>
#include <string>
#include <tuple>

namespace the
{
namespace lua
{

template < size_t nth >
class StackPopper
{
  public:
    template < typename ReturnValue >
    StackPopper( Stack& stack, ReturnValue& return_value )
    {
      typedef typename std::tuple_element< nth, ReturnValue >::type ValueType;
      std::get< nth >( return_value ) = stack.pop< ValueType >();
      StackPopper< nth - 1 >( stack, return_value );
    }
};

template <>
class StackPopper< 0 >
{
  public:
    template < typename ReturnValue >
    StackPopper( Stack& stack, ReturnValue& return_value )
    {
      typedef typename std::tuple_element< 0, ReturnValue >::type ValueType;
      std::get< 0 >( return_value ) = stack.pop< ValueType >();
    }
};

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
      push_to_stack( std::forward< Args >( args )... );
      call_stack( 0, sizeof...( Args ) );
    }

    template < typename...ReturnTypes, typename...Args >
    std::tuple< ReturnTypes...> call( Args&&...args )
    {
      lua_getglobal( m_lua_state, m_name.data() );
      push_to_stack( std::forward< Args >( args )... );
      call_stack( sizeof...( ReturnTypes ), sizeof...( Args ) );

      std::tuple< ReturnTypes... > return_value;
      StackPopper< sizeof...( ReturnTypes ) - 1 >( m_stack, return_value );
      return return_value;
    }

  private:
    template < typename Head, typename...Tail >
    void push_to_stack( Head&& head, Tail&&...tail )
    {
      m_stack.push( head );
      push_to_stack( std::forward< Tail >( tail )... );
    }

    template < typename Head >
    void push_to_stack( Head&& head )
    {
      m_stack.push( head );
    }

    void push_to_stack()
    {
    }

    void call_stack( int number_of_results, int number_of_arguments )
    {
      lua_pcall( m_lua_state, number_of_arguments, number_of_results, 0 );
    }

    lua_State* m_lua_state;
    Stack m_stack;
    const std::string m_name;
};

}
}

