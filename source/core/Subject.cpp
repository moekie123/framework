#include "Subject.h"

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
	for( auto o: mObservers )
		o->Update( *this );

	return false;
}


