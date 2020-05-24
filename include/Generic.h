#pragma once

#include "Object.h"
#include "Composite.h"
#include "Subject.h"
#include "Observer.h"

/**
 * @brief The (Base) Generic class combines all fundamental design patterns as one object
 */
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
