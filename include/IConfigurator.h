#pragma once

#include "Generic.h"

// Stl-Headers
#include <stdexcept>

/**
 * @brief The generic interface for the configurator 
 */
class IConfigurator : public Generic
{
       public:
        /**
		 * @brief Search for a property in a external source 
		 * @param _name The name of the property
		 * @param _attribute The attribute of the property
		 * @param _value The storage location when property is found
		 * @return True when property is found 
		 */
        template <class T>
        bool GetProperty( const std::string& _name, const std::string& _attribute, T& _value ) const
        {
                return Get( _name, _attribute, _value );
        }

       protected:
        /**
		 * @brief The specialized Getter for an integer
		 * @details (On purpose) This method is not abstract because otherwise it could be generarated by the Factory
		 * @param _name The name of the property
		 * @param _attribute The attribute of the property
		 * @param _value The storage location when property is found
		 * @return True when property was found, Throws exception when not implemented
		 */
        virtual bool Get( const std::string& _name, const std::string& _attribute, int& _value ) const
        {
                return false;
        }

        /** 
		 * @brief The specialized Getter for an string
		 * @details (On purpose) This method is not abstract because otherwise it could be generarated by the Factory
		 * @param _name The name of the property
		 * @param _attribute The attribute of the property
		 * @param _value The storage location when property is found
		 * @return True when property was found, Throws exception when not implemented
		 */
        virtual bool Get( const std::string& _name, const std::string& _attribute, std::string& _value ) const
        {
                return false;
        }
};
