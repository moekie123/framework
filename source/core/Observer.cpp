#include "Observer.h"

Observer::Observer()
{
	std::cout << "Observer: Construct\n";
}

bool Observer::Update( const Subject& )
{
	std::cout << "Observer: Update\n";
	return false;
}
