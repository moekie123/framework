#include <cstring>

#include <iostream> // printing

#include <signal.h> // Catch Interupts
#include <unistd.h> // Sleep 

#include <cerrno> // catch error returns

#include <mosquitto.h>

const std::string username = "rsalm";
const std::string password = "rsalm";

const std::string hostname = "localhost";
const int port = 1883;

const std::string topic = "#";

static bool run = false;
static bool connected = false;

void abort(int s)
{
	std::cout << "Abort Mosquitto Prototype\n";
	run = false;
}

void connect_callback(struct mosquitto *mosq, void *obj, int result)
{
	std::cout << "connect callback [" << result << "]"; 
}

void message_callback(struct mosquitto *mosq, void *obj, const struct mosquitto_message *message)
{
	int ret;
	bool match = 0;

	ret = mosquitto_topic_matches_sub( topic.c_str(), message->topic, &match );
	if( ret != MOSQ_ERR_SUCCESS )
	{
		std::cerr << "Failed match topic [" << mosquitto_strerror( errno ) << "]\n";
	}
	else if ( match ) 
	{
		char* buffer = new char[ message->payloadlen + 1];

		sprintf (buffer, (char *) message->payload );
		std::cout << "[" << message->topic << "] " << buffer << "\n";

		delete[] buffer;
	}
}

int main(int argc, char* argv[])
{
	int ret;
	std::cout << "Booting (Prototype) Mosquitto Implemenation\n";

	signal(SIGINT, abort);
	signal(SIGTERM, abort);

	std::cout << "Initialize Mosquitto Library";
	mosquitto_lib_init();

	{
		int x,y,z;
		mosquitto_lib_version( &x, &y, &z );
		std::cout << "mosquito version " << x << y << z << "\n";
	}

	std::cout << "Create new client\n";
	auto client = mosquitto_new( NULL, true, nullptr );
	if( !client )
	{
		std::cerr << "Failed to create client [" << mosquitto_strerror( errno ) << "]\n";
		goto cleanup;
	}

	std::cout << "Configure username [" << username << "] password [" << password << "]\n";
	ret = mosquitto_username_pw_set( client, username.c_str(), password.c_str() );
	if( ret != MOSQ_ERR_SUCCESS )
	{
		std::cerr << "Failed to set username and password [" << mosquitto_strerror( errno ) << "]\n";
		goto destroy;
	}

	std::cout << "Link callbacks\n";
	mosquitto_connect_callback_set( client, connect_callback );
	mosquitto_message_callback_set( client, message_callback );

	std::cout << "Connect to [" << hostname << "][" << port << "]\n";
	ret = mosquitto_connect( client, hostname.c_str(), port, 60 );
	if( ret != MOSQ_ERR_SUCCESS )
	{
		std::cerr << "Failed to connect [" << mosquitto_strerror( errno ) << "]\n";
		goto destroy;
	}
	connected = true;

	ret = mosquitto_subscribe( client, NULL, topic.c_str(), 0);
	if( ret != MOSQ_ERR_SUCCESS )
	{
		std::cerr << "Failed to subscribe [" << mosquitto_strerror( errno ) << "]\n";
		goto disconnect;
	}

	run = true;
	while( run )
	{
		// Check if client is still connceted 
		if( run && !connected )
		{
			sleep(5);
			ret = mosquitto_reconnect( client );

			if( run && ret != MOSQ_ERR_SUCCESS )
			{
				std::cerr << "Failed to reconnect [" << mosquitto_strerror( errno ) << "]\n";
				continue;
			}

			std::cout << "Reconnected to [" << hostname << "][" << port << "]\n";
			connected = true;
		}

		// Execute Loop
		ret = mosquitto_loop( client , -1, 1);
		if( run && ret != MOSQ_ERR_SUCCESS )
		{
			std::cerr << "General failure in loop [" << mosquitto_strerror( errno ) << "]\n";
			connected = false;
		}
	}
	std::cout << "Stopping Prototype\n";

disconnect:
	std::cout << "Disconnect from [" << hostname << "][" << port << "]\n";
	ret = mosquitto_disconnect( client );
	if( ret != MOSQ_ERR_SUCCESS )
	{
		std::cerr << "Failed to disconnect [" << mosquitto_strerror( errno ) << "]\n";
	}

destroy:	
	mosquitto_destroy( client );
	if ( !client )
	{
		std::cerr << "Failed to destroy client\n";
	}

cleanup:
	std::cout << "Cleanup Mosquitto Library\n";
	mosquitto_lib_cleanup();	
	
	std::cout << "Shutdown Application\n";

   	return 0;
}
