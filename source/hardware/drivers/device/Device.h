#pragma once

#include "IDevice.h"

#include "Generic.h"

#include "AbstractFactory.h"
#include "Factory.h"
#include "Builder.h"
#include "Singleton.h"

#include "Signal.h"
#include "IConfigurator.h"

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
				static IDevice* BuildDevice( const std::string& _name )
				{
	
					const std::string label = "Configurator";
				
					Factories& factory = Singleton< Factories >::Instance();
					IConfigurator* config = factory.Construct< IConfigurator >( label );
			
					Signal* period = new Signal( *config, _name + "/period" );
					Signal* dutycycle = new Signal( *config, _name + "/dutycycle" );
					
					Device* device = new Device( *config, _name, *period, *dutycycle );

					return device;
				}
			
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
