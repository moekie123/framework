#pragma once

/**
 * @brief The Framework is the Facaad that constructs the full core and drivers
 */
class Framework
{
	public:

		/**
		 * @brief This constructor will initialize all utilities and drivers.
		 * @details 	In the constructor it will register the Builders of all avaliable classes and store them in a Singleton Factory.
		 * 		This Factory can be used in the project to create new classes.
		 */
		Framework( int argc, char *argv[] );
};
