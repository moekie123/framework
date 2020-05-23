#pragma once

#include "Subject.h"

class Subject;

class Observer:
	virtual public Object
{
public:

	Observer();

	virtual bool Update( const Subject& );

private:
	/* Required to suppress the "no-virtual-move-assign"-Compiler Warning */
	Observer& operator=( Observer&& other) 
	{
        	return *this;
    	}

};
