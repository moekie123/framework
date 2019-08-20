#pragma once

#include "IDevice.h"

#include "Generic.h"
#include "Builder.h"
#include "Singleton.h"

#include "Signal.h"
#include "Configurator.h"

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
				Generic* build( std::string _name ) override
				{
					Configurator& config = Singleton< Configurator >::Instance();
					
					Signal* period = new Signal( config, _name + "/period" );
					Signal* dutycycle = new Signal( config, _name + "/dutycycle" );

					return new Device( config, _name, *period, *dutycycle );
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
		Device( Configurator& _config, std::string _name, Signal& _period, Signal& _dutycycle );
		
		/**
		 * @brief Setter
		 * @details TODO This can be replaced by the default Generic SetProperty
		 */
		void set( std::string, int )
		{

		}
};
