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
        void attach ( Observer<T> &_observer )
        {
            m_observers.push_back( &_observer );
        }
    
	/**
	 * @brief The trigger to update all subcribed Observers
	 */
        template< class U = T >
        void notify ()
        {
            for ( auto it = m_observers.begin(); it != m_observers.end(); it++ ) 
            {
                ( *it )->update( static_cast<U *>(this) );
            }
        }

   private:
      std::vector<Observer<T> *> m_observers;
};
