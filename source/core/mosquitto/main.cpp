// Framework
#include "Framework.h"

// Inheritance
#include "../configurator/Configurator.h"
#include "Mosquitto.h"

// Interfaces
#include "IMosquitto.h"
#include "IParameter.h"

// Design Patterns
#include "Observer.h"
#include "AbstractFactory.h"
#include "StateMachine.h"
#include "Singleton.h"

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

        // Retrieve Mosquitto Client
        auto mosquitto = factory.Construct<IMosquitto>( "Mosquitto", "mosquitto" );

        // Retrieve Parameter
        auto parameter = factory.Construct<IParameter>( "Parameter", "dummy" );

        // Start State Machine
        mosquitto->Attach( *parameter );
        StateMachine::Accept( *mosquitto );

        while ( StateMachine::IsRunning() )
        {
                StateMachine::dispatch( eCycle() );
                usleep( 50000 );
        }

        spdlog::info( "Shutdown Application" );

        return 0;
}
