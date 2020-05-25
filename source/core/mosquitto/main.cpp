// Inheritance
#include "Mosquitto.h"
#include "../configurator/Configurator.h"

// Interfaces
#include "IMosquitto.h"
#include "IParameter.h"

// Design Patterns
#include "Observer.h"
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

class Dummy : public IParameter
{
       public:
        Dummy()
        {
                SetName( "#" );
        }

        /* Observer methods **/
        bool Update( const IMosquitto* subject )
        {
                return true;
        }
};

int main( int argc, char* argv[] )
{
        spdlog::cfg::load_env_levels();

        spdlog::info( "Booting Application" );

        // Link Callbacks
        signal( SIGINT, abort );
        signal( SIGTERM, abort );

        Configurator::mConfigFileName = "mosquitto.xml";

        // Open Configuration File
        Configurator* configurator = new Configurator();

        // Build Mosquitto Instance
        std::string* hostname = new std::string();
        configurator->GetProperty( "mosquitto", "hostname", (std::string&)*hostname );

        std::string* username = new std::string();
        configurator->GetProperty( "mosquitto", "username", (std::string&)*username );

        std::string* password = new std::string();
        configurator->GetProperty( "mosquitto", "password", (std::string&)*password );

        int* port = new int();
        configurator->GetProperty( "mosquitto", "port", (int&)*port );

        Mosquitto mosquitto( *configurator, *hostname, *port, *username, *password );
        IParameter* param = new Dummy();

        // Start State Machine
        mosquitto.Attach( *param );
        StateMachine::Accept( mosquitto );

        while ( StateMachine::IsRunning() )
        {
                StateMachine::dispatch( eCycle() );
                usleep( 50000 );
        }

        spdlog::info( "Shutdown Application" );

        return 0;
}
