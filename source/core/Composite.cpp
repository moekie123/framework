#include "Composite.h"
#include <iostream>

Composite::Composite()
{
	std::cout << "Composite: Construct\n";
}

bool Composite::Add( Object& _obj )
{
	std::cout << "Composite: Add Child\n";

	std::string oName = _obj.GetName();
	_obj.SetName( std::string( mName + "/" + oName ) );

	mComponents.push_back( &_obj );

	return false;
}

bool Composite::SetProperty( const  std::string& _property, const int& _value )
{
	volatile bool res = false;
	std::cout << "Composite: SetProperty\n";

	if( mProperties.find( "const" )->second == 1 )
		goto exit;

	res = Object::SetProperty( _property, _value );
	if( res ) goto exit;

	for( auto c: mComponents )
	{
		res = c->SetProperty( _property, _value );
		if( res ) break;
	}

exit:
	return res;
}

bool Composite::GetProperty( const  std::string& _property, int& _value )
{
	volatile bool res = false;

	std::cout << "Composite: GetProperty\n";

	res = Object::GetProperty( _property, _value );
	if( res ) goto exit;

	for( auto c: mComponents )
	{
		res = c->GetProperty( _property, _value );
		if( res ) break;
	}

exit:
	return res;
}

bool Composite::Reset()
{
	std::cout << "Composite: Reset\n";
	return false;
}

