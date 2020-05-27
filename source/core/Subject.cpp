// Design Pattern
#include "Subject.h"

Subject::Subject()
{
}

bool Subject::Attach( Generic& _gen )
{
        spdlog::debug( "{} [{} -> {}]", __PRETTY_FUNCTION__, _gen.GetName(), mName );

        mObservers.push_back( &_gen );
        return false;
}

bool Subject::Notify()
{
        bool res = false;

        for ( auto o : mObservers )
        {
                res = o->Update( *mGeneric );

                // Observer returned failure
             	if ( !res ) break;
        }

        return res;
}
