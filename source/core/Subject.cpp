// Design Pattern
#include "Subject.h"

Subject::Subject()
{
}

bool Subject::Attach( Observer& obs )
{
        mObservers.push_back( &obs );
        return false;
}

bool Subject::Notify()
{
        bool res = false;

        for ( auto o : mObservers )
        {
                res = o->Update( *this );

                // Observer returned failure
                if ( !res ) break;
        }

        return res;
}
