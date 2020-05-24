#pragma once

#include "IParameter.h"
#include "IConfigurator.h"

#include "AbstractFactory.h"
#include "Builder.h"
#include "Singleton.h"
#include "Observer.h"
#include "Subject.h"

class Parameter:
	public IParameter
{
public:

	class ParameterBuilder: 
		public Builder< IParameter >
	{
	public:
		static IParameter* Build( std::string _name )
		{
			std::cout << "ParameterBuilder : Build Type\n";

			Factories& factory = Singleton< Factories >::Instance();
	
			const std::string label = "Configurator";
			IConfigurator* config = factory.Construct< IConfigurator >( label );
	
			IParameter *obj = new Parameter( *config, _name );

			return obj;
		}

		ParameterBuilder(): Builder( ParameterBuilder::Build )
		{
		}
	};

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
