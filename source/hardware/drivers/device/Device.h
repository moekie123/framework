#pragma once

#include "IDevice.h"
#include "Configurator.h"

#include "Signal.h"

#include "Generic.h"
#include "designpatterns/Builder.h"
#include "designpatterns/Singleton.h"

#include <string>

class Device:
    public IDevice
{
	public:
		/**
		 * Builder
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
		static DeviceBuilder builder;
		
		/**
		 * Constructor
		 */
		Device( Configurator& _config, std::string _name, Signal& _period, Signal& _dutycycle );
		
		void set( std::string, int ){}
};
