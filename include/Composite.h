#pragma once

#include <string>
#include <vector>

#include <string>
#include <iostream>

#include "Generic.h"

/**
 * @brief This generic class can be used to create a Uniform nested structure of Generic elements
 * @details This generic structional design pattern will be used command all (nested) attached classes.
 */
template< class T >
class Composite: 
	public Generic
{
	public:

	/**
	* @brief The 'add'-method will store the compontens that should be triggered when a command is send.
	*/
	void Add ( T& _node )
	{
		std::string nName = _node.GetName();
		
		_node.SetName( std::string( mName + "/" + nName ) );

        	mComponents.push_back( &_node ); 
   	}

	/** 
    	*  @brief Get an property of the class
	*  @details This composite overloads the Genereric method
      	*  @param _name The name of the requested property
	*  @param _value The storage location of the value
	*  @return True, when the value has been succesfully 'Get'
      	*/
	bool GetProperty( const std::string& _name, int& _value ) const override
	{
		bool result = false;
	
		result = Generic::GetProperty( _name, _value );	
		if( result )
			return result;	

		for( auto* component : mComponents )
		{
			result = component->GetProperty( _name, _value );
		
			if( result )
				break;
		}
		return result;
	}

	/** 
      	*  @brief Set an property of the class
 	*  @details This composite overloads the Genereric method
 	*  @param _name The name of the requested property
      	*  @param _value The storage location of the value
	*  @return True, when the value has been succelfully 'Set'
 	*/ 
	bool SetProperty( const std::string& _name, const int& _value ) override
	{
		bool result = false;

		for( auto* component : mComponents )
		{
			result = component->SetProperty( _name, _value );
		
			if( result ) 
				break;
		}
		return result;
	}

    	protected:
    	/**
	 * @brief The list of nested (composite) components
	 */
        std::vector< T* > mComponents;
};
