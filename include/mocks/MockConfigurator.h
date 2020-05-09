#pragma once

#include "Generic.h"
#include "IConfigurator.h"

#include <gmock/gmock.h>
#include <string>

class MockConfigurator: 
    public IConfigurator
{
        public:

		MOCK_CONST_METHOD2( GetInteger, bool( std::string, int& ));
		bool Get( std::string _property, int& _value ) const override
		{
			return GetInteger( _property, _value );
		}

		MOCK_CONST_METHOD2( GetString, bool( std::string, std::string& ));
		bool Get( std::string _property, std::string& _value ) const override
		{
			return GetString( _property, _value );
		}

};
