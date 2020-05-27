// Inheritance
#include "Generic.h"

// Design Pattern
#include "Observer.h"
#include "Subject.h"

// Third-Party
#include <gmock/gmock.h>
#include <gtest/gtest.h>

class Beta : public Generic
{
       public:
        bool Update( const Generic& ) override
        {
                return false;
        }
};

class MockBeta : public Beta
{
       public:
        MOCK_METHOD1( Update, bool( const Generic& ) );
};

TEST( Construct, Default )
{
        Beta beta;
        // Static cast to check whether all classes are intherent
}

TEST( Subject, AttachObserver )
{
        Beta observer;
        Beta subject;

        subject.Attach( observer );
        // Static cast to check whether all classes are intherent
}

TEST( Subject, NotifyObserverSuccesfull )
{
        MockBeta observer;

        Beta* beta = new Beta();
        beta->Attach( observer );

        EXPECT_CALL( observer, Update( testing::_ ) ).WillOnce( testing::Return( true ) );
        ASSERT_EQ( beta->Notify(), true );
}

TEST( Subject, NotifyObserverFailure )
{
        MockBeta observer;

        Beta* beta = new Beta();

        beta->Attach( observer );

        EXPECT_CALL( observer, Update( testing::_ ) ).WillOnce( testing::Return( false ) );
        ASSERT_EQ( beta->Notify(), false );
}

int main( int argc, char** argv )
{
        ::testing::InitGoogleTest( &argc, argv );
        return RUN_ALL_TESTS();
}
