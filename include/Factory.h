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
        bool Register( std::string _id )
        {
		/* Check if _id already excists as key in map */
		if ( mBuilderMap.find( _id ) == mBuilderMap.end() ) 
		{
 	            	mBuilderMap[ _id ] = &T::builder;
			return true;
		}

		return false;
       }

	/**
	 * @brief Create
	 * @details Build new elemetns with the builder
	 * @param _id the name of the builder to which it is Registered on
	 * @param _name the name of the new creation
	 * @param _obj the storage of the new create object
	 * @return True when creation was succesfull
	 */
        template< class T >
        T* Create( std::string _id, std::string _name )
        {
		/* Check if _id already excists as key in map */
		if ( mBuilderMap.find( _id ) != mBuilderMap.end() ) 
		{
        		return dynamic_cast<  T* >( mBuilderMap[ _id ]->Build( _name ));
        	}
		return nullptr;
	}

    private:
        std::map< std::string, Builder* > mBuilderMap;

};
