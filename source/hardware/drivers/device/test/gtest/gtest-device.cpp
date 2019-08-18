#include "../../Device.h"
#include "IDevice.h"

#include "mocks/MockConfigurator.h"
#include "mocks/MockSignal.h"

#include <gtest/gtest.h>
#include <gmock/gmock.h>

TEST( Construct, Default )
{
	MockConfigurator config;
	MockSignal period;
	MockSignal dutycycle;

	IDevice* d = new Device( config, "device" , period, dutycycle );
}

int main(int argc, char **argv) 
{
    ::testing::InitGoogleTest(&argc, argv); 
    return RUN_ALL_TESTS();
}
