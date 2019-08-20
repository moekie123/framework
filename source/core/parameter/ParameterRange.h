#pragma once

#include "Parameter.h"

#include "Singleton.h"
#include "Builder.h"

#include "Configurator.h"

#include <string>
#include <map>
#include <vector>


/** 
 *  @brief The (derived) Parameter Range
 *  @details The ParameterRange has threshold Parameters that will limit the setpoint of the parameter
 */
class ParameterRange: 
    public Parameter
{
    public:
 
   	/**
	 * @brief The ParameterRange Builder to create new ParameterRanges
	 */
	class ParameterRangeBuilder:
		public Builder
	{
		public:
		Generic* build( std::string _name ) override
		{
			Configurator& config = Singleton< Configurator >::Instance();
			return new ParameterRange( config, _name );
		}
	};
	/**
	 * @brief The global ParameterRange Builder
	 */
	static ParameterRangeBuilder builder;

        /** 
         *  @brief Default Constructor
	 *  @details TODO Most likely wont be nessacary
         */
        ParameterRange( );
           
        /** 
         *  @brief The default constructor
	 *  @param _config The Configurator to overwrite the default values
	 *  @param _name the name of the Parameter
         */
        ParameterRange( Configurator& _config, std::string _name );
       
};

ParameterRange::ParameterRangeBuilder ParameterRange::builder;
