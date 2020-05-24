#pragma once

// Interfaces
#include "IConfigurator.h"

// Design Patterns
#include "Builder.h"
#include "Singleton.h"

// Stl-Headers
#include <iostream>
#include <map>
#include <string>

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
			public Builder< IConfigurator >
		{
		public:

			/**
			 * @brief The build method that configures and constructs a new Parameter
 			 */
			static IConfigurator* Build( std::string _name )
			{
				IConfigurator& obj = Singleton< Configurator >::Instance();
				return &obj;
			}

			/**
	 		 * @brief The constructor will map the Build-Method to the (base) Builder class
		 	 */
			ConfiguratorBuilder(): Builder( ConfiguratorBuilder::Build )
			{
				std::cout << "ConfiguratorBuilder : Construct\n";
			}
		};

		/**
		 * @brief The global ParameterBuilder
		 */
		static ConfiguratorBuilder builder;

		/** 
		 * @brief The configuration file will loaded in the in the constructor
		 */
		Configurator();

		/** 
		 * @brief The name of the configuration file
		 */
		static std::string mConfigFileName;

	private:
		/* IConfigurator */
		bool Get( const std::string& _name, const std::string& _attribute, int& _value ) const override;
		bool Get( const std::string& _name, const std::string& _attribute,  std::string& _value ) const override;
	
};
