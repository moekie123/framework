#pragma once

#include "Builder.h"
#include "IConfigurator.h"

#include <string>
#include <map>

#include <iostream>
#include <stdexcept>

/**
 * @brief An (abstract) Factory that creates new instances with the registed Builders
 * @details This generic constructional design pattern of a generic (abstract) Factory that accepts Builders
 */
class Factory
{
    public:
	
    	/** 
         *  @brief The default constructor
         */
        Factory()
	{
	}

    	/** 
         *  @brief The default constructor
         *  @param _config the configurator
         */
        Factory( const IConfigurator& _config )
	{
	}

	/**
	 * @brief Register
	 * @details Builders should be added to the factory before it can create new
	 * @param _id builder name that can be later called by Create
	 */	
	template< class T >
        bool Register( const std::string& _id )
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
	 * @return True when creation was succesfull
	 */
        template< class T >
        T& Create( const std::string& _id, const std::string& _name )
        {
		/* Check if _id already excists as key in map */
		if ( mBuilderMap.find( _id ) != mBuilderMap.end() ) 
		{
			/* ###### ERROR ###### */
			/*
				The downcast to a generalized base class (generic) will back updated by the dynamic_cast
				However, the downcast lost all parent vtable properties....
				There for the upcast, by dynamice, will not have the properties as before the downcast....
			*/
        		return dynamic_cast< T& >( mBuilderMap[ _id ]->Build( _name ));
        	}
		throw std::invalid_argument( "received negative value" );
	}

    private:
        std::map< std::string, Builder* > mBuilderMap;

};
