// Inheritance
#include "Actuator.h"

// Interfaces
#include "IConfigurator.h"
#include "IParameter.h"

// Design Patterns
#include "Factory.h"
#include "Singleton.h"

// Stl-Headers
#include <fcntl.h>
#include <filesystem>
#include <map>
#include <string>

namespace fs = std::filesystem;

std::map<std::string, int> fds;
int channels = 0;

Actuator::ActuatorBuilder Actuator::builder;

Actuator::Actuator( const IConfigurator& _config, std::string _name )
{
        mName = _name;

        _config.GetProperty( mName, "driver", mDriver );
        _config.GetProperty( mName, "chip", mChip );

        fds["period"] = -1;
        fds["dutycycle"] = -1;
}

bool Actuator::visitInitialize( const StateMachine& )
{
        spdlog::info( "[Visit] Initialize" );
        return fs::exists( mChip );
}

bool Actuator::visitConfigure( const StateMachine& )
{
        int fd = -1;
        spdlog::info( "[Visit] Configure" );

        // Read N-Channels
        std::string npwm = mChip + "npwm";
        fd = open( npwm.c_str(), O_RDONLY );

        if ( fd != -1 )
        {
                char* buf = (char*)calloc( 10, sizeof( char ) );

                read( fd, buf, 10 );
                channels = std::stoi( buf, nullptr );
                close( fd );

                free( buf );

                spdlog::info( "Channels [{}]", channels );
                return true;
        }
        return false;
}

bool Actuator::visitConnect( const StateMachine& )
{
        int fd = -1;
        spdlog::info( "[Visit] Connect" );

        // Open Export
        std::string exprt = mChip + "export";
        fd = open( exprt.c_str(), O_WRONLY );

        if ( fd != -1 )
        {
                // Iterate through all channels
                for ( int i = 0; i < channels; i++ )
                {
                        std::string index = std::to_string( i );
                        spdlog::debug("Export Channel [{}]", index );
                        write( fd, index.c_str(), strlen( index.c_str() ) );

			/* Configure the channels */
                }
                close( fd );
                return true;
        }
        return false;
}

bool Actuator::visitLoop( const StateMachine& )
{
        //        spdlog::info( "[Visit] Loop" );

        // Move the server
        return true;
}

bool Actuator::visitReconnect( const StateMachine& )
{
        spdlog::info( "[Visit] Reconnect" );
        return false;
}

bool Actuator::visitDisconnect( const StateMachine& )
{
        spdlog::info( "[Visit] Disconnect" );

        // Close all file descriptors
        return true;
}

bool Actuator::visitDestroy( const StateMachine& )
{
        int fd;
        spdlog::info( "[Visit] Destroy" );

        // Open Export
        std::string exprt = mChip + "unexport";
        fd = open( exprt.c_str(), O_WRONLY );

        if ( fd != -1 )
        {
                // Iterate through all channels
                for ( int i = 0; i < 17; i++ )
                {
                        std::string index = std::to_string( i );
                        spdlog::debug( "Unexport Channel [{}]", index );
                        write( fd, index.c_str(), strlen( index.c_str() ) );
                }
                close( fd );
                return true;
        }
        return false;
}

bool Actuator::visitCleanup( const StateMachine& )
{
        spdlog::info( "[Visit] Cleanup" );
        // Gracefull terminate
        return true;
}
