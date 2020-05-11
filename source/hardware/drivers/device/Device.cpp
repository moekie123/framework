#include "Device.h"

#include "Signal.h"

#include "IConfigurator.h"

Device::DeviceBuilder Device::builder;

Device::Device( const IConfigurator& _config, const std::string& _name, const Signal& _period, const Signal& _dutycycle )
{

}

