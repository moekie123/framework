// Inheritance
#include "Generic.h"

// Design Pattern
#include "Observer.h"
#include "Subject.h"

// Testing
#include "mocks/MockGeneric.h"

// Third-Party
#include <gmock/gmock.h>
#include <gtest/gtest.h>

// Ignore Nagy Mocks for the Configurator Get(ters)
using ::testing::NiceMock;

/* All classes that inherent the Composite Class should be included in these unit-tests */
template <typename T>
class TypedTest : public ::testing::Test
{
};

using Types = ::testing::Types< std::pair<Generic, Generic>>;
TYPED_TEST_CASE( TypedTest, Types );

/* Define here which classes in the framework are inheriting Composite */
TYPED_TEST_CASE( TypedTest, Types );

TYPED_TEST( TypedTest, Default )
{
        typename TypeParam::first_type ObserverClass;
        typename TypeParam::second_type SubjectClass;
}

TYPED_TEST( TypedTest, AttachMockObserver )
{
        MockGeneric mock;
        std::string name = "Mock";

        typename TypeParam::first_type observer;
        typename TypeParam::second_type subject;

        // This call is only for logging....
        EXPECT_CALL( mock, GetName() ).WillOnce( testing::ReturnRef( name ) );
        subject.Attach( mock );
}

TYPED_TEST( TypedTest, Attach )
{
        typename TypeParam::first_type observer;
        typename TypeParam::second_type subject;

        subject.Attach( observer );
}

TYPED_TEST( TypedTest, NotifyMockObserverSussesfull )
{
        MockGeneric mock;
        std::string name = "Mock";

        typename TypeParam::first_type observer;
        typename TypeParam::second_type subject;

        // This call is only for logging....
        EXPECT_CALL( mock, GetName() ).WillOnce( testing::ReturnRef( name ) );
        subject.Attach( mock );

        EXPECT_CALL( mock, Update( testing::_ ) ).WillOnce( testing::Return( true ) );
        ASSERT_EQ( subject.Notify(), true );
}

TYPED_TEST( TypedTest, NotifyObserverSussesfull )
{
        typename TypeParam::first_type observer;
        typename TypeParam::second_type subject;

        subject.Attach( observer );
        ASSERT_EQ( subject.Notify(), true );
}

TYPED_TEST( TypedTest, NotifyMockObserverFailure )
{
        MockGeneric mock;
        std::string name = "Mock";

        typename TypeParam::first_type observer;
        typename TypeParam::second_type subject;

        // This call is only for logging....
        EXPECT_CALL( mock, GetName() ).WillOnce( testing::ReturnRef( name ) );
        subject.Attach( mock );

        EXPECT_CALL( mock, Update( testing::_ ) ).WillOnce( testing::Return( false ) );
        ASSERT_EQ( subject.Notify(), false );
}

int main( int argc, char** argv )
{
        ::testing::InitGoogleTest( &argc, argv );
        return RUN_ALL_TESTS();
}
