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

Configurator::Configurator() 
{
	if( !document )
	{
		document = new XMLDocument();
		document->LoadFile( mConfigFileName.c_str() );
	}
}

/**
 * @brief (Visitor Pattern) Custom XML-Parser for Parameter elements
 */
class XMLParameter: public XMLVisitor
{
	std::string mName;
	std::string mAttribute;
	
	public:

	/*
	 * @brief The colected property after the visitor has been visited
	 * @details will be a nullptr when nothing has been found
	 */
	const XMLElement* property = nullptr;

	/**
	 * @brief The constructor
	 * @param _name The name of the paramter that needs to be found
	 * @param _attribute The attribute that request is searching for
	 */
	XMLParameter( std::string _name, std::string _attribute )
	{
		mName = _name;
		mAttribute = _attribute;
	}

	/**
	 * @brief (Visitor) Visited when a XMLDocument enters a new element.
	 * @param e The visited element
	 * @param a The corrosponding attributes of the vistied element
	 * @return True, if the XMLParameter needs to keep search for a match
	 */
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
	 
