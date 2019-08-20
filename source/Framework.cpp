#include "Framework.h"

#include "Singleton.h"
#include "Factory.h"

#include "Configurator.h"
#include "core/parameter/Parameter.h"

#include "hardware/drivers/chipset/Chipset.h"
#include "hardware/drivers/device/Device.h"

// TODO This should be moved to a documenation page
/**
 * @mainpage  Documentation for the Autonomous Bar Tender (Robotic Arm)
 * 	This is the documentation for a framework to create and control an robotic arm. 
 *
 *	This doxygen generated webpages are describing the code base. 
 * 	Detailed design choices van be found on the <a href="https://moekiehome.wpcomstaging.com"> WordPress Pages </a> 
 *
 * @section Introduction
 *	This is de doxygen generated documentation for this Robotic Arm project.
 */

Framework::Framework( int argc, char *argv[] )
{
	Configurator config = Singleton< Configurator >::Instance();
	Factory& factory = Singleton< Factory >::Instance();

	/** Registered Builders: */

	///	- Parameter 
	factory.Register( "Parameter",  &Parameter::builder );

	///	- Chipset
    	factory.Register( "Chipset", &Chipset::builder );

	///	- Device
	factory.Register( "Device", &Device::builder );
};
