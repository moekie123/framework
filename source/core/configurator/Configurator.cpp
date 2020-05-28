// Inheritance
#include "Configurator.h"

// Third-Party
#include <tinyxml2.h>

// Third-Party
#include <spdlog/spdlog.h>

// Stl-Headers
#include <sys/stat.h>
#include <filesystem>
#include <fstream>
#include <string>

namespace fs = std::filesystem;

tinyxml2::XMLDocument* document = nullptr;

Configurator::ConfiguratorBuilder Configurator::builder;
std::string Configurator::mConfigFileName;

Configurator::Configurator()
{
        spdlog::info( "Loading XML-File [{}]", mConfigFileName );

        // Check if xml document is already loaded
        if ( document )
        {
                spdlog::warn( "Document already loaded" );
                return;
        }

        // Check if xml file excists
        if ( !fs::exists( mConfigFileName ) )
        {
                throw std::runtime_error( "Could not open file" );
        }

        // Check read permission
        auto p = fs::status( mConfigFileName ).permissions();
        if ( ( p & fs::perms::owner_read ) == fs::perms::none )
        {
                throw std::runtime_error( "Could not read the file" );
        }

        // Construce new document
        document = new tinyxml2::XMLDocument();

        // Load XML-File
        tinyxml2::XMLError res = document->LoadFile( mConfigFileName.c_str() );
        if ( res != tinyxml2::XMLError::XML_SUCCESS )
        {
                throw std::runtime_error( "Failed to load file" );
        }
}

Configurator::~Configurator()
{
        spdlog::debug( "UnLoad XML-File [{}]", mConfigFileName );

        // Something is horrible wrong if the document is already clear before this point....
        if ( !document )
                spdlog::critical( "Document already deleted" );

        document->Clear();

        delete document;
        document = nullptr;
}

/**
 * @brief (Visitor Pattern) Custom XML-Parser for Parameter elements
 */
class XMLFramework : public tinyxml2::XMLVisitor
{
        const std::string& mName;
        const std::string& mType;
        const std::string& mAttribute;

       public:
        /**
	 * @brief The colected property after the visitor has been visited
	 * @details will be a nullptr when nothing has been found
	 */
        const tinyxml2::XMLElement* property = nullptr;

        /**
	 * @brief The constructor
	 * @param _name The name of the paramter that needs to be found
	 * @param _attribute The attribute that request is searching for
	 */
        XMLFramework( const std::string& _name, const std::string& _type, const std::string& _attribute ) : mName( _name ),
                                                                                                            mType( _type ),
                                                                                                            mAttribute( _attribute )
        {
        }

        /**
	 * @brief (Visitor) Visited when a XMLDocument enters a new element.
	 * @param e The visited element
	 * @param a The corrosponding attributes of the vistied element
	 * @return True, if the XMLParameter needs to keep search for a match
	 */
        bool VisitEnter( const tinyxml2::XMLElement& e, const tinyxml2::XMLAttribute* a )
        {
                // Check if it is a parameter
                if ( strcmp( mType.c_str(), e.Name() ) != 0 )
                {
                        // Continue searching
                        return true;
                }

                // Check the name of the parameter
                if ( e.Attribute( "name", mName.c_str() ) )
                {
                        property = e.FirstChildElement( mAttribute.c_str() );
                        return false;
                }

                return true;
        }
};

bool Configurator::Get( const std::string& _name, const std::string& _type, const std::string& _attribute, int& _value ) const
{
        tinyxml2::XMLElement* root;

        // Find root of the tree
        if ( !document ) return false;

        root = document->RootElement();

        // Search for property
      	XMLFramework* config = new XMLFramework( _name, _type, _attribute );
        root->Accept( config );

        // Property
        if ( config->property )
        {
                bool res;
                res = ( config->property->QueryIntText( &_value ) == tinyxml2::XML_SUCCESS );

                spdlog::debug( "Configurator Retrieve {} [{}.{}] : {}", _type, _name, _attribute, _value );

                return res;
        }
        return false;
}

bool Configurator::Get( const std::string& _name, const std::string& _type, const std::string& _attribute, std::string& _value ) const
{
        tinyxml2::XMLElement* root;

        // Find root of the tree
        if ( !document ) return false;
        root = document->RootElement();

        // Search for property
        XMLFramework* config = new XMLFramework( _name, _type, _attribute );
        root->Accept( config );

        if ( config->property )
        {
                // Get String
                _value = config->property->GetText();
                spdlog::debug( "Configurator Retrieve {} [{}.{}] : {}", _type, _name, _attribute, _value );

                return true;
        }

        return false;
}
