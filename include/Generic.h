#pragma once

#include <string>

class Generic
{
    public:
        /** 
         *  @brief getName 
         *  @details return the name of the Parameter
         */
        const std::string& getName() const;
 
        /**
         * @brief create
         * @details The abstract function for the builder 
         */
        virtual Generic* build( std::string _name ) = 0;


    protected:

        /** @brief name of the component */
        std::string mName;

};
