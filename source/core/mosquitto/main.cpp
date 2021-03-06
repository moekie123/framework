#include <iostream>
#include <signal.h>

#include <unistd.h>

#include "Observer.h"

#include "IMosquitto.h"
#include "Mosquitto.h"
#include "StateMachine.h"

#include "../configurator/Configurator.h"
#include "IParameter.h"

void abort(int s)
{
	std::cout << "Terminate\n";
	StateMachine::dispatch( eTerminate() );
}

class Dummy: public IParameter
{
	public:
	Dummy()
	{
		SetName( "#" );
	}

        /* Observer methods **/
        bool Update( const IMosquitto* subject )
	{
		std::cout << "Dummy Update\n";
		return true;
	}
};


int main(int argc, char* argv[])
{
	std::cout << "Booting Application\n";

	// Link Callbacks
	signal(SIGINT, abort);
	signal(SIGTERM, abort);

	Configurator::mConfigFileName = "mosquitto.xml";

	// Open Configuration File
	Configurator* configurator = new Configurator();

	// Build Mosquitto Instance
	std::string* hostname = new std::string();
	configurator->GetProperty( "mosquitto", "hostname", (std::string&) *hostname );

	std::string* username = new std::string();
	configurator->GetProperty( "mosquitto", "username", (std::string&) *username );

	std::string* password = new std::string();
	configurator->GetProperty( "mosquitto", "password", (std::string&) *password );

	int* port = new int();
	configurator->GetProperty( "mosquitto", "port", (int&) *port );

	Mosquitto mosquitto( *configurator, *hostname, *port, *username, *password );
	IParameter *param = new Dummy();

	// Start State Machine
	mosquitto.Attach( *param );
	StateMachine::Accept( mosquitto );
	
	while( StateMachine::IsRunning() )
	{
		StateMachine::dispatch( eCycle() );
		usleep( 50000 );
	}

	std::cout << "Shutdown Application\n";

   	return 0;
}
