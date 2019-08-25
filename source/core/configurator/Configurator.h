#pragma once

#include "IConfigurator.h"

#include "Builder.h"

#include <string>
#include <map>

/**
 * @brief This generic configuration class can be used to an configuration from an external source
 */
class Configurator:
	public IConfigurator
{
	public:
		/**
		 * @brief The Configurator Builder class to create new (base) Configurator
		 */
		class ConfiguratorBuilder:
			public Builder
		{
			public:
				Generic* Build( std::string _filename ) override
				{
					return new Configurator( _filename );
				}
		};
		/**
		 * @brief The global ParameterBuilder
		 */
		static ConfiguratorBuilder builder;

		/** 
		 * @brief The configuration file will loaded in the in the constructor
		 * @param _name The configuration file 
		 */
		Configurator( std::string _name );

		/* Generic */	
		bool GetProperty( std::string _property, int& _value ) const override;
		bool SetProperty( std::string _property, const int& ) override;
};
