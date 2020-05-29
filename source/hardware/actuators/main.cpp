// Framework
#include "Framework.h"

// Inheritance
#include "Actuator.h"

// Interfaces
#include "IActuator.h"
#include "IMosquitto.h"

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
        StateMachines::dispatch( eTerminate() );
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

        // Configure the Mosquitto Client
        auto mosquitto = factory.Construct<IMosquitto>( "Mosquitto", "mosquitto" );
        auto actuator = factory.Construct<IActuator>( "Actuator", "actuator" );

        // Link Observers
        mosquitto->Attach( *actuator );

        // Link the vistiors
        MqttStateMachine::Accept( *mosquitto );
        ActuatorStateMachine::Accept( *actuator );

        // Loop through
        StateMachines::start();
        while ( ActuatorStateMachine::IsRunning() )
        {
                StateMachines::dispatch( eCycle() );
                usleep( 50000 );
        }

        spdlog::info( "Shutdown Application" );

        return 0;
}
