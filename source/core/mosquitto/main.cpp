#include <iostream>
#include <signal.h>

#include "Mosquitto.h"
#include "StateMachine.h"

void abort(int s)
{
	std::cout << "Terminate\n";
	MqttStateMachine::dispatch( MqttEventTerminate() );
}


int main(int argc, char* argv[])
{
	std::cout << "Booting Application\n";

	signal(SIGINT, abort);
	signal(SIGTERM, abort);

	Mosquitto mosquitto;
	MqttStateMachine::Accept( mosquitto );

	std::cout << "Shutdown Application\n";

   	return 0;
}
