#pragma once

#include "IDevice.h"

#include "Generic.h"

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
			public Builder
		{
			public:
				Generic& Build( const std::string& _name ) override
				{
					Factory& factory = Singleton< Factory >::Instance();

					IConfigurator& config = factory.Create< IConfigurator >( "Configurator", "configuration.xml" );

					Signal* period = new Signal( config, _name + "/period" );
					Signal* dutycycle = new Signal( config, _name + "/dutycycle" );
					Device* device = new Device( config, _name, *period, *dutycycle );

					return *device;
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
		
		/**
		 * @brief Setter
		 * @details TODO This can be replaced by the default Generic SetProperty
		 */
		void Set( const std::string&, const int& )
		{

		}
};
