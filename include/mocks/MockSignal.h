#pragma once

#include "Signal.h"
#include "Generic.h"

#include "IConfigurator.h"

#include <gmock/gmock.h>
#include <string>

class MockSignal: 
    public Signal
{
	public:
		MockSignal():Signal( mConfig , "MockSignal"){}

		MOCK_METHOD1( Write, void( const int& ));
		MOCK_METHOD1( Read, void( int& ));

	private:
		IConfigurator* mConfig;
};
