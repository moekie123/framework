#include "Parameter.h"

#include "IParameter.h"

#include "Generic.h"
#include "IConfigurator.h"

#include <map>
#include <iostream>

Parameter::ParameterBuilder Parameter::builder;

using property = std::pair< std::string, int >;

const std::map< std::string, int> defaults =
{
    { "default", 0 },
    { "const",   0 },
    { "value",   0 }
};

Parameter::Parameter( const IConfigurator& _config, const std::string& _name )
{
	SetName( _name );
    	
	mProperties.insert ( defaults.begin(), defaults.end() );

	for( auto it = defaults.begin(); it != defaults.end(); ++it )
	{
		int value;
		
		mProperties[ it->first ] =  it->second;
	
	       	if ( _config.GetProperty( mName, it->first, value ))
		{
			mProperties[ it->first ] =  value;
		}
	}
}
 
void Parameter::Reset()
{
	if ( mProperties.find( "const" )->second == 0 )
	{
		SetProperty( mName + ".value",  mProperties.find( "default" )->second );

		// Composite
	    	for( auto* component : mComponents )
		{
			component->Reset();
		}
	}

}

bool Parameter::SetProperty( const std::string& _property, const int& _value )
{
	bool result = false;

	if ( mProperties.find( "const" )->second == 1 )
		goto exit;

	result = Generic::SetProperty( _property, _value );
	if ( result ) 
	{
		goto exit;
	}
	// Composite
	for( auto* component : mComponents )
	{
		result = component->SetProperty( _property, _value );
		if( result ) 
			break;
	}

exit:
	return result;
}

bool Parameter::Update( const IParameter* subject )
{
	// Composite
	std::cout << "test\n";
	for( auto* component : mComponents )
	{
		std::cout << "Checkpoint\n";
		// Extract the IParameter Observer 
		Observer< IParameter >* param = dynamic_cast< IParameter* >( component );	
		param->Update( subject );
	}

	return true;
}

