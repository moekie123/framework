#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "Observer.h"
#include "Subject.h"


class Beta:
    public Subject< Beta >,
    public Observer< Beta >
{
    public:
        void Update( Beta* subject ) override
        { 
        }
};

class MockBeta: public Beta
{
    public:
        MOCK_METHOD1( Update, void( Beta* ) );
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

TEST( Subject, NotifyObserver )
{
    MockBeta observer;
    Beta *subject = new Beta();

    subject->Attach( observer );

    EXPECT_CALL( observer, Update( subject ) );
    
    subject->Notify< MockBeta >();
}

int main(int argc, char **argv) 
{
    ::testing::InitGoogleTest(&argc, argv); 
    return RUN_ALL_TESTS();
}
