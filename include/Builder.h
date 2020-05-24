#pragma once

// Interfaces
#include "IConfigurator.h"

// Stl-headers
#include <functional>
#include <string>

/**
 * @brief The (Base) Builder class
 * @details This should from a guidline when a Builder is add to a concrete class. This Base-class can be stored in the Factory by Registering
 */
template< class T >
class Builder
{
public:
	
	/**
	 * @brief The Constructor will map the parent build-method to variable
	 * @details The method, passed as argument will be used in the Factory to create new instances
	 * @param _func The actual method that will build a new instance
 	 */
	Builder( std::function< T*( const IConfigurator*, const std::string& ) > _func ): builder( _func )
	{

	}

	/**
	 * @brief The Build method will use the builder-function (passed as argument in the constructor) to create a new instance
	 # @param _config The pre build Configurator
	 * @param _name The name of the new instance
 	 */
	T* Build( const IConfigurator* _config = nullptr, const std::string& _name = "" )
	{
		return builder( _config, _name );
	}

protected:
	/**
	 * @brief The builder method, that creates a new instance
	 */
	std::function< T*( const IConfigurator*, const std::string& )> builder;
};
