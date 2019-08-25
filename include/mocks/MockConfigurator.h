#pragma once

#include "Generic.h"
#include "IConfigurator.h"

#include <gmock/gmock.h>
#include <string>

class MockConfigurator: 
    public IConfigurator
{
        public:
            MOCK_CONST_METHOD1( getProperty, const int&( std::string ) );
};
