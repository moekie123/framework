#pragma once

#include "Observer.h"

#include <vector>
#include <iterator>

template <class T>
class Subject
{
   public:
        Subject() {}
        virtual ~Subject() {}

        void attach ( Observer<T> &observer )
        {
            m_observers.push_back( &observer );
        }
    
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
