#include <gtest/gtest.h>

#include "Composite.h"

class   Beta:
    public Composite< Beta >
{
    public:
        std::string mName = "Beta";
};

TEST( Construct, Default )
{
    Beta *b1 = new Beta();
    ASSERT_NE( b1, nullptr );
}

TEST( BuildTree, Add )
{
    Beta *b1 = new Beta();
    Beta *b2 = new Beta();

    b1->add( b2 );
}


int main(int argc, char **argv) 
{
    ::testing::InitGoogleTest(&argc, argv); 
    return RUN_ALL_TESTS();
}
