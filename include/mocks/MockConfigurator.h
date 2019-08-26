#pragma once

#include "Generic.h"
#include "IConfigurator.h"

#include <gmock/gmock.h>
#include <string>

class MockConfigurator: 
    public IConfigurator
{
        public:
	    MOCK_CONST_METHOD2( Get, bool( std::string, int& ));
	    MOCK_CONST_METHOD2( Get, bool( std::string, std::string& ));
};
