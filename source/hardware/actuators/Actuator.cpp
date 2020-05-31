// Inheritance
#include "Actuator.h"

// Interfaces
#include "IConfigurator.h"
#include "IParameter.h"

// Design Patterns
#include "Factory.h"
#include "Singleton.h"

// Stl-Headers
#include <fcntl.h>
#include <filesystem>
#include <string>
#include <vector>

Actuator::ActuatorBuilder Actuator::builder;

Actuator::Actuator( const IConfigurator& _config, std::string _name )
{
        mName = _name;
}

bool Actuator::visitInitialize( const ActuatorStateMachine& afsm )
{
        spdlog::info( "[Visit] Initialize" );

        for ( auto channel : mChannels )
                channel->visitInitialize( afsm );

        return true;
}

bool Actuator::visitPreConfigure( const ActuatorStateMachine& afsm )
{
        spdlog::info( "[Visit] PreConfigure" );

        for ( auto channel : mChannels )
                channel->visitPreConfigure( afsm );

        return true;
}

bool Actuator::visitConnect( const ActuatorStateMachine& afsm )
{
        spdlog::info( "[Visit] Connect" );

        for ( auto channel : mChannels )
                channel->visitConnect( afsm );

        return true;
}

bool Actuator::visitPostConfigure( const ActuatorStateMachine& afsm )
{
        spdlog::info( "[Visit] PostConfigure" );

        for ( auto channel : mChannels )
                channel->visitPostConfigure( afsm );

        return true;
}

bool Actuator::visitLoop( const ActuatorStateMachine& afsm )
{
        for ( auto channel : mChannels )
                channel->visitLoop( afsm );

        // "period", 20000000 );

        // min = 450000;
        // max = 2300000;

        //        spdlog::info( "[Visit] Loop" );
        return true;
}

bool Actuator::visitReconnect( const ActuatorStateMachine& afsm )
{
        for ( auto channel : mChannels )
                channel->visitReconnect( afsm );

        spdlog::info( "[Visit] Reconnect" );
        return false;
}

bool Actuator::visitDisconnect( const ActuatorStateMachine& afsm )
{
        spdlog::info( "[Visit] Disconnect" );

        for ( auto channel : mChannels )
                channel->visitDisconnect( afsm );

        // Close all file descriptors
        return true;
}

bool Actuator::visitDestroy( const ActuatorStateMachine& afsm )
{
        spdlog::info( "[Visit] Destroy" );

        for ( auto channel : mChannels )
                channel->visitDestroy( afsm );

        return true;
}

bool Actuator::visitCleanup( const ActuatorStateMachine& afsm )
{
        spdlog::info( "[Visit] Cleanup" );

        for ( auto channel : mChannels )
        {
                channel->visitCleanup( afsm );
                delete channel;
        }

        mChannels.clear();

        // Gracefull terminate
        return true;
}
