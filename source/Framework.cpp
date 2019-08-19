#include "Framework.h"

#include "Singleton.h"
#include "Factory.h"

#include "Configurator.h"
#include "core/parameter/Parameter.h"

#include "hardware/drivers/chipset/Chipset.h"
#include "hardware/drivers/device/Device.h"

/**
 * @mainpage  Documentation for the Autonomous Bar Tender (Robotic Arm)
 * 	This webpage contains webpage documentation. 
 * 	The background developement and choices made during this project
 * 	are explained on "https://moekiehome.wpcomstaging.com".
 *
 * @section Introduction
 *	Welcome on the documentation for this Robotic Arm project.
 *
 * @section Core Idea
 *	The main idea for this project
 *
 * @section Controller
 * 	
 *
 */

Framework::Framework( int argc, char *argv[] )
{
	Configurator config = Singleton< Configurator >::Instance();
	Factory& factory = Singleton< Factory >::Instance();

	factory.Register( "Parameter",  &Parameter::builder );

    	factory.Register( "Chipset", &Chipset::builder );
	factory.Register( "Device", &Device::builder );
};
