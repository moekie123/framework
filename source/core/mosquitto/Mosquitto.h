#pragma once

#include "Visitor.h"
#include "StateMachine.h"


#include "IMosquitto.h"
#include "IConfigurator.h"

#include "Singleton.h"
#include "Generic.h"
#include "Builder.h"
#include "Factory.h"

#include "StateMachine.h"

class Mosquitto:
	public IMosquitto,
	public MosquittoVisitor
{
	public:
	/**
	 * @brief The Mosquitto Builder class to build a new Mosquitto client
	 * @details It acctually retuns a Singleton
	 */
	class MosquittoBuilder:
		public Builder
	{
		public:
			Generic& Build( const std::string& _name ) override
			{
				if( !Singleton< Mosquitto >::IsConstructed() )
				{
					std::cout << "Construct Mosquitto Client on-the-fly\n";

					// Build Instance if not already done
					Factory& factory = Singleton< Factory >::Instance();
					IConfigurator& config = factory.Create< IConfigurator >( "Configurator", "configuration.xml" );
					
					std::string* hostname = new std::string();
					config.GetProperty( "mosquitto", "hostname", (std::string&) *hostname );
			
					std::string* username = new std::string();
					config.GetProperty( "mosquitto", "username", (std::string&) *username );

					std::string* password = new std::string();
					config.GetProperty( "mosquitto", "password", (std::string&) *password );

					int* port = new int();
					config.GetProperty( "mosquitto", "port", (int&) *port );

					Mosquitto* mosquitto = new Mosquitto( config, *hostname, *port, *username, *password );
					Singleton< Mosquitto >::Register( *mosquitto );
				}

				// Retrieve the client
				Mosquitto& mosquitto = Singleton< Mosquitto >::Instance();
				return mosquitto;
			}
	};

	/**
	 * @brief The constructor
	 */
	Mosquitto();

	/**
	 * @brief The desctructor
	 */
	~Mosquitto();

	/**
	 * @brief The constructor
	 */
	Mosquitto( const IConfigurator& _config, const std::string&, const int&, const std::string&, const std::string&);

	/**
	 * @brief The global ParameterBuilder
	 */
	static MosquittoBuilder builder;

	/** 
	 * Visitor Pattern Methods
	 */	
	bool visitInitialize( const MqttStateMachine& ) override;
	bool visitConfigure( const MqttStateMachine& ) override;
	bool visitConnect( const MqttStateMachine& ) override;
	bool visitLoop( const MqttStateMachine& ) override;
	bool visitReconnect( const MqttStateMachine& ) override;
	bool visitDisconnect( const MqttStateMachine& ) override;
	bool visitDestroy( const MqttStateMachine& ) override;
	bool visitCleanup( const MqttStateMachine& ) override;

	private:

	/**
	 * @brief The mosquitto client
	 */
	struct mosquitto* mClient;

	/**
	 * @brief The network addres of the mqtt broker
	 */
	const std::string& mHostname;

	/**
	 * @brief The network port of the mqtt broker
	 */
	const int& mPort;

	/**
	 * @brief The Username of the mqtt broker 
	 */
	const std::string& mUsername;

	/**
	 * @brief The Password of the mqtt broker
	 */
	const std::string& mPassword;
};
