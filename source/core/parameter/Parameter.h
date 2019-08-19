#pragma once

#include "IParameter.h"

#include "Builder.h"
#include "Singleton.h"

#include "Configurator.h"

#include <string>
#include <vector>

/** 
 *  @brief Base: Parameter 
 *  @details base framework for a Parameter,
 */
class Parameter: 
    public IParameter
{

public:
	/**
	 * Builder
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
	static ParameterBuilder builder;
	
        /** 
         *  @brief Constructor
         *  @param _config the configurator
	 *  @param _name the name of the Parameter
         */
        Parameter( Configurator& _config, std::string _name );
        
        void reset() override;

	/** Generic **/
	bool setProperty( std::string _property, const int& _value ) override;

        /** Observer **/
        void update( IParameter *subject ) override; 

};


