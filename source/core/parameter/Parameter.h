#pragma once

#include "IParameter.h"

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
         * @brief Builder
         * @details Builder to create a new Parameter fully constructed and initiliazed
         * @param _name the name of the Parameter
         * @return Generic Class
         */
        Generic* build( std::string _name ) override;

        /** 
         *  @brief Constructor
         *  @param _name the name of the Parameter
         */
        Parameter();

        /** 
         *  @brief Constructor
         *  @param _name the name of the Parameter
         */
        Parameter( std::string _name );
        
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
