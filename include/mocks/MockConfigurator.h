#pragma once

#include "Generic.h"
#include "IConfigurator.h"

#include <gmock/gmock.h>
#include <string>

class MockConfigurator: 
    public IConfigurator
{
        public:

		MOCK_CONST_METHOD3( GetInteger, bool( const std::string&, const std::string&, int& ));
		bool Get( const std::string& _name, const std::string& _attribute, int& _value ) const override
		{
			return GetInteger( _name, _attribute, _value );
		}

		MOCK_CONST_METHOD3( GetString, bool( const std::string&, const std::string&, std::string& ));
		bool Get( const std::string& _name, const std::string& _attribute, std::string& _value ) const override
		{
			return GetString( _name, _attribute, _value );
		}

};
