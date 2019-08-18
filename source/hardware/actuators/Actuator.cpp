#include "Actuator.h"
#include "Configurator.h"
#include "IParameter.h"

#include "designpatterns/Singleton.h"
#include "designpatterns/AbstractFactory.h"

#include <string>

Actuator::Actuator( std::string _name ) 
{
    mName = _name;

    Factory& factory = Singleton< Factory >::Instance(); 

    IParameter* ip = factory.Create< IParameter >( "Parameter", "TargetPosition" );

    Composite< IParameter >::add( ip );
}

