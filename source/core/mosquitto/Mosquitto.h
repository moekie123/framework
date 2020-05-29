#pragma once

// Inheritance
#include "Generic.h"

// Interfaces
#include "IConfigurator.h"
#include "IMosquitto.h"

// Design Patterns
#include "StateMachine.h"

#include "AbstractFactory.h"
#include "Builder.h"
#include "Factory.h"
#include "Singleton.h"

/**
 * @brief (Wrapper Design Pattern) The Mosquitto Class
 * @details This class wraps around the libmosquitto library and functions can be called through the MosquittoVisitor
 */
class Mosquitto : public IMosquitto
{
 
     public:
        /**
	 * @brief The Mosquitto Builder class to build a new Mosquitto client
	 * @details It acctually retuns a Singleton
	 */
        class MosquittoBuilder : public Builder<IMosquitto>
        {
               public:
                /**
			 * @brief The build method that configures and constructs a new Parameter
			 * @param _config The pre build Configurator
			 * @param _name The name of the Mosquitto Broker (not used)
 			 */
                static IMosquitto* Build( const IConfigurator* _config, const std::string& _name )
                {
                        if ( !Singleton<Mosquitto>::IsConstructed() )
                        {
                                Mosquitto* mosquitto = new Mosquitto( *_config );
                                Singleton<Mosquitto>::Register( *mosquitto );
                        }

                        // Retrieve the client
                        Mosquitto& mosquitto = Singleton<Mosquitto>::Instance();
                        return &mosquitto;
                }

                /**
		 	 * @brief The constructor will map the Build-Method to the (base) Builder class
			 */
                MosquittoBuilder() : Builder( MosquittoBuilder::Build )
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
        Mosquitto( const IConfigurator& _config );

        /**
	 * @brief The global ParameterBuilder
	 */
        static MosquittoBuilder builder;

        /** 
	 * Visitor Pattern Methods
	 */
        bool visitInitialize( const MqttStateMachine& ) override;
	bool visitPreConfigure( const MqttStateMachine& ) override;
        bool visitConnect( const MqttStateMachine& ) override;
       	bool visitPostConfigure( const MqttStateMachine& ) override;
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
        std::string mHostname;

        /**
	 * @brief The network port of the mqtt broker
	 */
        int mPort;

        /**
	 * @brief The Username of the mqtt broker 
	 */
        std::string mUsername;

        /**
	 * @brief The Password of the mqtt broker
	 */
        std::string mPassword;
};
