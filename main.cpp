#include "Framework.h"
#include <iostream>

int main( int argc, char *argv[] )
{
	std::cout << "Booting Application\n";

	Framework *framework = new Framework( argc, argv );

	std::cout << "Shutdown Application\n";
}