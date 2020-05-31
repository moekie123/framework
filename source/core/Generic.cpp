#include "Generic.h"

Generic::Generic()
{
        mGeneric = this;
}

bool Generic::Update( const IMosquitto& _mqtt, const std::string& _package )
{
        spdlog::debug( "Mosquito Observer Package Received [{}]", _package );
        return true;
}

bool Generic::Update( const Generic& _gen )
{
        return Observer::Update( _gen );
}
