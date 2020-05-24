
// Framework
#include "Framework.h"

// Stl-Headers
#include <iostream>

int main(int argc, char* argv[])
{
	std::cout << "Booting Application\n";
	
	Framework *f = new Framework( argc, argv );

	std::cout << "Shutdown Application\n";

   	return 0;
}
