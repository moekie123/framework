#pragma once

#include "Object.h"
#include "Composite.h"
#include "Subject.h"
#include "Observer.h"

class Generic:
	virtual public Object,
	public Composite,
	public Observer,
	public Subject
{
public:

private:
	/* Required to suppress the "no-virtual-move-assign"-Compiler Warning */
	Generic& operator=( Generic&& other) 
	{
        	return *this;
    	}

};


