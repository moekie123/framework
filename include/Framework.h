#pragma once

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
};
