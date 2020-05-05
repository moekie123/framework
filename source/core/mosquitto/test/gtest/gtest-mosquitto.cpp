//#include "../../Mosquitto.h"
#include "IMosquitto.h"

#include "mocks/MockParameter.h"
#include "mocks/MockConfigurator.h"

#include <gtest/gtest.h>
#include <gmock/gmock.h>

// Ignore Nagy Mocks for the Configurator Get(ters)
using ::testing::NiceMock;

/**
 * GTest: get the name op the parameter 
 */
TEST( MosquittoTest, Dummy )
{
    	ASSERT_EQ( true, true );
}

int main(int argc, char **argv) 
{
    ::testing::InitGoogleTest(&argc, argv); 
    return RUN_ALL_TESTS();
}
