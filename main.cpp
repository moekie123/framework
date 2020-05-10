#include "Framework.h"
#include "version.h"

#include "Singleton.h"
#include "Factory.h"
#include "IActuator.h"

#include <iostream>
#include <cstring>

int main(int argc, char* argv[])
{
	std::cout << "Booting Application\n";

	std::cout << "version: " << FRAMEWORK_VERSION << '\n';
	std::cout << "compiled: " << FRAMEWORK_COMPILE_DATE << " " << FRAMEWORK_COMPILE_TIME << '\n';

	Framework *framework = new Framework( argc, argv );

	/*
	Factory& factory = Singleton< Factory >::Instance();
    	auto ab = factory.Create< IActuator >( "Actuator", "pca9685" );

	if( ab )
		std::cout << "[Succes]\n";
	else
		std::cout << "[Failed]\n";

	std::cout << "Shutdown Application\n";
	*/

   	return 0;
}
