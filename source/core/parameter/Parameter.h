#pragma once

#include "IParameter.h"

#include "Factory.h"
#include "Builder.h"
#include "Singleton.h"

#include "IConfigurator.h"

#include <string>
#include <vector>

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
		public Builder
	{
		public:
			Generic* Build( std::string _name ) override
			{
				Factory& factory = Singleton< Factory >::Instance();
				
				auto config = factory.Create< IConfigurator >( "Configurator", "configuration.xml" ); 
				return new Parameter( config, _name );
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
        Parameter( IConfigurator* _config, std::string _name );
        
        
	/* IParameter methods */
	void Reset() override;

	/* Generic methods **/
	bool SetProperty( std::string _property, const int& _value ) override;

        /* Observer methods **/
        bool Update( IParameter *subject ) override; 

	

};


