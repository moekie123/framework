#pragma once

#include "IParameter.h"
#include "IConfigurator.h"

#include "AbstractFactory.h"
#include "Builder.h"
#include "Singleton.h"
#include "Observer.h"
#include "Subject.h"

/** 
 *  @brief The (base) Parameter class
 */
class Parameter:
	public IParameter
{
public:

	/**
	 * @brief The Parameter Builder class to create new (base) Parameters
	 */
	class ParameterBuilder: 
		public Builder< IParameter >
	{
	public:
		
		/**
		 * @brief The build method that configures and constructs a new Parameter
 		 */
		static IParameter* Build( std::string _name )
		{
			std::cout << "ParameterBuilder : Build Type\n";

			Factories& factory = Singleton< Factories >::Instance();
	
			const std::string label = "Configurator";
			IConfigurator* config = factory.Construct< IConfigurator >( label );
	
			IParameter *obj = new Parameter( *config, _name );

			return obj;
		}

		/**
	 	 * @brief The constructor will map the Build-Method to the (base) Builder class
		 */
		ParameterBuilder(): Builder( ParameterBuilder::Build )
		{
		}
	};

	/**
	 * @brief The global ParameterBuilder
	 */
	static ParameterBuilder builder;

        /** 
         *  @brief The default constructor
         *  @param _config the configurator
	 *  @param _name the name of the Parameter
         */
        Parameter( const IConfigurator& _config, const std::string& _name );

	/** Object Methods */
	bool Reset() override;
	bool SetProperty( const  std::string& property, const int& value ) override;
	bool GetProperty( const  std::string& property, int& value ) override;

	/** Observer Methods */
	bool Update( const Subject& ) override;
	
};
