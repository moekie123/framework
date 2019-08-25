#pragma once

#include "Observer.h"

#include <vector>
#include <iterator>

/**
 * @brief The generic behavorial design patterns Observer-Subject
 * @details This class should be used in combinaation with the Observer
 */
template <class T>
class Subject
{
   public:
        Subject() {}
        virtual ~Subject() {}

	/**
	 * @brief Observers can subscribe to the subject through this method
	 * @param _observer The observer that needs the get notified
	 */
        void Attach ( Observer<T> &_observer )
        {
            mObservers.push_back( &_observer );
        }
    
	/**
	 * @brief The trigger to update all subcribed Observers
	 * @details 	All observers should return True on their update... 
	 * 		Abort 'Notify' when the first observer return False.
	 */
        template< class U = T >
        bool Notify ()
        {
            for ( auto it = mObservers.begin(); it != mObservers.end(); it++ ) 
            {
		/* All should pass, return false immedially when one fails */
		if( (*it)->Update( static_cast<U *>( this )) == false )
			return false;
            }

	    return true;
        }

   private:
      std::vector<Observer<T> *> mObservers;
};
