#include "Mosquitto.h"

#include <iostream>
#include <cstring>
#include <queue>
#include <utility>  

#include <mosquitto.h>

#include "Factory.h"
#include "IConfigurator.h"

Mosquitto::MosquittoBuilder Mosquitto::builder;

std::queue< std::pair< std::string, std::string >> payloads;

/* Callback */
/*
	0 - success
	1 - connection refused (unacceptable protocol version)
	2 - connection refused (identifier rejected)
	3 - connection refused (broker unavailable)
	4-255 - reserved for future use
*/
void connect_callback(struct mosquitto *mosq, void *obj, int result)
{
	std::cout << "connect callback [" << result << "]\n";
	
	switch( result )
	{
		case 0:
			std::cout << "Succes\n";
			break;
		case 1: 
		case 2:
		case 3:
		default:
			std::cout << "Terminate\n";
			MqttStateMachine::dispatch( eTerminate() );
	}
}

/* Callback */
void message_callback(struct mosquitto *mosq, void *obj, const struct mosquitto_message *message)
{
	// Process the message under controll of the statemachine
	char* buffer = new char[ message->payloadlen + 1];
	sprintf (buffer, (char *) message->payload );
	
	std::cout << " Received Message \n";
	
	payloads.push( std::make_pair( std::string( message->topic ), std::string( buffer )));

	delete[] buffer;
}


Mosquitto::Mosquitto():
	mHostname( "localhost" ),mPort( 1883 ),
	mUsername( "rsalm" ),mPassword( "rsalm" )
{
	std::cout << "[DEFAULT] Construct Mosquitto\n";

	mClient = nullptr;	
}

Mosquitto::Mosquitto( const IConfigurator& _config, const std::string& _hostname, const int& _port, const std::string& _username, const std::string& _password):
	mHostname( _hostname ), 
	mPort( _port ), 
	mUsername( _username ), 
	mPassword( _password )
{
	std::cout << "Construct Configured Mosquitto\n";
		
	mClient = nullptr;	
}

Mosquitto::~Mosquitto()
{
	std::cout << "Cleanup Mosquitto Library\n";
}

bool Mosquitto::visitInitialize( const MqttStateMachine& )
{
	std::cout << "[Visit] Initialized\n";

	// Clean Memory if not free (yet)
	if( mClient )
		free( mClient );

	// Initialize Library
 	std::cout << "Initialize Mosquitto Library\n";
	mosquitto_lib_init();

	// Print Version number
	{
		int x,y,z;
		mosquitto_lib_version( &x, &y, &z );
		std::cout << "mosquito version " << x << y << z << "\n";
	}

	// Construct Client
 	std::cout << "Create new client\n";
	mClient = mosquitto_new( NULL, true, nullptr );
	if( !mClient )
	{
		std::cerr << "Failed to create client [" << mosquitto_strerror( errno ) << "]\n";
		return false;
	}
	
	return true;
}

bool Mosquitto::visitConfigure( const MqttStateMachine& )
{
	int ret;
	std::cout << "[Visit] Configure username [" << mUsername << "] password [" << mPassword << "]\n";
	
	ret = mosquitto_username_pw_set( mClient, mUsername.c_str(), mPassword.c_str() );
	if( ret != MOSQ_ERR_SUCCESS )
	{
		std::cerr << "Failed to set username and password [" << mosquitto_strerror( errno ) << "]\n";
		return false;
	}

	std::cout << "Link callbacks\n";
	mosquitto_connect_callback_set( mClient, connect_callback );
	mosquitto_message_callback_set( mClient, message_callback );
	
	return true;
}

