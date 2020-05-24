#pragma once

// Inheritance
#include "Generic.h"

// Design Patterns
#include "Builder.h"
#include "Singleton.h"

// Interfaces
#include "IConfigurator.h"

// Third-Party
#include <gmock/gmock.h>

// Stl-Headers
#include <string>

class MockConfigurator : public IConfigurator
{
       public:
        /*
		 * GMock Builder, To test base class builder
		 * It is common to load a configurator in the builder
		 */
        class MockBuilder : public Builder<IConfigurator>
        {
               public:
                static IConfigurator* Build( const IConfigurator*, const std::string& _name )
                {
                        MockConfigurator& mock = Singleton<MockConfigurator>::Instance();
                        return &mock;
                }

                MockBuilder() : Builder( MockBuilder::Build )
                {
                }
        };
        static MockBuilder builder;

        MOCK_CONST_METHOD3( GetInteger, bool( const std::string&, const std::string&, int& ) );
        bool Get( const std::string& _name, const std::string& _attribute, int& _value ) const override
        {
                return GetInteger( _name, _attribute, _value );
        }

        std::map<std::string, std::string> stringResults;
        MOCK_CONST_METHOD3( GetString, bool( const std::string&, const std::string&, std::string& ) );
        bool Get( const std::string& _name, const std::string& _attribute, std::string& _value ) const override
        {
                bool result = GetString( _name, _attribute, _value );

                auto it = stringResults.find( _attribute );
                if ( it != stringResults.end() )
                        _value = it->second;

                return result;
        }
};

MockConfigurator::MockBuilder MockConfigurator::builder;
