#pragma once

#include <string>
#include <functional>

template< class T >
class Builder
{
public:
	Builder( std::function< T*( std::string ) > b ): builder( b )
	{

	}

	T* Build( const std::string& _name )
	{
		return builder( _name );
	}
protected:
	std::function< T*( std::string )> builder;
};

