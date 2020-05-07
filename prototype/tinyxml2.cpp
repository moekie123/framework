#include <iostream>
#include <cstring>

#include "tinyxml2.h"

static std::string filename = "/tmp/prototype.xml";

using namespace tinyxml2;

//This function parses the one of the XML files that parses the XML-formatted reuters corpus files.
int main(int argc, const char * argv[]) 
{
	tinyxml2::XMLDocument doc;

	std::cout << "Booting (Prototype) TinyXML Implemenation\n";

	// Create XMLElement
	{
		static std::string data = "<element>Framework</element>";
	
		std::cout << "Prototype 1: InMemory demo\n";
	
		// Evaluta the string
		std::cout << "\t- parse the variable\n";
		doc.Parse( data.c_str() );
		
		// Create new XML file
		std::cout << "\t- define root of xml tree\n";
		XMLElement* root = doc.FirstChildElement();

		std::cout << "\t- create xml element\n";
		XMLElement* newElement = doc.NewElement( "Subelement" );
		
		// Insert add new element to XML (in memeory)
		std::cout << "\t- add new element to xml-tree\n";
		root->InsertEndChild( newElement );

		// Print Document
		std::cout << "\t- print xml-tree\n";
		doc.Print();

		std::cout << "Prototype 1: Complete\n\n";
	}	


	{
		static std::string data = "<element>Framework</element>";
	
		std::cout << "Prototype 2: Storage demo\n";

		// Evaluta the string
		std::cout << "\t- parse the variable\n";
		doc.Parse( data.c_str() );
		
		// Create new XML file
		std::cout << "\t- define root of xml tree\n";
		XMLElement* root = doc.FirstChildElement();

		std::cout << "\t- create xml element\n";
		XMLElement* newElement = doc.NewElement( "Subelement" );
		
		// Insert add new element to XML (in memeory)
		std::cout << "\t- add new element to xml-tree\n";
		root->InsertEndChild( newElement );

		/* Write XML-File */
		std::cout << "Write to file [" << filename << "]\n";
		doc.SaveFile( filename.c_str() );

		if( doc.ErrorID() != 0 )
			std::cerr << "Failed writing to file [" << doc.ErrorID() <<"]\n";

		std::cout << "Prototype 2: Complete\n\n";
	}
	

	{
		std::cout << "Prototype 3: Load File demo\n";

		// Read from file
		std::cout << "Read from file [" << filename << "]\n";
		doc.LoadFile( filename.c_str() );
		if( doc.ErrorID() != 0 )
			std::cerr << "Failed reading from file [" << doc.ErrorID() <<"]\n";

		// Print Document
		std::cout << "\t- print xml-tree\n";
		doc.Print();

		std::cout << "Prototype 3: Complete\n\n";
	}

	{
		tinyxml2::XMLPrinter printer;
		static std::string data = "<element>Framework</element>";

		std::cout << "Prototype 4: Custom Print demo\n";

		class XMLPrinterVisitor: 
			public tinyxml2::XMLVisitor
		{
			public:
			XMLPrinterVisitor()
			{
				std::cout << "\t-Construct Printer Visitor\n";
				std::cout << "\t[All visits (on default) should return true]\n";
			}

			bool VisitEnter( const XMLDocument & )
			{
				std::cout << "\t\tVisit Enter with XMLDocument\n";
				return true;
			}

			bool VisitExit( const XMLDocument & )
			{
				std::cout << "\t\tVisit Exit with XMLElement\n";
				return true;
			}	

			bool VisitEnter( const XMLElement &, const XMLAttribute *)
			{
				std::cout << "\t\tVisit Enter with XMLElement\n";
				return true;
			}

			bool VisitExit( const XMLElement & )
			{
				std::cout << "\t\tVisit Exit with XMLElement\n";
				return true;
			}	

			bool Visit( const XMLDeclaration & )
			{
				std::cout << "\t\tVisit with XMLDeclaration\n";
				return true;
			}	

			bool Visit( const XMLText & )
			{
				std::cout << "\t\tVisit with XMLTest\n";
				return true;
			}	

			bool Visit( const XMLComment & )
			{
				std::cout << "\t\tVisit with XMLComment\n";
				return true;
			}	

			bool Visit( const XMLUnknown & )
			{
				std::cout << "\t\tVisit With XMLUnknown\n";
				return true;
			}	
		};
		
		// Evaluta the string
		std::cout << "\t- parse the variable\n";
		doc.Parse( data.c_str() );
		
		// Create new XML file
		std::cout << "\t- define root of xml tree\n";
		XMLElement* root = doc.FirstChildElement();

		std::cout << "\t- inserting multiple element\n";
		for( int i=0; i < 10; i++)
			root->InsertEndChild( doc.NewElement("Subelement") );
	
		std::cout << "\t- Accept the visitor\n";
		XMLPrinterVisitor visitor;
		doc.Accept( &visitor );

		std::cout << "Prototype 4: Complete\n\n";
	}

	std::cout << "Terminate TinyXML Prototype\n";
}
