#pragma once

// Inheritance
#include "Generic.h"

// Interfaces

// Third-Party
#include <gmock/gmock.h>

// Stl-Headers
#include <string>

class MockGeneric : public Generic
{
       public:
        /* Inherintance of Object */
        MOCK_CONST_METHOD0( GetName, const std::string&());
        MOCK_METHOD1( SetName, bool( const std::string& ) );

        /* Inherintance of Object, which are already override by Composite */
        MOCK_METHOD2( SetProperty, bool( const std::string&, const int& ));
        MOCK_METHOD2( GetProperty, bool( const std::string&, int& ));

        MOCK_METHOD0( Reset, bool() );

        /* Observer Mockes */
        MOCK_METHOD1( Update, bool( const Generic& ) );

        /* Subject Mockes */
        MOCK_METHOD1( Attach, bool( Generic& ) );
        MOCK_METHOD0( Notify, bool() );
};
