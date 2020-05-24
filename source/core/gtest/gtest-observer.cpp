#include "Observer.h"
#include "Subject.h"

#include <gtest/gtest.h>
#include <gmock/gmock.h>

class Beta:
    public Subject,
    public Observer
{
    public:
        bool Update( const Subject& ) override
        {
	       return false;	
        }
};

class MockBeta: public Beta
{
    public:
        MOCK_METHOD1( Update, bool( const Subject& ) );
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

	EXPECT_CALL( observer, Update( testing::_  ) ).WillOnce( testing::Return( true ));
	ASSERT_EQ( beta->Notify(), true );
}

TEST( Subject, NotifyObserverFailure )
{
	MockBeta observer;

	Beta* beta = new Beta();

	beta->Attach( observer );

	EXPECT_CALL( observer, Update( testing::_  ) ).WillOnce( testing::Return( false ));
	ASSERT_EQ( beta->Notify(), false );
}


int main(int argc, char **argv) 
{
    ::testing::InitGoogleTest(&argc, argv); 
    return RUN_ALL_TESTS();
}
