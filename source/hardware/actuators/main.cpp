// Framework
#include "Framework.h"

// Inheritance
#include "Actuator.h"

// Interfaces
#include "IActuator.h"

// Design Patterns
#include "AbstractFactory.h"
#include "Observer.h"
#include "Singleton.h"
#include "StateMachine.h"

// Third-Party
#include <spdlog/spdlog.h>
#include "spdlog/cfg/env.h"

// Stl-Headers
#include <signal.h>
#include <unistd.h>

void abort( int s )
{
        spdlog::info( "Terminate" );
        StateMachine::dispatch( eTerminate() );
}

int main( int argc, char* argv[] )
{
        spdlog::cfg::load_env_levels();

        spdlog::info( "Booting Application" );

        // Link Callbacks
        spdlog::trace( "Link Signals" );
        signal( SIGINT, abort );
        signal( SIGTERM, abort );

        // Declare Framework
	Framework* fw = new Framework( argc, argv );

        // Retrieve Factory
        auto factory = Singleton<Factories>::Instance();

        // Retrieve Actuator Client
        auto actuator = factory.Construct<IActuator>( "Actuator", "actuator" );

        // Start State Machine
        StateMachine::Accept( *actuator );

        while ( StateMachine::IsRunning() )
        {
                StateMachine::dispatch( eCycle() );
                usleep( 50000 );
        }

        spdlog::info( "Shutdown Application" );

        return 0;
}
