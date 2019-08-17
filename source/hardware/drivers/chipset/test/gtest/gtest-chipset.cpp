#include <gtest/gtest.h>

#include "IChipset.h"
#include "../../Chipset.h"

TEST( Construct, Default )
{
    IChipset *cs = new Chipset();
}

TEST( Open, Default )
{
    IChipset *cs = new Chipset();
//    IDevice *d = cs->getDevice( 0 );
}


int main(int argc, char **argv) 
{
    ::testing::InitGoogleTest(&argc, argv); 
    return RUN_ALL_TESTS();
}
