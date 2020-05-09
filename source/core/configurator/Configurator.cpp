#include "Configurator.h"

#include <tinyxml2.h>

#include <string>
#include <fstream>
#include <iostream>

using namespace tinyxml2;
XMLDocument xmlDoc;

Configurator::ConfiguratorBuilder Configurator::builder;
std::string Configurator::mConfigFileName;

XMLElement* FindElement( std::string _property )
{
	XMLNode * pRoot = xmlDoc.FirstChild();
	if (pRoot == nullptr) 
		return nullptr;

	for( auto e = pRoot->FirstChildElement( "Parameter" ); e != NULL; e = e->NextSiblingElement( "Parameter" ))
	{
		std::string name = e->Attribute( "name" );

		if( name.compare( _property ) == 0 )
		{		
			return  e->FirstChildElement( "value" );
		}
	}
	return nullptr;
}

Configurator::Configurator( std::string _name ) 
{
	xmlDoc.LoadFile( mConfigFileName.c_str() );
	if( xmlDoc.ErrorID() != 0 )
		std::cerr << "Failed reading from file [" << xmlDoc.ErrorID() <<"]\n";
}

bool Configurator::Get( std::string _property, int& _value ) const
{
	XMLElement* pValue = FindElement( _property );

	if  ( pValue != nullptr)
	{
		int tmp;
		pValue->QueryIntText( &tmp );
		_value = tmp;
	
		return true;
	}

	return false;
}


bool Configurator::Get( std::string _property, std::string& _value ) const
{
	XMLElement* pElement = FindElement( _property );

	if  ( pElement != nullptr)
	{
		const char *tmp = pElement->GetText();
		_value = std::string( tmp );
		return true;
	}

	return false;
}

