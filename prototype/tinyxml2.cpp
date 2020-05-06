#include <iostream>
#include <cstring>

#include "tinyxml2.h"

static std::string filename = "/tmp/prototype.xml";

using namespace tinyxml2;

//This function parses the one of the XML files that parses the XML-formatted reuters corpus files.
int main(int argc, const char * argv[]) 
{
	tinyxml2::XMLDocument doc;
	tinyxml2::XMLPrinter printer;

	std::cout << "Booting (Prototype) TinyXML Implemenation\n";

	{
		static const char* test = "<element>Text before</element>";
		doc.Parse( test );
		
		XMLElement* root = doc.FirstChildElement();
		XMLElement* newElement = doc.NewElement( "Subelement" );
		
		root->InsertEndChild( newElement );
		doc.Print();
	}	

	/* Write XML-File */
	std::cout << "Write to file [" << filename << "]\n";
	doc.SaveFile( filename.c_str() );
	if( !doc.ErrorID() )
		std::cerr << "Failed writing to file [" << doc.ErrorID() <<"]\n";

	/* Read XML-File */
	std::cout << "Load from file [" << filename << "]\n";
	doc.LoadFile( filename.c_str() );
	if( !doc.ErrorID() )
		std::cerr << "Failed writing to file [" << doc.ErrorID() <<"]\n";

	/* Print XML-File */
	doc.Print( &printer );
	if( !doc.ErrorID() )
		std::cerr << "Failed writing to file [" << doc.ErrorID() <<"]\n";


	std::cout << "Terminate TinyXML Prototype\n";
}
