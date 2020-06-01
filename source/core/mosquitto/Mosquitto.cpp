// Inheritance
#include "Mosquitto.h"

// Interfaces
#include "IConfigurator.h"

// Design Patterns
#include "Factory.h"

// Third-Party
#include <mosquitto.h>
#include <rapidjson/document.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/writer.h>
#include <spdlog/spdlog.h>

// Stl-Headers
#include <queue>
#include <string>
#include <utility>

Mosquitto::MosquittoBuilder Mosquitto::builder;

std::queue<std::pair<std::string, std::string>> payloads;

/* Callback */
/*
	0 - success
	1 - connection refused (unacceptable protocol version)
	2 - connection refused (identifier rejected)
	3 - connection refused (broker unavailable)
	4-255 - reserved for future use
*/
void connect_callback( struct mosquitto* mosq, void* obj, int result )
{
        spdlog::debug( "Connect [{}]", result );

        switch ( result )
        {
                case 0:
                        break;
                case 1:
                case 2:
                case 3:
                default:
                        MqttStateMachine::dispatch( eTerminate() );
        }
}

/* Callback */
void message_callback( struct mosquitto* mosq, void* obj, const struct mosquitto_message* message )
{
        // Process the message under controll of the statemachine
        char* buffer = new char[message->payloadlen + 1];
        sprintf( buffer, (char*)message->payload );

        spdlog::trace( "Received message" );

        payloads.push( std::make_pair( std::string( message->topic ), std::string( buffer ) ) );

        delete[] buffer;
}

Mosquitto::Mosquitto() : mHostname( "localhost" ), mPort( 1883 ), mUsername( "rsalm" ), mPassword( "rsalm" )
{
        spdlog::debug( "{}", __PRETTY_FUNCTION__ );
        SetName( "Mosquitto" );
        mClient = nullptr;
}

Mosquitto::Mosquitto( const IConfigurator& _config )
{
        spdlog::debug( "{}", __PRETTY_FUNCTION__ );
        SetName( "Mosquitto" );

        _config.GetProperty( "Mosquitto", "client", "hostname", mHostname );
        _config.GetProperty( "Mosquitto", "client", "username", mUsername );
        _config.GetProperty( "Mosquitto", "client", "password", mPassword );
        _config.GetProperty( "Mosquitto", "client", "port", mPort );

        mClient = nullptr;
}

Mosquitto::~Mosquitto()
{
        spdlog::debug( __PRETTY_FUNCTION__ );
}

bool Mosquitto::visitInitialize( const MqttStateMachine& )
{
        spdlog::info( "[Visit] Initialize" );

        // Clean Memory if not free (yet)
        if ( mClient )
                free( mClient );

        // Initialize Library
        spdlog::debug( "Initialize Mosquitto Library" );
        mosquitto_lib_init();

        // Print Version number
        {
                int x, y, z;
                mosquitto_lib_version( &x, &y, &z );
                spdlog::debug( "Mosquitto Verions {}.{}.{}", x, y, z );
        }

        // Construct Client
        spdlog::debug( "Create new client" );

        mClient = mosquitto_new( NULL, true, nullptr );
        if ( !mClient )
        {
                spdlog::error( "Failed to create client [{}]", mosquitto_strerror( errno ) );
                return false;
        }

        return true;
}

bool Mosquitto::visitPreConfigure( const MqttStateMachine& )
{
        int ret;
        spdlog::info( "[Visit] PreConfigure username [{}] password [{}]", mUsername, mPassword );

        ret = mosquitto_username_pw_set( mClient, mUsername.c_str(), mPassword.c_str() );
        if ( ret != MOSQ_ERR_SUCCESS )
        {
                spdlog::error( "Failed to set username and password [{}]", mosquitto_strerror( errno ) );
                return false;
        }

        spdlog::debug( "Link callbacks" );
        mosquitto_connect_callback_set( mClient, connect_callback );
        mosquitto_message_callback_set( mClient, message_callback );

        return true;
}

