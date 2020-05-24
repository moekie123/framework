// Inheritance
#include "Object.h"

// Stl-Headers
#include <algorithm>
#include <string>
#include <vector>

// Third-Party
#include <spdlog/spdlog.h>

const std::map<std::string, int> defaults = {
        { "const", 0 },
};

Object::Object()
{
        //        auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
        //        console_sink->set_level( spdlog::level::debug );
        //        console_sink->set_pattern( "[multi_sink_example] [%^%l%$] %v" );

        //        mLogger = spdlog::logger( "Object", { console_sink } );
        //        mLogger = new spdlog::logger( "Object" );
        //       mLogger->info( "this should appear in both console and file" );
        spdlog::debug( "Construct Object" );

        for ( auto it = defaults.begin(); it != defaults.end(); ++it )
        {
                mProperties[it->first] = it->second;
        }
};

const std::string& Object::GetName() const
{
        return mName;
}

bool Object::SetName( const std::string& _name )
{
        mName = _name;
        return true;
}

bool Object::GetProperty( const std::string& _property, int& _value )
{
        auto property = std::find_if( mProperties.begin(), mProperties.end(), [this, _property]( auto const& property ) {
                // Check for match (without name)
                if ( _property.compare( property.first ) == 0 )
                {
                        return true;
                }

                // Check for match when name attached
                if ( _property.compare( mName + "." + property.first ) == 0 )
                {
                        return true;
                }

                return false;
        } );

        if ( property != mProperties.end() )
        {
                _value = property->second;
                return true;
        }

        return false;
}

bool Object::SetProperty( const std::string& _property, const int& _value )
{
        if ( mProperties.find( "const" )->second == 1 )
                return false;

        auto property = std::find_if( mProperties.begin(), mProperties.end(), [this, _property]( auto const& property ) {
                // Check for match (without name)
                if ( _property.compare( property.first ) == 0 )
                {
                        return true;
                }

                // Check for match when name attached
                if ( _property.compare( mName + "." + property.first ) == 0 )
                {
                        return true;
                }

                return false;
        } );

        if ( property != mProperties.end() )
        {
                property->second = _value;
                return true;
        }

        return false;
}

bool Object::Reset()
{
        return false;
}
