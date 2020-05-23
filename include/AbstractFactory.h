#pragma once

#include <iostream>
#include <cstring>

#include "Factory.h"
#include "Builder.h"

#include "IParameter.h"
#include "IConfigurator.h"
#include "IChipset.h"
#include "IDevice.h"

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

		std::cout << "Not Found\n";
		return nullptr;
	}

	template< class T >	
	bool Register( const std::string& name, Builder<T>* builder )
	{
		std::cout << "AbstractFactory: Register\n";
		Factory<T>::mBuilders.emplace( name, builder );
		return false;
	}
};

using Factories = AbstractFactory< 	Factory< IParameter >,
					Factory<  IConfigurator >,
					Factory<  IChipset >,
					Factory<  IDevice >
				>;
