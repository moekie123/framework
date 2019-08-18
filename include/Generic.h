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
 
    protected:

        /** @brief name of the component */
        std::string mName;

};
