#include "Singleton.h"

#include "Generic.h"

#include <gtest/gtest.h>

class   Beta
{
    public:
        std::string mName = "Beta";
    
};

TEST( Construct, Default )
{
    Beta &b1 = Singleton< Beta >::Instance();
    
    ASSERT_EQ( b1.mName, "Beta" );
    
    b1.mName = "Alpha";
    ASSERT_EQ( b1.mName, "Alpha" );

    Beta &b2 = Singleton< Beta >::Instance();
    ASSERT_EQ( b2.mName, "Alpha" );
}

int main(int argc, char **argv) 
{
    ::testing::InitGoogleTest(&argc, argv); 
    return RUN_ALL_TESTS();
}
