#include <gtest/gtest.h>

#include "designpatterns/AbstractFactory.h"
#include "Generic.h"

class InterfaceBeta:
    public Generic
{
    public:
        virtual void execute() = 0;
};

class ConcreteBeta:
    public InterfaceBeta
{
    Generic* build( std::string ){ return new ConcreteBeta; }
    void execute(){}
};

TEST( Construct, Default )
{
    Factory *f = new Factory;

    f->push( "CB", new ConcreteBeta );

    auto ab = f->create< InterfaceBeta >( "CB", "Name" );

    ab->execute();

}

int main(int argc, char **argv) 
{
    ::testing::InitGoogleTest(&argc, argv); 
    return RUN_ALL_TESTS();
}
