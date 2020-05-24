#pragma once

#include <iostream>
#include <cstring>

#include "Factory.h"
#include "Builder.h"

#include "IParameter.h"
#include "IConfigurator.h"
#include "IChipset.h"
#include "IDevice.h"

#include <stdexcept>

/**
 * @brief The Abstract Factory holds all Factories as Templates, as a varidic
 * @details The templates should be of base class Factory
 */
template< class ... Mixin >
class AbstractFactory: 
	public Mixin...
{
public:

    	/** 
         *  @brief The default constructor
         */
	AbstractFactory(): Mixin()...
	{
		std::cout << "AbstractFactory: Construct\n";
	}
		
	/**
	*  @brief With Construct the Factory will be picked by (template) specialization and the specfic builder in this Factory is choosen by _name   
	*  @details Will throw and exception when _name does not match any builder
	*  @param _name The name of the builder
	*  @return The created class, which is typical a Interface Class
	*/
	template< class T >	
	T* Construct( const std::string& _name )
	{
		std::cout << "AbstractFactory: Construct\n";
		
		auto search = Factory<T>::mBuilders.find( _name );
    		
		if ( search != Factory<T>::mBuilders.end() )
		{
			T* obj = search->second->Build( _name );
			return obj;
    		} 

		throw std::invalid_argument( "AbstractFactory: Unknown Builder" );
	}

	/**
	* @brief New builders can be added by registering
	* @details Will throw an exception when _name is already in use
        * @param _name The name of the registered builder
        * @param _builder The actual builder 
	* @return True, when build was succesfull
	*/ 
	template< class T >	
	bool Register( const std::string& _name, Builder<T>* _builder )
	{
		std::cout << "AbstractFactory: Register\n";

		// Check whether the name already excists
		auto search = Factory<T>::mBuilders.find( _name );
		if ( search == Factory<T>::mBuilders.end() )
		{
			Factory<T>::mBuilders.emplace( _name, _builder );
			return true;
		}
	
		throw std::invalid_argument( "AbstractFactory: Builder already excists" );
	}
};

using Factories = AbstractFactory< 	Factory< IParameter >,
					Factory<  IConfigurator >,
					Factory<  IChipset >,
					Factory<  IDevice >
				>;
