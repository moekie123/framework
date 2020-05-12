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
/*
	mosquitto_lib_init();

	{
		int x,y,z;
		mosquitto_lib_version( &x, &y, &z );
		std::cout << "mosquito version " << x << y << z << "\n";
	}
*/
}

bool Mosquitto::Connect( const std::string& _hostname, const std::string& _port)
{
/*
	int ret;
	std::cout << "Mosquitto::Client\n";

	std::cout << "Create new client\n";
	mClient = mosquitto_new( NULL, true, nullptr );
	if( !mClient )
	{
		std::cerr << "Failed to create client [" << mosquitto_strerror( errno ) << "]\n";
		return false;
	}

	std::cout << "Configure new client\n";
	ret = mosquitto_username_pw_set( mClient, mUsername.c_str(), mPassword.c_str() );
	if( ret != MOSQ_ERR_SUCCESS )
	{
		std::cerr << "Failed to set username and password [" << mosquitto_strerror( errno ) << "]\n";
		return false;
	}

	std::cout << "Connect new client\n";
	ret = mosquitto_connect( mClient, _hostname.c_str(), 1886, 60 );
	if( ret != MOSQ_ERR_SUCCESS )
	{
		std::cerr << "Failed to connect [" << mosquitto_strerror( errno ) << "]\n";
		return false;
	}
*/
	return true;
}

bool Mosquitto::Disconnect()
{
	return false;
}

Mosquitto::~Mosquitto()
{
	std::cout << "Cleanup Mosquitto Library\n";
/*
	mosquitto_lib_cleanup();
*/
}
