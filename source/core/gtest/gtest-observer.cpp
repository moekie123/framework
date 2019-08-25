#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "Observer.h"
#include "Subject.h"


class Beta:
    public Subject< Beta >,
    public Observer< Beta >
{
    public:
        void update( Beta* subject ) override
        { 
        }
};

class MockBeta: public Beta
{
    public:
        MOCK_METHOD1( update, void( Beta* ) );
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

    subject.attach( observer );
    // Static cast to check whether all classes are intherent
}

TEST( Subject, NotifyObserver )
{
    MockBeta observer;
    Beta *subject = new Beta();

    subject->attach( observer );

    EXPECT_CALL( observer, update( subject ) );
    
    subject->notify< MockBeta >();
}

int main(int argc, char **argv) 
{
    ::testing::InitGoogleTest(&argc, argv); 
    return RUN_ALL_TESTS();
}
