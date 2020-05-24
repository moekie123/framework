#pragma once

#include "Subject.h"

// Forward Declaration
class Subject;

/**
 * @brief The (Base) Observer class
 * @details Combined with the Subject class this implements the Observer-Pattern
 */
class Observer:
	virtual public Object
{
public:
	/**
	 * @brief The default constructor
 	 */
	Observer();

	/**
	 * @brief The callback for a Subject to notify when a Object has been modified
	 */
	virtual bool Update( const Subject& );

private:
	/* Required to suppress the "no-virtual-move-assign"-Compiler Warning */
	Observer& operator=( Observer&& other) 
	{
        	return *this;
    	}

};
