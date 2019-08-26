#pragma once

#include "Generic.h"

#include <iostream>
#include <typeinfo>
#include <type_traits>
/**
 * @brief The generic interface for the configurator 
 */
class IConfigurator:
	public Generic
{
	public:
		/**
		 * @brief Search for a property in a external source 
		 * @param _property The name of the property
		 * @param _value The storage location when property is found
		 * @return True when property is found 
		 */
		template< class T >
		bool GetProperty( std::string _property, T& _value ) const
		{
			return Get( _property, _value );	
		}
	
	protected:

		/**
		 * @brief The specialized Getter for an integer
		 * @param _property The name of the property
		 * @param _value The storage location when property is found
		 * @return True when property was found
		 */
		virtual	bool Get( std::string _property, int& _value ) const = 0;

		/** 
		 * @brief The specialized Getter for an string
		 * @param _property The name of the property
		 * @param _value The storage location when property is found
		 * @return True when property was found
		 */
		virtual	bool Get( std::string _property, std::string& _value ) const = 0;
};
