// Design Pattern
#include "Observer.h"

Observer::Observer()
{
}

bool Observer::Update( const Generic& )
{
        spdlog::debug( "{}", __PRETTY_FUNCTION__ );
        return true;
}
