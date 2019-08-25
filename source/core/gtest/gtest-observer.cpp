#include "Observer.h"
#include "Subject.h"

#include <gtest/gtest.h>
#include <gmock/gmock.h>

class Beta:
    public Subject< Beta >,
    public Observer< Beta >
{
    public:
        bool Update( Beta* subject ) override
        {
	       return false;	
        }
};

class MockBeta: public Beta
{
    public:
        MOCK_METHOD1( Update, bool( Beta* ) );
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
    Beta *subject = new Beta();

    subject->Attach( observer );

    EXPECT_CALL( observer, Update( subject ) ).WillOnce( testing::Return(true));
    ASSERT_EQ( subject->Notify< MockBeta >(), true );
}

TEST( Subject, NotifyObserverFailure )
{
    MockBeta observer;
    Beta *subject = new Beta();

    subject->Attach( observer );

    EXPECT_CALL( observer, Update( subject ) ).WillOnce( testing::Return( false ));
    ASSERT_EQ( subject->Notify< MockBeta >(), false );
}


int main(int argc, char **argv) 
{
    ::testing::InitGoogleTest(&argc, argv); 
    return RUN_ALL_TESTS();
}
