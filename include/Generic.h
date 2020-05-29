#pragma once

// Design Patterns
#include "Object.h"
#include "Observer.h"
#include "Subject.h"
#include "Composite.h"

/**
 * @brief The (Base) Generic class combines all fundamental design patterns as one object
 */
class Generic : virtual public Object,
                public Composite,
                public Observer,
                public Subject
{
       	public:
         Generic();

         virtual ~Generic() = default;

        private:
        /** 
	 * @brief Required to suppress the "no-virtual-move-assign"-Compiler Warning 
	 */
        Generic& operator=( Generic&& _other )
        {
                return *this;
        }
};


