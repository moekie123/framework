// Inheritance
#include "../../Configurator.h"
#include "Generic.h"

// Interfaces
#include "IConfigurator.h"

// Third-Party
#include <gmock/gmock.h>
#include <gtest/gtest.h>

// Stl-Headers
#include <filesystem>
#include <string>
#include <type_traits>
#include <typeinfo>

static std::string filename = "gtest-configurator.xml";

template <typename T>
struct TypedTest : public testing::Test
{
        using ParamType = T;
};

using Types = testing::Types<int, std::string>;
TYPED_TEST_CASE( TypedTest, Types );

TEST( Default, Construct )
{
        Configurator *cf = new Configurator();
        delete cf;
}

TEST( Default, ConstructInterface )
{
        IConfigurator *icf = new Configurator();
        delete icf;
}

TEST( Default, ConstructBuilder )
{
        auto cf = Configurator::builder.Build( nullptr, "Configurator" );
        ASSERT_EQ( typeid( IConfigurator * ), typeid( cf ) );

        delete cf;
}

TEST( Specalization, Integer )
{
        int value;

        IConfigurator *cf = new Configurator();

        ASSERT_EQ( cf->GetProperty<int>( "gtest-parameter", "Parameter", "value", value ), true );
        ASSERT_EQ( value, 42 );

        delete cf;
}

TEST( Specalization, String )
{
        std::string value;

        IConfigurator *cf = new Configurator();

        ASSERT_EQ( cf->GetProperty<std::string>( "gtest-parameter", "Parameter", "value", value ), true );
        ASSERT_EQ( value, "42" );

        delete cf;
}

TEST( IntegerException, Unknown )
{
        int value;
        IConfigurator *cf = new Configurator();
        ASSERT_EQ( cf->GetProperty<int>( "unknown", "unknown", "unknown", value ), false );

        delete cf;
}

TYPED_TEST( TypedTest, AllUnknown )
{
        using ParamType = typename TestFixture::ParamType;
        ParamType value;

        IConfigurator *cf = new Configurator();
        ASSERT_EQ( cf->GetProperty<ParamType>( "unknown", "unknown", "unknown", value ), false );

        delete cf;
}

TYPED_TEST( TypedTest, UnknownName )
{
        using ParamType = typename TestFixture::ParamType;
        ParamType value;

        IConfigurator *cf = new Configurator();
        ASSERT_EQ( cf->GetProperty<ParamType>( "unknown", "Parameter", "value", value ), false );

        delete cf;
}

TYPED_TEST( TypedTest, UnknownType )
{
        using ParamType = typename TestFixture::ParamType;
        ParamType value;

        IConfigurator *cf = new Configurator();
        ASSERT_EQ( cf->GetProperty<ParamType>( "gtest-parameter", "unknown", "value", value ), false );

        delete cf;
}

TYPED_TEST( TypedTest, UnknownAttribute )
{
        using ParamType = typename TestFixture::ParamType;
        ParamType value;

        IConfigurator *cf = new Configurator();
        ASSERT_EQ( cf->GetProperty<ParamType>( "gtest-parameter", "Parameter", "unknown", value ), false );

        delete cf;
}

int main( int argc, char **argv )
{
        if ( std::filesystem::exists( filename ) )
        {
                Configurator::mConfigFileName = filename;
                ::testing::InitGoogleTest( &argc, argv );
                return RUN_ALL_TESTS();
        }
        else
                spdlog::info( "Gtests aborted, Failed to load [{}]", filename );

        return 0;
}