bool Mosquitto::visitConnect( const MqttStateMachine& )
{
        int ret;
        spdlog::info( "[Visit] Connect to [{}][{}]", mHostname.c_str(), mPort );

        ret = mosquitto_connect( mClient, mHostname.c_str(), mPort, 60 );

        if ( ret != MOSQ_ERR_SUCCESS )
        {
                spdlog::error( "Failed to connect [{}]", mosquitto_strerror( errno ) );
                return false;
        }

        for ( auto it = mObservers.begin(); it != mObservers.end(); it++ )
        {
                /* All should pass, return false immedially when one fails */
                std::string name = ( *it )->GetName();

                spdlog::info( "Subscribe [{}]", name );

                ret = mosquitto_subscribe( mClient, NULL, name.c_str(), 0 );
                if ( ret != MOSQ_ERR_SUCCESS )
                {
                        spdlog::error( "Failed to subscribe [{}]", mosquitto_strerror( errno ) );
                        // TODO, This results in immedially destroy, but first a gental disconnect needs to be done actually
                        return false;
                }
        }

        return true;
}

bool Mosquitto::visitPostConfigure( const MqttStateMachine& )
{
        spdlog::info( "[Visit] PostConfigure" );
        return true;
}

bool Mosquitto::visitLoop( const MqttStateMachine& )
{
        int ret;
        bool match = false;

        // Execute Loop
        ret = mosquitto_loop( mClient, -1, 1 );
        if ( ret != MOSQ_ERR_SUCCESS )
        {
                spdlog::error( "General failure in loop [{}]", mosquitto_strerror( errno ) );
                return false;
        }

        if ( !payloads.empty() )
        {
                // Get the first element from the queue
                auto message = payloads.front();

                // Convert payload to json document
                rapidjson::Document jpackage;
                jpackage.Parse( message.second.c_str() );

                if ( !jpackage.IsObject() )
                {
                        spdlog::warn( "Invalid Payload [{}]", message.second );
                        return false;
                }

                for ( auto it = mObservers.begin(); it != mObservers.end(); it++ )
                {
                        ret = mosquitto_topic_matches_sub( ( *it )->GetName().c_str(), message.first.c_str(), &match );
                        if ( ret != MOSQ_ERR_SUCCESS )
                        {
                                spdlog::error( "Failed matching topic [{}]", mosquitto_strerror( errno ) );
                        }
                        else if ( match )
                        {
                                spdlog::info( "[{}][{}]", message.first, message.second );

                                // Package should be lexed on invalid charaters
                                // Package should be converted to RadidJson
                                ( *it )->Update( *this, jpackage );
                        }
                }

                // Remove the message from the queue when all observers have been notified
                payloads.pop();
        }
        return true;
}

bool Mosquitto::visitReconnect( const MqttStateMachine& )
{
        spdlog::info( "[Visit] Reconnect" );
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
        spdlog::info( "[Visit] Disconnect from [{}][{}]", mHostname, mPort );

        // Check if client is already empty
        if ( !mClient )
                return true;

        // Disconnect client
        ret = mosquitto_disconnect( mClient );
        if ( ret != MOSQ_ERR_SUCCESS )
        {
                spdlog::error( "Failed to disconnect [{}]", mosquitto_strerror( errno ) );
                return false;
        }

        return true;
}

bool Mosquitto::visitDestroy( const MqttStateMachine& )
{
        spdlog::info( "[Visit] Destroy" );

        // Check if client is already empty
        if ( !mClient )
                return true;

        // Destroy the client
        mosquitto_destroy( mClient );

        if ( !mClient )
        {
                spdlog::error( "Failed to destroy client" );
                // Client should be destroy and free by now... So delete it manually
                free( mClient );
                return false;
        }

        return true;
}

bool Mosquitto::visitCleanup( const MqttStateMachine& )
{
        spdlog::info( "[Visit] Cleanup" );

        // Clean up the Library
        mosquitto_lib_cleanup();

        return true;
}

bool Mosquitto::Update( const Generic& _gen )
{
        int ret;

        const std::string topic = _gen.GetName() + "/reply";
        spdlog::info( "Mosquitto Publish [{}]", topic.c_str() );

        const std::string& json = _gen.ToJson();

        ret = mosquitto_publish( mClient, NULL, topic.c_str(), strlen( json.c_str() ), json.c_str(), 0, false );
        if ( ret != MOSQ_ERR_SUCCESS )
        {
                spdlog::error( "Failed to Publish [{}][{}]", topic, mosquitto_strerror( errno ) );
                return false;
        }
        return true;
}
