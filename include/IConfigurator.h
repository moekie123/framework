#pragma once

#include "Generic.h"

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
		 * @param _name The name of the property
		 * @param _attribute The attribute of the property
		 * @param _value The storage location when property is found
		 * @return True when property is found 
		 */
		template< class T >
		bool GetProperty( std::string _name, std::string _attribute, T& _value ) const
		{
			return Get( _name, _attribute, _value );	
		}
	
	protected:

		/**
		 * @brief The specialized Getter for an integer
		 * @param _name The name of the property
		 * @param _attribute The attribute of the property
		 * @param _value The storage location when property is found
		 * @return True when property was found
		 */
		virtual	bool Get( std::string _name, std::string _attribute, int& _value ) const = 0;

		/** 
		 * @brief The specialized Getter for an string
		 * @param _name The name of the property
		 * @param _attribute The attribute of the property
		 * @param _value The storage location when property is found
		 * @return True when property was found
		 */
		virtual	bool Get( std::string _name, std::string _attribute, std::string& _value ) const = 0;
};
