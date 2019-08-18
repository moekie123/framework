#include "Framework.h"

#include "Singleton.h"
#include "Factory.h"

#include "Configurator.h"
#include "core/parameter/Parameter.h"

#include "hardware/drivers/chipset/Chipset.h"
#include "hardware/drivers/device/Device.h"

Framework::Framework( int argc, char *argv[] )
{
	Configurator config = Singleton< Configurator >::Instance();
	Factory& factory = Singleton< Factory >::Instance();

	factory.Register( "Parameter",  &Parameter::builder );

    	factory.Register( "Chipset", &Chipset::builder );
	factory.Register( "Device", &Device::builder );
};
