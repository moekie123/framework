// Inheritance
#include "Actuator.h"

// Interfaces
#include "IConfigurator.h"
#include "IParameter.h"

// Design Patterns
#include "Factory.h"
#include "Singleton.h"

// Stl-Headers
#include <string>

Actuator::ActuatorBuilder Actuator::builder;

Actuator::Actuator( const IConfigurator& _config, std::string _name )
{
        mName = _name;
}

bool Actuator::visitInitialize( const StateMachine& )
{
        spdlog::info( "[Visit] Initialize" );
        return false;
}

bool Actuator::visitConfigure( const StateMachine& )
{
        spdlog::info( "[Visit] Configure" );
        return false;
}

bool Actuator::visitConnect( const StateMachine& )
{
        spdlog::info( "[Visit] Connect" );
        return false;
}

bool Actuator::visitLoop( const StateMachine& )
{
        spdlog::info( "[Visit] Loop" );
        return false;
}

bool Actuator::visitReconnect( const StateMachine& )
{
        spdlog::info( "[Visit] Reconnect" );
        return false;
}

bool Actuator::visitDisconnect( const StateMachine& )
{
        spdlog::info( "[Visit] Disconnect" );
        return false;
}

bool Actuator::visitDestroy( const StateMachine& )
{
        spdlog::info( "[Visit] Destroy" );
        return false;
}

bool Actuator::visitCleanup( const StateMachine& )
{
        spdlog::info( "[Visit] Cleanup" );
        return false;
}
