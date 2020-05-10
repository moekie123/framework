#pragma once

#include "IConfigurator.h"

#include "Builder.h"

#include <string>
#include <map>
#include <iostream>

#include "Singleton.h"

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
				Generic* Build( std::string _name ) override
				{
					return new Configurator( _name );
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

		/** 
		 * @brief The name of the configuration file
		 */
		static std::string mConfigFileName;

		/* Generic methods **/

	private:
		/* IConfigurator */
		bool Get( std::string _name, std::string _attribute, int& _value ) const override;
		bool Get( std::string _name, std::string _attribute,  std::string& _value ) const override;
	
};
