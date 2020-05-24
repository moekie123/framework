#pragma once

// Inheritance
#include "Generic.h"

// Interfaces
#include "IMosquitto.h"
#include "IConfigurator.h"

// Design Patterns
#include "Visitor.h"
#include "StateMachine.h"

#include "Singleton.h"
#include "Builder.h"
#include "AbstractFactory.h"
#include "Factory.h"

/**
 * @brief (Wrapper Design Pattern) The Mosquitto Class
 * @details This class wraps around the libmosquitto library and functions can be called through the MosquittoVisitor
 */
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
		public Builder< IMosquitto >
	{
		public:

			/**
			 * @brief The build method that configures and constructs a new Parameter
			 * @param _config The pre build Configurator
			 * @param _name The name of the Mosquitto Broker (not used)
 			 */
			static IMosquitto* Build( const IConfigurator* _config, const std::string& _name )
			{
				std::cout << "Run Builder\n";
				if( !Singleton< Mosquitto >::IsConstructed() )
				{
					std::cout << "Construct Mosquitto Client on-the-fly\n";

					const std::string label = "Configurator";

					Factories& factory = Singleton< Factories >::Instance();
					IConfigurator* config = factory.Construct< IConfigurator >( label );

					std::string* hostname = new std::string();
					config->GetProperty( "mosquitto", "hostname", (std::string&) *hostname );
			
					std::string* username = new std::string();
					config->GetProperty( "mosquitto", "username", (std::string&) *username );

					std::string* password = new std::string();
					config->GetProperty( "mosquitto", "password", (std::string&) *password );

					int* port = new int();
					config->GetProperty( "mosquitto", "port", (int&) *port );

					Mosquitto* mosquitto = new Mosquitto( *config, *hostname, *port, *username, *password );
					Singleton< Mosquitto >::Register( *mosquitto );
				}

				// Retrieve the client
				Mosquitto& mosquitto = Singleton< Mosquitto >::Instance();
				return &mosquitto;
			}

			/**
		 	 * @brief The constructor will map the Build-Method to the (base) Builder class
			 */
			MosquittoBuilder(): Builder( MosquittoBuilder::Build )
			{
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
	bool visitInitialize( const StateMachine& ) override;
	bool visitConfigure( const StateMachine& ) override;
	bool visitConnect( const StateMachine& ) override;
	bool visitLoop( const StateMachine& ) override;
	bool visitReconnect( const StateMachine& ) override;
	bool visitDisconnect( const StateMachine& ) override;
	bool visitDestroy( const StateMachine& ) override;
	bool visitCleanup( const StateMachine& ) override;

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
