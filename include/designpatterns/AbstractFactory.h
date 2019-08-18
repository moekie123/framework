#pragma once

#include "Configurator.h"
#include "Singleton.h"

#include "Builder.h"

#include <string>
#include <map>

class Factory
{
    public:

        void Register( std::string _id, Builder* _builder )
        {
            BuilderMap[ _id ] = _builder;
        }
       
        template< class U >
        U* Create( std::string _id, std::string _name )
        {
        	U* factory = static_cast< U* >( BuilderMap[ _id ]->build( _name ));
            	return factory;
        }

    private:
        std::map< std::string, Builder* > BuilderMap;

};
