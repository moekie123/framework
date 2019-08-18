#pragma once

#include "IParameter.h"
#include "Configurator.h"

#include "designpatterns/Builder.h"
#include "designpatterns/Singleton.h"

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
         *  @param _name the name of the Parameter
         */
        Parameter();

        /** 
         *  @brief Constructor
         *  @param _config the configurator
	 *  @param _name the name of the Parameter
         */
        Parameter( Configurator& _config, std::string _name );
        
        /// Getter
        const int& getProperty( std::string _property ) const override;
        
        /// Setter
        void setProperty( std::string _property, int _value ) override;

        void reset() override;

        /** Observer **/
        void update( IParameter *subject ) override; 

    protected: 

        /** @brief the properties of the Parameter */
        std::map< std::string, int > mProperties;

};


