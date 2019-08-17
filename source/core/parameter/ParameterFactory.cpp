#include "ParameterFactory.h"

#include "designpatterns/Singleton.h"
#include "designpatterns/AbstractFactory.h"

#include "Parameter.h"
#include "ParameterRange.h"

ParameterFactory::ParameterFactory()
{
    Factory& factory = Singleton< Factory >::Instance();
    
    factory.push( "ParameterDefault",   new Parameter );
    factory.push( "ParameterRange",     new ParameterRange );

};


