#pragma once

#include <string>
#include <map>

/**
 * @brief An generic class that should be inherent by all used classes in the Framework.
 * @details All generic design patters should be compatible with this base class
 */
class Generic
{
    public:

	/* *
	 * @brief The basic constructor to initiaaze the generic properties
	 */
       	Generic();

	/** 
         *  @brief Get the name of the derived class
	 *  @return The name of the created class
         */
        const std::string& GetName() const;
 
	/** 
         *  @brief Set the name of the derived class
      	 *  @param _name The new name of the derived class
	 *  @return True, when the renaming was succesfull
         */
       	bool SetName( const std::string& _name );

	/** 
    	*  @brief Get an property of the class
      	*  @param _property The name of the requested property
	*  @param _value The storage location of the value
	*  @return True, when the value has been succesfully 'Get'
      	*/
	virtual bool GetProperty( const std::string& _property, int& _value ) const;

	/** 
      	*  @brief Set an property of the class
      	*  @param _property The name of the requested property
      	*  @param _value The storage location of the value
	*  @return True, when the value has been succelfully 'Set'
 	*/ 
	virtual bool SetProperty( const std::string& _property, const int& _value );

    protected:

        /** @brief name of the component */
        std::string mName;

	/** @brief the properties of the Parameter */
        std::map< std::string, int > mProperties;
};
