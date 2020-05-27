#pragma once

// Design Patterns
#include "Object.h"

// Stl-Headers
#include <vector>

// Forward Declaration
class Generic;

/**
 * @brief The (Base) Subject class
 * @details Combined with the Observer class this implements the Observer-Pattern
 */
class Subject : virtual public Object
{
       public:
        /**
	 * @brief The default constructor 
	 */
        Subject();

        /** 
	 * @brief The observer registrator
	 * @details With this method Observers can be added to an object.
	 * @param _gen The observer that should be notified
	 */
        bool Attach( Generic& _gen );

        /**
	 * @brief The notifier, for all observers
	 * @details This will run the callback "Update" of each Observer
	 */
        bool Notify();

       protected:
        /**
	 * @brief The vector of registerd Observers 
	 */
        std::vector<Generic*> mObservers;

       private:
        /** 
	 * @brief Required to suppress the "no-virtual-move-assign"-Compiler Warning 
	 */
        Subject& operator=( Subject&& _other )
        {
                return *this;
        }
};

/* This file is already included through Generic.h */
#include "Generic.h"
