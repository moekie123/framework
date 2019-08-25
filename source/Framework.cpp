#include "Framework.h"

#include "Singleton.h"
#include "Factory.h"

#include "core/configurator/Configurator.h"
#include "core/parameter/Parameter.h"

#include "hardware/drivers/chipset/Chipset.h"
#include "hardware/drivers/device/Device.h"

Framework::Framework( int argc, char *argv[] )
{
	Factory& factory = Singleton< Factory >::Instance();

	/** Registered Builders: */

	///	- Configurator
	factory.Register< Configurator> ( "Configurator" );

	///	- Parameter 
	factory.Register< Parameter >( "Parameter" );

	///	- Chipset
    	factory.Register< Chipset >( "Chipset" );

	///	- Device
	factory.Register< Device >( "Device" );
};
