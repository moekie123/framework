// Framework
#include "Framework.h"

// Design Patterns
#include "AbstractFactory.h"
#include "Factory.h"
#include "Singleton.h"

// Concrete Objects
#include "core/configurator/Configurator.h"
#include "core/mosquitto/Mosquitto.h"
#include "core/parameter/Parameter.h"

// Concrete Hardward elements
#include "hardware/actuators/Actuator.h"
#include "hardware/drivers/chipset/Chipset.h"
#include "hardware/drivers/device/Device.h"

// Stl-Headers
#include <getopt.h>
#include <iostream>

#define FRAMEWORK_USAGE                                              \
        "Usage: %s [-h]\n"                                           \
        "\n"                                                         \
        "Options:\n"                                                 \
        "  -h, --help        Print this menu and exit.\n"            \
        "  -c, --config      The configuation file [default: %s].\n" \
        "\n"

Framework::Framework( int argc, char* argv[] ) : mConfigurationFilename( "config.xml" )
{
        int ret;

        // Parse Arguments
        ret = parseArguments( argc, argv );

        Configurator::mConfigFileName = mConfigurationFilename;

        // Open Configuration File
        Configurator* configurator = new Configurator();
        Singleton<Configurator>::Register( *configurator );

        // Build Mosquitto Instance
        std::string* hostname = new std::string();
        configurator->GetProperty( "mosquitto", "hostname", (std::string&)*hostname );

        std::string* username = new std::string();
        configurator->GetProperty( "mosquitto", "username", (std::string&)*username );

        std::string* password = new std::string();
        configurator->GetProperty( "mosquitto", "password", (std::string&)*password );

        int* port = new int();
        configurator->GetProperty( "mosquitto", "port", (int&)*port );

        Mosquitto* mosquitto = new Mosquitto( *configurator, *hostname, *port, *username, *password );
        Singleton<Mosquitto>::Register( *mosquitto );

        // Creat Abstract Factory
        auto factory = Singleton<Factories>::Instance();

        /** Current registered builders: */

        ///	- Configurator

        ///	- Parameter
        factory.Register<IParameter>( "Parameter", &Parameter::builder );

        ///	- Mosquitto

        ///	- Chipset

        ///	- Device

        ///	- Actuator

        /* ##### DEPRECATED #######
	// Construct Factory
	Factory* factory = new Factory( *configurator );
	Singleton< Factory >::Register( *factory );
	
	///	- Configurator
	factory->Register< Configurator> ( "Configurator" );

	///	- Parameter 
	factory->Register< Parameter >( "Parameter" );

	///	- Mosquitto
	factory->Register< Mosquitto >( "Mosquitto" );

	///	- Chipset
    	factory->Register< Chipset >( "Chipset" );

	///	- Device
	factory->Register< Device >( "Device" );

	///	- Actuator
	factory->Register< Actuator >( "Actuator" );
*/
};

int Framework::parseArguments( int argc, char* argv[] )
{
        int c;

        struct option long_options[] = {
                { "help", no_argument, NULL, 'h' },
                { "config", required_argument, NULL, 'c' },
        };

        // Loop through all arguments and handle
        while ( ( c = getopt_long( argc, argv, "hc:", long_options, 0 ) ) != -1 )
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
