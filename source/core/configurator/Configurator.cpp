#include "Configurator.h"

#include <string>
#include <fstream>

#include <iostream>

#include "tinyxml2.h"
using namespace tinyxml2;

XMLDocument xmlDoc;

Configurator::Configurator( std::string _filename ) 
{
	std::cout << "Configurator: read file " << _filename << "\n";
	XMLError eResult = xmlDoc.LoadFile( _filename.c_str() );
}

bool Configurator::getSignal( std::string _name, std::string _property, std::string& _filename ) const
{
	XMLNode * pRoot = xmlDoc.FirstChild();
	if (pRoot == nullptr) 
		return false;

	for( auto e = pRoot->FirstChildElement("Signal"); e != NULL; e = e->NextSiblingElement("Signal") )
	{
		std::string name = e->Attribute("name");
		if( name.compare( _name ) == 0 )
		{
			XMLElement* pValue = e->FirstChildElement( _property.c_str() );
			if  ( pValue != nullptr)
			{
				const char* strAttr = pValue->GetText();
				std::cout << strAttr;
				
				_filename = std::string( strAttr );
				return true;
			}
		}
	}

	return false;
}


bool Configurator::getProperty( std::string _name, std::string _property, int& _value ) const
{
	XMLNode * pRoot = xmlDoc.FirstChild();
	if (pRoot == nullptr) 
		return false;
	
	for( auto e = pRoot->FirstChildElement("Parameter"); e != NULL; e = e->NextSiblingElement("Parameter") )
	{
		std::string name = e->Attribute("name");
		
		if( name.compare( _name ) == 0 )
		{	
			XMLElement* pValue = e->FirstChildElement( _property.c_str() );
			if  ( pValue != nullptr)
			{
				int tmp;
				pValue->QueryIntText( &tmp );
				_value = tmp;
				return true;
			}
		}
	}

	return false;
}

bool Configurator::setProperty( std::string _name, std::string _property, const int &_value )
{
	return false;
}
