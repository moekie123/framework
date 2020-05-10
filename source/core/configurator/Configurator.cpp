#include "Configurator.h"

#include <tinyxml2.h>

#include <string>
#include <fstream>
#include <iostream>
#include <cstring>

using namespace tinyxml2;
XMLDocument* document;

Configurator::ConfiguratorBuilder Configurator::builder;
std::string Configurator::mConfigFileName;

Configurator::Configurator( std::string _name ) 
{
	if( !document )
	{
		document = new XMLDocument();
		document->LoadFile( mConfigFileName.c_str() );
	}
}

class XMLParameter: public XMLVisitor
{
	std::string mName;
	std::string mAttribute;
	
	public:

	const XMLElement* property;

	XMLParameter( std::string _name, std::string _attribute )
	{
		mName = _name;
		mAttribute = _attribute;
	}

	bool VisitEnter ( const XMLElement& e, const XMLAttribute* a )
	{
		// Check if it is a parameter
		if( strcmp( "Parameter" , e.Name() ) != 0 )
			return true;
		

		// Check the name of the parameter
		if ( e.Attribute( "name", mName.c_str() ) )
		{
			property = e.FirstChildElement( mAttribute.c_str() );
			return false;
		}
		return true;
	}	
};

bool Configurator::Get( std::string _name, std::string _attribute, int& _value ) const
{
	XMLElement* root;

	// Find root of the tree
	if( !document ) return false;

	root = document->RootElement();
	
	// Search for property
	XMLParameter* parameter = new XMLParameter( _name, _attribute );
	root->Accept( parameter );
	
	if( parameter->property )
		// Get Integer 
		return ( parameter->property->QueryIntText( &_value ) == XML_SUCCESS );
	
	return false;
}


bool Configurator::Get( std::string _name, std::string _attribute, std::string& _value ) const
{
	XMLElement* root;

	// Find root of the tree
	if( !document ) return false;
	root = document->RootElement();

	// Search for property
	XMLParameter* parameter = new XMLParameter( _name, _attribute );
	root->Accept( parameter );
	
	if( parameter->property )
	{
		// Get String
		_value = parameter->property->GetText();
		return true;
	}
	
	return false;
}
	 
