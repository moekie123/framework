#pragma once

// Inheritance, Design Patterns
#include "Object.h"

// Forward Declaration
class Generic;

/**
 * @brief The (Base) Observer class
 * @details Combined with the Subject class this implements the Observer-Pattern
 */
class Observer : virtual public Object
{
       public:
        /**
	 * @brief The default constructor
 	 */
        Observer();

        /**
	 * @brief The callback for a Subject to notify when a Object has been modified
	 * @param _subject The instance that invokes this method
	 */
        virtual bool Update( const Generic& _subject );

       private:
        /** 
	 * @brief Required to suppress the "no-virtual-move-assign"-Compiler Warning 
         */
        Observer& operator=( Observer&& other )
        {
                return *this;
        }
};

/* This file is already included through Generic.h */
#include "Generic.h"
