#include "Framework.h"

#include "designpatterns/Singleton.h"
#include "designpatterns/AbstractFactory.h"

#include "Configurator.h"
#include "core/parameter/Parameter.h"

#include "hardware/drivers/device/Device.h"

Framework::Framework( int argc, char *argv[] )
{
	Configurator config = Singleton< Configurator >::Instance();

	Factory& factory = Singleton< Factory >::Instance();
	factory.Register( "Parameter",  &Parameter::builder );

	factory.Register( "Device",  &Device::builder );
};
