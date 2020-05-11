#pragma once

#include "Signal.h"
#include "Generic.h"

#include "IConfigurator.h"

#include <gmock/gmock.h>
#include <string>

#include "MockConfigurator.h"

class MockSignal: 
    public Signal
{
	public:
		MockSignal( const IConfigurator& _config ):Signal( _config , "MockSignal"){}
		MockSignal():Signal( mConfig , "MockSignal"){}

		MOCK_METHOD1( Write, void( const int& ));
		MOCK_METHOD1( Read, void( int& ));

	private:
		MockConfigurator mConfig;
};
