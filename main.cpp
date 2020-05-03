#include "Framework.h"
#include "version.h"

#include <iostream>
#include <cstring>

#include <mosquitto.h>


int main(int argc, char* argv[])
{
	std::cout << "Booting Application\n";

	std::cout << "version: " << FRAMEWORK_VERSION << '\n';
	std::cout << "compiled: " << FRAMEWORK_COMPILE_DATE << " " << FRAMEWORK_COMPILE_TIME << '\n';

	Framework *framework = new Framework( argc, argv );

	std::cout << "Shutdown Application\n";

   	return 0;
}
