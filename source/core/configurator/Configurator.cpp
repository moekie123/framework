#include "Configurator.h"

#include "tinyxml2.h"

#include <string>
#include <fstream>
#include <iostream>

using namespace tinyxml2;
XMLDocument xmlDoc;

Configurator::ConfiguratorBuilder Configurator::builder;

Configurator::Configurator( std::string _filename ) 
{
	std::cout << "Configurator: read file " << _filename << "\n";
	XMLError eResult = xmlDoc.LoadFile( _filename.c_str() );
}

bool Configurator::getProperty( std::string _property, int& _value ) const
{
/*
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
*/
	return false;
}


bool Configurator::setProperty( std::string _property, const int &_value )
{
	return false;
}
