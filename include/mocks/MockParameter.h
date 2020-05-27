#pragma once

// Inheritance
#include "Generic.h"

// Interfaces
#include "IConfigurator.h"
#include "IParameter.h"

// Design Patterns
#include "Builder.h"
#include "Singleton.h"

// Third-Party
#include <gmock/gmock.h>

// Stl-Headers
#include <string>

class MockParameter : public IParameter
{
       public:
        /*
		 * GMock Builder, To test base class builder
		 * It is common to load a configurator in the builder
		 */
        class MockBuilder : public Builder<IParameter>
        {
               public:
                static IParameter* Build( const IConfigurator*, const std::string& _name )
                {
                        MockParameter& mock = Singleton<MockParameter>::Instance();
                        return &mock;
                }

                MockBuilder() : Builder( MockBuilder::Build )
                {
                }
        };
        static MockBuilder builder;

        /* IParameter */
        MOCK_METHOD0( Reset, bool() );

        /* IGeneric */
        MOCK_METHOD2( SetProperty, bool( const std::string&, const int& ) );
        MOCK_METHOD2( GetProperty, bool( const std::string&, int& ) );

        /* IObserver */
        MOCK_METHOD1( Update, bool( const Generic& ) );
};

MockParameter::MockBuilder MockParameter::builder;
