#pragma once

#include "Configurator.h"
#include "Singleton.h"

#include "Builder.h"

#include <string>
#include <map>

/**
 * @brief ( Creational Design Pattern ) Factory
 * @details a generic factory that accepts Builders
 */
class Factory
{
    public:
	
	/**
	 * @brief Register
	 * @details Builders should be added to the factory before it can create new
	 * @param _id builder name that can be later called by Create
	 * @param _builder the builder
	 */
        void Register( std::string _id, Builder* _builder )
        {
            BuilderMap[ _id ] = _builder;
        }
       
	/**
	 * @brief Create
	 * @details Build new elemetns with the builder
	 * @param _id the name of the builder to which it is Registered on
	 * @param _name the name of the new creation
	 * @return the new creation
	 */
        template< class U >
        U* Create( std::string _id, std::string _name )
        {
        	U* factory = static_cast< U* >( BuilderMap[ _id ]->build( _name ));
            	return factory;
        }

    private:
        std::map< std::string, Builder* > BuilderMap;

};
