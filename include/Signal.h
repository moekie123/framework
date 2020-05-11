#pragma once

#include "IConfigurator.h"

#include <string>

/**
 * @brief The base Signal class to open a file descriptor to a signal
 */
class Signal
{
	public:

		/**
		 * @brief The default constructor
		 * @param _config The Configurator that will fill in the default values
		 * @param _name The name of the created Signal
		 */
		Signal( const IConfigurator& _config, const std::string& _name );
	
		/**
		 * @brief The setter of the signal
		 * @details TODO Should return a bool, whether the write was succesfull
		 * @param _value The new value to which it will be set
		 */
    		virtual void Write( const int& _value );

		/**
		 * @brief The getter of the signal
		 * @details TODO Should return a bool, whether the read was succesfull
		 * @param _value The new value of the signal
		 */
    		virtual void Read ( int& _value );

	private:
		const std::string mName;
		const std::string mFilename;
};
