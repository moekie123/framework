#include "Actuator.h"

#include "Singleton.h"
#include "Factory.h"

#include "IConfigurator.h"
#include "IParameter.h"

#include <string>

Actuator::Actuator( std::string _name ) 
{
    mName = _name;

    Factory& factory = Singleton< Factory >::Instance(); 

    IParameter* ip = factory.Create< IParameter >( "Parameter", "TargetPosition" );

    Composite< IParameter >::Add( ip );
}

