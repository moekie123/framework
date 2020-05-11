#pragma once

#include "IMosquitto.h"

#include "Singleton.h"
#include "Generic.h"
#include "Builder.h"

#include "IConfigurator.h"

class Mosquitto:
	public IMosquitto
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

	protected:
	
	/*
	 * @brief Connect to the broker 
	 * @param _hostname The server address
	 * @param _port The server port
	 * @details The connection credentials are loaded in the constructor
	 */
	bool Connect( const std::string& _hostname, const std::string& _port );

	/*
	 * @brief Disonnect from the broker
	 */
	bool Disconnect();

	private:

	/*
	 * @brief The mosquitto client
	 */
	struct mosquitto* mClient;

	/*
	 * @brief The network addres of the mqtt broker
	 */
	std::string mHostname;

	/*
	 * @brief The network port of the mqtt broker
	 */
	std::string mPort;

	/*
	 * @brief The Username of the mqtt broker 
	 */
	std::string mUsername;

	/*
	 * @brief The Password of the mqtt broker
	 */
	std::string mPassword;
};
