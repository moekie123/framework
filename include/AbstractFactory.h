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

template< class ... Mixin >
class AbstractFactory: 
	public Mixin...
{
public:
	AbstractFactory(): Mixin()...
	{
		std::cout << "AbstractFactory: Construct\n";
	}
	

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
