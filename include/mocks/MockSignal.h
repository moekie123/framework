#pragma once

#include "Signal.h"
#include "Generic.h"

#include "Configurator.h"

#include <gmock/gmock.h>
#include <string>

class MockSignal: 
    public Signal
{
	public:
		MockSignal():Signal( mConfig , "MockSignal"){}

		MOCK_METHOD1( write, void( const int& ));
		MOCK_METHOD1( read, void( int& ));

	private:
		Configurator mConfig;
};
