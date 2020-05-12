#include <iostream>

#include "Mosquitto.h"
#include "MqttStateMachine.h"

#include <unistd.h>

FSM_INITIAL_STATE( MqttStateMachine , MqttStateIdle )

int main(int argc, char* argv[])
{
	std::cout << "Booting Application\n";
	
	MqttStateMachine::start();

	for( int index = 0; index < 4; index++ )
	{
		auto current_state = MqttStateMachine::current_state_ptr;
		current_state->cycle();
		
		switch( index )
		{
			case 0:
				MqttStateMachine::dispatch( MqttEventInitialize() );
				break;
			case 1:		
				MqttStateMachine::dispatch( MqttEventInitialized() );
				break;
			case 2:
				MqttStateMachine::dispatch( MqttEventTerminate() );
				break;
			case 3:		
				MqttStateMachine::dispatch( MqttEventTerminated() );
				break;
		}
		sleep(1);
	}

	std::cout << "Shutdown Application\n";

   	return 0;
}
