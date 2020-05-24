#pragma once

// Inheritance
#include "Generic.h"
#include "Signal.h"

// Interface
#include "IDevice.h"
#include "IConfigurator.h"

// Design Patterns
#include "AbstractFactory.h"
#include "Factory.h"
#include "Builder.h"
#include "Singleton.h"

// Stl-Headers
#include <string>

/**
 * @brief The (base) Device class
 */
class Device:
    public IDevice
{
	public:
		/**
		 * @brief The Device Builder to create new (base) Devices
		 */
		class DeviceBuilder:
			public Builder< IDevice >
			{
			public:

				/**
				 * @brief The build method that configures and constructs a new Parameter
				 * @param _config The pre build Configurator
				 * @param _name The name of the new Device
		 		 */
				static IDevice* BuildDevice( const IConfigurator* _config, const std::string& _name )
				{
					const std::string label = "Configurator";
				
					Factories& factory = Singleton< Factories >::Instance();
					IConfigurator* config = factory.Construct< IConfigurator >( label );
			
					Signal* period = new Signal( *config, _name + "/period" );
					Signal* dutycycle = new Signal( *config, _name + "/dutycycle" );
					
					Device* device = new Device( *config, _name, *period, *dutycycle );

					return device;
				}
			
				/**
	 			 * @brief The constructor will map the Build-Method to the (base) Builder class
				 */
				DeviceBuilder(): Builder( BuildDevice )
				{
				}
		};

		/**
		 * @brief The global Device builder
		 */
		static DeviceBuilder builder;
		
		/**
		 * @brief The default constructor
		 * @details TODO The signal should be move to a derived class only for PWM signals
		 * @param _config The Configurator to update the default properties
		 * @param _name The name of the new Device
		 * @param _period The Signal to control the Period
		 * @param _dutycycle The Signal to control the DutyCycle
		 */
		Device( const IConfigurator& _config, const std::string& _name, const Signal& _period, const Signal& _dutycycle );
};
