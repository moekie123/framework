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

// Third-Party
#include <spdlog/spdlog.h>

// Stl-Headers
#include <getopt.h>
#include <iostream>

#define FRAMEWORK_USAGE                                              \
        "Usage: %s [-h]\n"                                           \
        "\n"                                                         \
        "Options:\n"                                                 \
        "  -h, --help        Print this menu and exit.\n"            \
        "  -c, --config      The configuation file [default: %s].\n" \
        "  -v, --verbose     Turn on the debug.\n"                   \
        "\n"

Framework::Framework( int argc, char* argv[] ) : mConfigurationFilename( "config.xml" )
{
        int ret;

        // Parse Arguments
        ret = parseArguments( argc, argv );

        spdlog::debug( "Initialize Framework" );


        // Open Configuration File
        spdlog::debug( "Configure Configurator" );

        Configurator::mConfigFileName = mConfigurationFilename;

        Configurator* configurator = new Configurator();
        Singleton<Configurator>::Register( *configurator );

        // Build Mosquitto Instance
        spdlog::debug( "Configure Mosquitto" );

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
        spdlog::debug( "Configure Factory" );
        auto factory = Singleton<Factories>::Instance();

        /** Current registered builders: */

        ///	- Configurator
        factory.Register<IConfigurator>( "Configurator", &Configurator::builder );

        ///	- Parameter
        factory.Register<IParameter>( "Parameter", &Parameter::builder );

        ///	- Mosquitto
        factory.Register<IMosquitto>( "Mosquitto", &Mosquitto::builder );

        ///	- Chipset
        factory.Register<IChipset>( "Chipset", &Chipset::builder );

        ///	- Device
        factory.Register<IDevice>( "Device", &Device::builder );

        ///	- Actuator
        factory.Register<IActuator>( "Actuator", &Actuator::builder );

        delete port;
};

int Framework::parseArguments( int argc, char* argv[] )
{
        int c;

        struct option long_options[] = {
                { "help", no_argument, NULL, 'h' },
                { "config", required_argument, NULL, 'c' },
                { "verbose", no_argument, NULL, 'v' },
        };

        // Loop through all arguments and handle
        while ( ( c = getopt_long( argc, argv, "hc:v", long_options, 0 ) ) != -1 )
        {
                switch ( c )
                {
                        case 'v':
                                spdlog::set_level( spdlog::level::debug );
                                break;
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
