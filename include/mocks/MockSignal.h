#pragma once

// Inheritance
#include "Generic.h"
#include "Signal.h"

// Interfaces
#include "IConfigurator.h"

// Testing
#include "MockConfigurator.h"

// Third-Party
#include <gmock/gmock.h>

// Stl-Headers
#include <string>

class MockSignal : public Signal
{
       public:
        MockSignal( const IConfigurator& _config ) : Signal( _config, "MockSignal" ) {}
        MockSignal() : Signal( mConfig, "MockSignal" ) {}

        MOCK_METHOD1( Write, void( const int& ) );
        MOCK_METHOD1( Read, void( int& ) );

       private:
        MockConfigurator mConfig;
};
