#pragma once

// Stl-Headers
#include <map>
#include <string>

// Forward Declaration
class Generic;

/**
 * @brief The (Base) Object class
 * @details This class holds the most basic functionalliy that every component in the Framework should be able to work with. 
 *          The Generic class will inherent this together with the fundamentals design pattern class
 */
class Object
{
       public:
        Object();

        virtual ~Object() = default;

        /** 
         *  @brief get the name of the derived class
	 *  @return the name of the created class
         */
        virtual const std::string& GetName() const;

        /** 
         *  @brief set the name of the derived class
      	 *  @param _name the new name of the derived class
	 *  @return true, when the renaming was succesfull
         */
        virtual bool SetName( const std::string& _name );

        /** 
      	*  @brief Set an property of the class
      	*  @param _property The name of the requested property
      	*  @param _value The storage location of the value
	*  @return True, when the value has been succelfully 'Set'
 	*/
        virtual bool SetProperty( const std::string& _property, const int& _value );

        /** 
    	*  @brief Get an property of the class
      	*  @param _property The name of the requested property
	*  @param _value The storage location of the value
	*  @return True, when the value has been succesfully 'Get'
      	*/
        virtual bool GetProperty( const std::string& _property, int& _value );

        /**
	*  @brief Reset the object
	*  @return True, when reset was succesfull
	*/
        virtual bool Reset();

        /**
	*  @brief Get current state of object in a string
	*  @return The current state of object
	*/
        virtual const std::string ToString() const;

        /**
	*  @brief Get current state of object in json-format
	*  @return The current state of object
	*/
        virtual const std::string ToJson() const;

       protected:
        /** @brief The Generic Object Element
	*   @details used for upwards inheritance  
	*/
        Generic* mGeneric;

        /** @brief name of the component */
        std::string mName;

        /** @brief the properties of the Parameter */
        std::map<std::string, int> mProperties;
};
