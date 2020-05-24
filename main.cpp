// Framework
#include "Framework.h"

// Third-Party
#include <spdlog/spdlog.h>

int main( int argc, char* argv[] )
{
        spdlog::info( "Booting Application" );

        Framework* f = new Framework( argc, argv );

        spdlog::info( "Terminate Application" );

        return 0;
}
