#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "IDevice.h"
#include "../../Device.h"

#include "mocks/MockConfigurator.h"
#include "mocks/MockSignal.h"

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
