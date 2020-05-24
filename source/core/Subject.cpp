// Design Pattern
#include "Subject.h"

// Stl-Headers
#include <iostream>

Subject::Subject()
{
	std::cout << "Subject: Construct\n";
}

bool Subject::Attach( Observer& obs )
{
	std::cout << "Subject: Attach\n";
	mObservers.push_back( & obs );
	return false;
}

bool Subject::Notify()
{
	bool res = false;

	for( auto o: mObservers )
	{
		res = o->Update( *this );
		
		// Observer returned failure
		if( !res ) break;
	}

	return res;
}
