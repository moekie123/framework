#pragma once

#include "Object.h"
#include "Observer.h"
#include <vector>

class Observer;

class Subject:
	virtual public Object
{
public:
	Subject();

	bool Attach( Observer& obs );
	bool Notify();

protected:
	std::vector< Observer* > mObservers;

private:
	/* Required to suppress the "no-virtual-move-assign"-Compiler Warning */
	Subject& operator=( Subject&& other) 
	{
        	return *this;
    	}

};


