#pragma once

#include "Builder.h"

#include <string>
#include <map>

/**
 * @brief An (abstract) Factory that creates new instances with the registed Builders
 * @details This generic constructional design pattern of a generic (abstract) Factory that accepts Builders
 */
class Factory
{
    public:
	
	/**
	 * @brief Register
	 * @details Builders should be added to the factory before it can create new
	 * @param _id builder name that can be later called by Create
	 */	
	template< class T >
        void Register( std::string _id )
        {
            BuilderMap[ _id ] = &T::builder;
        }

	/**
	 * @brief Create
	 * @details Build new elemetns with the builder
	 * @param _id the name of the builder to which it is Registered on
	 * @param _name the name of the new creation
	 * @return the new creation
	 */
        template< class T >
        T* Create( std::string _id, std::string _name )
        {
        	T* obj = static_cast< T* >( BuilderMap[ _id ]->Build( _name ));
            	return obj;
        }

    private:
        std::map< std::string, Builder* > BuilderMap;

};
