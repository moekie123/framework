#pragma once

#include <string>
#include <map>

/**
 * @brief Configurator
 * details An interface to get configuration from an external source
 */
class Configurator
{
	public:
		/* 
		 * @brief Constructor
		 * @details The External Source will get opened in the constructor
		 */
		Configurator( std::string = "default.config" );

		/*
		 * @brief Getter
		 * @details Get a property from the external source
		 * @param _name the name of the parameter or device
		 * @param _property the property of the parameter or device
		 * @param _value the memory location where to store the value
		 * @return True, when property has been succesfull Get
		 */
		virtual bool getProperty( std::string _name, std::string _property, int& _value ) const;

		/*
		 * @brief setter
		 * @details Set a property in the external source
		 * @param _name the name of the parameter or device
		 * @param _property the property of the parameter or device
		 * @param _value the memory location of the new value
		 * @return True, when property has been succesfull Set
		 */
		virtual bool setProperty( std::string _name, std::string _property, const int& _value );

		/*
		 * @brief Signal Getter
		 * @details Get a signal property in the external source
		 * @param _name the name of the signal
		 * @param _signal the property of the signal
		 * @param _value the memory location of the new value
		 * @return True, when property has been succesfull Get
		 */
		virtual bool getSignal( std::string _name, std::string _signal, std::string& _value ) const;

};
