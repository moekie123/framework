#pragma once

#include <string>

/**
 * @brief The Framework is the Facaad that constructs the full core and drivers
 * @details This class should be declared such that the class will initialized at startup of the program
 */
class Framework
{
	public:
		/**
		 * @brief This constructor will initialize all utilities and drivers.
		 */
		Framework( int argc, char *argv[] );

	private:
		/**
		 * @brief The argument parser
		 */
		int parseArguments( int argc, char* argv[] );

		/**
		 * @brief The name of the configuration file
		 * TODO Renamen such that it corrosponds the (static) configuration or link to it by a refrence
		 */
		std::string mConfigurationFilename;
};
