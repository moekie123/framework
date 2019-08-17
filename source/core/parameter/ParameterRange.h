#pragma once

#include "Parameter.h"

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
         *  @brief Constructor
         *  @param _name the name of the Parameter
         */
        ParameterRange( );
           
        /** 
         *  @brief Constructor
         *  @param _name the name of the Parameter
         */
        ParameterRange( std::string _name );
        
        /// Setter
        void setProperty( std::string _property, int _value ) override;
       
};
