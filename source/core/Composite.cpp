#include "Composite.h"

Composite::Composite()
{
	std::cout << "Composite: Construct\n";
}

bool Composite::Add( Object& obs )
{
	std::cout << "Composite: Add Child\n";
	mComponents.push_back( &obs );
	return false;
}

bool Composite::SetProperty( const  std::string& property, const int& value )
{
	std::cout << "Composite: SetProperty\n";

	Object::SetProperty( property, value );

	for( auto c: mComponents )
		c->SetProperty( property, value );

	return false;
}

bool Composite::GetProperty( const  std::string& property, int& value )
{
	std::cout << "Composite: GetProperty\n";

	Object::GetProperty( property, value );

	for( auto c: mComponents )
		c->GetProperty( property, value );

	return false;
}

bool Composite::Reset()
{
	std::cout << "Composite: Reset\n";
	return false;
}

