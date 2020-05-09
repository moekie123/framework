#include "Framework.h"

#include "Singleton.h"
#include "Factory.h"

#include "core/configurator/Configurator.h"
#include "core/parameter/Parameter.h"

#include "hardware/drivers/chipset/Chipset.h"
#include "hardware/drivers/device/Device.h"

#include "hardware/actuators/Actuator.h"

#include <getopt.h>
#include <iostream>

#define FRAMEWORK_USAGE                                               	   	\
"Usage: %s [-h]\n" 	                                                 	\
"\n"                                                                           	\
"Options:\n"                                                                   	\
"  -h, --help        Print this menu and exit.\n"                              	\
"  -c, --config      The configuation file [default: %s].\n"                   	\
"\n"

Framework::Framework( int argc, char *argv[] ):
	mConfigurationFilename("config.xml")
{
	int ret;

	// Parse Arguments
	ret = parseArguments( argc, argv );

	// Construct Factory
	Factory& factory = Singleton< Factory >::Instance();
		
	/** Current registered builders: */

	///	- Configurator
	Configurator::mConfigFileName = mConfigurationFilename;
	factory.Register< Configurator> ( "Configurator" );

	///	- Parameter 
	factory.Register< Parameter >( "Parameter" );

	///	- Chipset
    	factory.Register< Chipset >( "Chipset" );

	///	- Device
	factory.Register< Device >( "Device" );

	///	- Actuator
	factory.Register< Actuator >( "Actuator" );

};


int Framework::parseArguments( int argc, char* argv[] )
{
	int c;

	struct option long_options[] = {
		{"help",	no_argument, 		NULL, 	'h'},
		{"config",	required_argument, 	NULL, 	'c'},
	};

	// Loop through all arguments and handle
	while (( c = getopt_long( argc, argv, "hc:", long_options, 0 )) != -1 ) 
	{
		switch ( c ) 
		{
			case 'c':
				mConfigurationFilename = std::string( optarg );
				break;
			case 'h':
			case '?':
				printf( FRAMEWORK_USAGE, argv[0], mConfigurationFilename.c_str() );
				return -1;
		}
	}
	return 0;
}

