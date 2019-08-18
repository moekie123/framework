#pragma once

#include "Generic.h"
#include "Configurator.h"

#include <gmock/gmock.h>
#include <string>

class MockConfigurator: 
    public Configurator
{
        public:
            MOCK_CONST_METHOD1( getProperty, const int&( std::string ) );
};
