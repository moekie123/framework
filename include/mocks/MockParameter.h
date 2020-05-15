#pragma once

#include "Generic.h"
#include "IParameter.h"

#include <gmock/gmock.h>
#include <string>

class MockParameter: 
    public IParameter
{
        public:
		/*
		 * GMock Builder, To test base class builder
		 * It is common to load a configurator in the builder
		 */
		class MockBuilder:
			public Builder
		{
			public:
				Generic& Build( const std::string& _name ) override
				{
					MockParameter& mock = Singleton< MockParameter >::Instance();
					return mock;
				}
		};
		static MockBuilder builder;

		/* IParameter */
    		MOCK_METHOD0( Reset, void() );

		/* IGeneric */
	   	MOCK_CONST_METHOD2( GetProperty, bool( const std::string&, int& ));
	    	MOCK_METHOD2( GetProperty, bool( const std::string&, const int& ));

		/* IObserver */
    		MOCK_METHOD1( Update, bool( const IParameter* ));
          
          	/* ??
		 * TODO - Is This Still necssary 
		 **/
	    	MOCK_METHOD1( Build, Generic*( const std::string& ));
};

MockParameter::MockBuilder MockParameter::builder;
