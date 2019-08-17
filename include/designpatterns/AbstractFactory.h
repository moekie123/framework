#pragma once

#include "Generic.h"

#include <string>
#include <map>

class Factory
{
    public:

        void push( std::string _id, Generic* _factory )
        {
            FactoryMap[ _id ] = _factory;
        }
        
        template< class U >
        U* create( std::string _id , std::string _name )
        {
            U* factory = static_cast< U* >( FactoryMap[ _id ]->build( _name ) );
            return factory;
        }

    private:
        std::map< std::string, Generic* > FactoryMap;

};
