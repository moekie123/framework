// Design Pattern
#include "Composite.h"

// Third Party
#include <gmock/gmock.h>
#include <gtest/gtest.h>

class Beta : public Composite
{
       public:
        virtual void Trigger()
        {
                for ( auto c : mComponents )
                {
                        // mComppnents holds a Object-Base class
                        //			c->Trigger();
                }
        }

        std::string mName = "Beta";
};

class MockBeta : public Beta
{
       public:
        MOCK_METHOD0( Trigger, void() );
};

TEST( Construct, Default )
{
        Beta *b1 = new Beta();
        ASSERT_NE( b1, nullptr );
}

TEST( BuildTree, Add )
{
        Beta *b = new Beta();
        MockBeta m;

        b->Add( m );
        b->Trigger();
}

int main( int argc, char **argv )
{
        ::testing::InitGoogleTest( &argc, argv );
        return RUN_ALL_TESTS();
}
