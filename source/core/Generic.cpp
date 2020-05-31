// Inheritance
#include "Generic.h"

// Third-Party
#include <rapidjson/document.h>

Generic::Generic()
{
        mGeneric = this;
}

bool Generic::Update( const IMosquitto& _mqtt, const rapidjson::Document& _jpackage )
{
        spdlog::debug( "Mosquito Observer Package Received" );
        return true;
}

bool Generic::Update( const Generic& _gen )
{
        return Observer::Update( _gen );
}
