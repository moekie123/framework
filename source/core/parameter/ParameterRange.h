#pragma once

#include "Parameter.h"

#include "Singleton.h"
#include "Builder.h"

#include "Configurator.h"

#include <string>
#include <map>
#include <vector>


/** 
 *  @brief Derived: Parameter Range
 *  @details The ParameterRange has threshold Parameters that will limit the setpoint of the parameter
 */
class ParameterRange: 
    public Parameter
{
    public:
 
   	/**
	 * Builder
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
	static ParameterRangeBuilder builder;

        /** 
         *  @brief Constructor
         *  @param _name the name of the Parameter
         */
        ParameterRange( );
           
        /** 
         *  @brief Constructor
         *  @param _name the name of the Parameter
         */
        ParameterRange( Configurator& _config, std::string _name );
        
        /// Setter
        void setProperty( std::string _property, int _value ) override;
       
};

ParameterRange::ParameterRangeBuilder ParameterRange::builder;
