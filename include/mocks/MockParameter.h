#pragma once

#include "Generic.h"
#include "IParameter.h"
#include "Configurator.h"

#include <gmock/gmock.h>
#include <string>

class MockParameter: 
    public IParameter
{
        public:
            MOCK_METHOD1( update, void( IParameter* ));
 //           MOCK_CONST_METHOD1( getProperty, const int&( std::string ));
 //           MOCK_METHOD2( setProperty, void( std::string, int ));
            MOCK_METHOD0( reset, void() );
            MOCK_METHOD1( build, Generic*( std::string ));
};


