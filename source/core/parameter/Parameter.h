#pragma once

#include "IParameter.h"

#include "Builder.h"
#include "Singleton.h"

#include "Configurator.h"

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
			Generic* build( std::string _name ) override
			{
				Configurator& config = Singleton< Configurator >::Instance();
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
        Parameter( Configurator& _config, std::string _name );
        
        
	/* IParameter methods */
	void reset() override;

	/* Generic methods **/
	bool setProperty( std::string _property, const int& _value ) override;

        /* Observer methods **/
        void update( IParameter *subject ) override; 

};


