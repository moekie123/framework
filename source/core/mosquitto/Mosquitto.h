#pragma once

#include "Visitor.h"
#include "StateMachine.h"


#include "IMosquitto.h"
#include "IConfigurator.h"

#include "Singleton.h"
#include "Generic.h"
#include "Builder.h"

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
	Mosquitto( const IConfigurator& _config );

	/**
	 * @brief The global ParameterBuilder
	 */
	static MosquittoBuilder builder;

	/** 
	 * Visitor Pattern Methods
	 */	
	bool visitInitialize( const MqttStateMachine& );
	bool visitConfigure( const MqttStateMachine& );
	bool visitConnect( const MqttStateMachine& );
	bool visitReconnect( const MqttStateMachine& );
	bool visitDisconnect( const MqttStateMachine& );
	bool visitDestroy( const MqttStateMachine& );
	bool visitCleanup( const MqttStateMachine& );

	private:

	/**
	 * @brief The mosquitto client
	 */
	struct mosquitto* mClient;

	/**
	 * @brief The network addres of the mqtt broker
	 */
	std::string mHostname;

	/**
	 * @brief The network port of the mqtt broker
	 */
	std::string mPort;

	/**
	 * @brief The Username of the mqtt broker 
	 */
	std::string mUsername;

	/**
	 * @brief The Password of the mqtt broker
	 */
	std::string mPassword;
};