bool Mosquitto::visitConnect( const MqttStateMachine& )
{
	int ret;
	std::cout << "[Visit] Connect to [" << mHostname.c_str() << "][" << mPort << "]\n";

	ret = mosquitto_connect( mClient, mHostname.c_str(), mPort, 60 );

	if( ret != MOSQ_ERR_SUCCESS )
	{
		std::cerr << "Failed to connect [" << mosquitto_strerror( errno ) << "]\n";
		return false;
	}

	for ( auto it = mObservers.begin(); it != mObservers.end(); it++ ) 
	{
		/* All should pass, return false immedially when one fails */
	   	auto param = dynamic_cast< IParameter* >( *it );
		std::string name = param->GetName();

		std::cout << "Subscribe [" << name << "]\n";	
	
		ret = mosquitto_subscribe( mClient, NULL, name.c_str(), 0);
		if( ret != MOSQ_ERR_SUCCESS )
		{
			std::cerr << "Failed to subscribe [" << mosquitto_strerror( errno ) << "]\n";
			// TODO, This results in immedially destroy, but first a gental disconnect needs to be done actually
			return false;
		}
	}

	return true;
}

bool Mosquitto::visitLoop( const MqttStateMachine& )
{
	int ret;
	bool match = false;

	// Execute Loop
	ret = mosquitto_loop( mClient , -1, 1 );
	if( ret != MOSQ_ERR_SUCCESS )
	{
		std::cerr << "General failure in loop [" << mosquitto_strerror( errno ) << "]\n";
		return false;
	}


	if( !payloads.empty() )
	{
		// Get the first element from the queue
		auto message = payloads.front();

		for ( auto it = mObservers.begin(); it != mObservers.end(); it++ ) 
		{
			/* 
  			 * Convert the iterator, which is stored in a vector a Observer*, back to a parameter
			 */
			auto parameter = dynamic_cast< IParameter* >(( *it ));

			ret = mosquitto_topic_matches_sub( parameter->GetName().c_str(), message.first.c_str(), &match );
	
			if( ret != MOSQ_ERR_SUCCESS )
			{
				std::cerr << "Failed match topic [" << mosquitto_strerror( errno ) << "]\n";
			}
			else if ( match ) 
			{
				std::cout << "[" << message.first << "] " << message.second << "\n";
				
				/* 
				 * Extract the (parent) Mosquitto Observer from the IParameter
				 *    Take the Observer ( defined as IParamater ) on the right side
        			 *    Cast this up to extract only the IMosquitto Observer ( left )	
				 *    TODO, Find out what will happen when multiple observer types are allowed....
				 */
				Observer< IMosquitto >* param = dynamic_cast< IParameter* >( parameter );

				// This will avoid ambgious Update calls since there are multiple observers in IParameter.
				param->Update( this );
			}
		}

		// Remove the message from the queue when all observers have been notified
		payloads.pop();

	}
	return true;
}

bool Mosquitto::visitReconnect( const MqttStateMachine& )
{
	std::cout << "[Visit] Reconnect\n";
/*
			ret = mosquitto_reconnect( client );

			if( run && ret != MOSQ_ERR_SUCCESS )
			{
				std::cerr << "Failed to reconnect [" << mosquitto_strerror( errno ) << "]\n";
				continue;
			}

			std::cout << "Reconnected to [" << hostname << "][" << port << "]\n";
*/
	return true;
}

bool Mosquitto::visitDisconnect( const MqttStateMachine& )
{
	int ret;
	std::cout << "[Visit] Disconnect from [" << mHostname << "][" << mPort << "]\n";

	// Check if client is already empty	
	if( !mClient )
		return true;

	// Disconnect client
	ret = mosquitto_disconnect( mClient );
	if( ret != MOSQ_ERR_SUCCESS )
	{
		std::cerr << "Failed to disconnect [" << mosquitto_strerror( errno ) << "]\n";
		return false;
	}

	return true;
}

bool Mosquitto::visitDestroy( const MqttStateMachine& )
{
	std::cout << "[Visit] Destroy\n";
	
	// Check if client is already empty
	if( !mClient )
		return true;

	// Destroy the client
	mosquitto_destroy( mClient );

	if ( !mClient )
	{
		std::cerr << "Failed to destroy client\n";
		// Client should be destroy and free by now... So delete it manually
		free( mClient );
		return false;
	}

	return true;
}

bool Mosquitto::visitCleanup( const MqttStateMachine& )
{
	std::cout << "[Visit] Cleanup\n";

	// Clean up the Library
	mosquitto_lib_cleanup();	
	
	return true;
}

