#pragma once

#include <string>
#include <map>

/**
 * @brief This generic configuration class can be used to an configuration from an external source
 */
class Configurator
{
	public:
		/** 
		 * @brief The configuration file will loaded in the in the constructor
		 * @param _name The configuration file 
		 */
		Configurator( std::string _name = "default.config" );

		/**
		 * @brief Get a property from the external source
		 * @param _name the name of the parameter or device
		 * @param _property the property of the parameter or device
		 * @param _value the memory location where to store the value
		 * @return True, when property has been succesfull Get
		 */
		virtual bool getProperty( std::string _name, std::string _property, int& _value ) const;

		/**
		 * @brief Set a property in the external source
		 * @param _name the name of the parameter or device
		 * @param _property the property of the parameter or device
		 * @param _value the memory location of the new value
		 * @return True, when property has been succesfull Set
		 */
		virtual bool setProperty( std::string _name, std::string _property, const int& _value );

		/**
		 * @brief Signal Getter
		 * @details Get a signal property in the external source
		 * @param _name the name of the signal
		 * @param _signal the property of the signal
		 * @param _value the memory location of the new value
		 * @return True, when property has been succesfull Get
		 */
		virtual bool getSignal( std::string _name, std::string _signal, std::string& _value ) const;

};
