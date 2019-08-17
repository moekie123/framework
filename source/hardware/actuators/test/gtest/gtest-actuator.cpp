#include <gtest/gtest.h>
#include <map>

#include "IActuator.h"
#include "../../Actuator.h"

TEST( Interface, Construct )
{

}

int main(int argc, char **argv) 
{
    ::testing::InitGoogleTest(&argc, argv); 
    return RUN_ALL_TESTS();
}
