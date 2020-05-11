#pragma once

#include "Generic.h"
#include "IParameter.h"

#include <gmock/gmock.h>
#include <string>

class MockParameter: 
    public IParameter
{
        public:
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


