#include "Singleton.h"

#include "Generic.h"

#include <gtest/gtest.h>

class Beta
{
    public:
        std::string mName = "Beta";
    
};

TEST( Construct, Default )
{
	Beta &b1 = Singleton< Beta >::Instance();
    	Beta &b2 = Singleton< Beta >::Instance();
    
	ASSERT_EQ( &b1, &b2 );
}

TEST( Register, NewInstance  )
{
	Beta &b1 = Singleton< Beta >::Instance();
	
	Beta b2;
    	Singleton< Beta >::Register( b2 );

	Beta &b3 = Singleton< Beta >::Instance();

	ASSERT_EQ( &b1, &b3 );
}

TEST( Register, ExistingInstance  )
{
// GTest does not clear out a Singleton
/*
	Beta b1;
	Beta b2;

	Singleton< Beta >::Register( b1 );
    	Beta &b3 = Singleton< Beta >::Instance();
	ASSERT_EQ( &b1, &b2 );

	Singleton< Beta >::Register( b2 );
	b3 = Singleton< Beta >::Instance();
	ASSERT_NE( &b1, &b3 );
*/
}

TEST( Constructed, NewInstance )
{
// GTest does not clear out a Singleton
/*
	ASSERT_EQ( Singleton< Beta >::IsConstructed(), false );
*/
}

TEST( Constructed, ExistingInstance )
{
// GTest does not clear out a Singleton
/*
	Beta b1;
	Singleton< Beta >::Register( b1 );

	ASSERT_EQ( Singleton< Beta >::IsConstructed(), true );
*/
}

int main(int argc, char **argv) 
{
    ::testing::InitGoogleTest(&argc, argv); 
    return RUN_ALL_TESTS();
}
