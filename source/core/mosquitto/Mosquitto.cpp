#include "Mosquitto.h"

#include <iostream>
#include <mosquitto.h>

#include "IConfigurator.h"

Mosquitto::MosquittoBuilder Mosquitto::builder;

Mosquitto::Mosquitto()
{
	std::cout << "Construct Mosquitto\n";
}

Mosquitto::Mosquitto( const IConfigurator& _config )
{
	std::cout << "Construct Mosquitto\n";
	
	_config.GetProperty( "mosquitto", "hostname", mHostname );
	_config.GetProperty( "mosquitto", "port"    , mPort );
	_config.GetProperty( "mosquitto", "username", mUsername );
	_config.GetProperty( "mosquitto", "password", mPassword );

	std::cout << "Mosquitto Client Configured [" << mHostname << ":" << mPort << "][" << mUsername << ":" <<  mPassword << "]\n";
	
	std::cout << "Initialize Mosquitto Library";
}

Mosquitto::~Mosquitto()
{
	std::cout << "Cleanup Mosquitto Library\n";
}

bool Mosquitto::visitInitialize( const MqttStateMachine& )
{
	std::cout << "[Visit] Initialized\n";
	return true;
}

bool Mosquitto::visitConfigure( const MqttStateMachine& )
{
	std::cout << "[Visit] Configure\n";
	return true;
}

bool Mosquitto::visitConnect( const MqttStateMachine& )
{
	std::cout << "[Visit] Connect\n";
	return true;
}

bool Mosquitto::visitReconnect( const MqttStateMachine& )
{
	std::cout << "[Visit] Reconnect\n";
	return true;
}

bool Mosquitto::visitDisconnect( const MqttStateMachine& )
{
	std::cout << "[Visit] Disconnect\n";
	return true;
}

bool Mosquitto::visitDestroy( const MqttStateMachine& )
{
	std::cout << "[Visit] Destroy\n";
	return true;
}

bool Mosquitto::visitCleanup( const MqttStateMachine& )
{
	std::cout << "[Visit] Cleanup\n";
	return true;
}

