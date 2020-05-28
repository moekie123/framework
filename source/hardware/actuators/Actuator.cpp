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
#include <string>
#include <vector>

namespace fs = std::filesystem;

struct pwm_file_descriptors
{
        int id;
        int enable;
        int period;
        int duty_cycle;
};
std::vector<pwm_file_descriptors*> fds;

Actuator::ActuatorBuilder Actuator::builder;

Actuator::Actuator( const IConfigurator& _config, std::string _name )
{
        mName = _name;

        _config.GetProperty( "Actuator", mName, "driver", mDriver );
        _config.GetProperty( "Actuator", mName, "chip", mChip );
}

int Actuator::Channels( bool _enable )
{
        spdlog::info( "Configure Channels" );

        // Actuator Chip Descriptors
        int fd_npwm = -1;
        int fd_config = -1;

        int channels = 0;

        std::string filename = "";
        int result = 0;  // Read and Write Result

        // Open Chip Descriptors
        filename = mChip + "npwm";
        fd_npwm = open( filename.c_str(), O_RDONLY );
        if ( fd_npwm < 0 ) goto exit;

        filename = mChip + ( _enable ? "export" : "unexport" );
        fd_config = open( filename.c_str(), O_WRONLY );
        if ( fd_config < 0 ) goto exit;

        // Get the channels
        {
                char* buf = (char*)calloc( 10, sizeof( char ) );

                result = read( fd_npwm, buf, 10 );
                if ( result < 0 ) goto exit;

                channels = std::stoi( buf, nullptr );

                free( buf );

                spdlog::info( "Channels [{}]", channels );
        }
        if ( channels <= 0 ) goto exit;

        // Iterate through all channels
        for ( int i = 0; i < channels; i++ )
        {
                std::string index = std::to_string( i );
                spdlog::debug( "{} Channel [{}]", ( _enable ? "Export" : "Unexport" ), index );

                // Open Channel
                write( fd_config, index.c_str(), strlen( index.c_str() ) );
        }

exit:
        // Close Chip Descriptors
        if ( fd_npwm != -1 )
                close( fd_npwm );
        if ( fd_config != -1 )
                close( fd_config );

        return channels;
}

bool Actuator::visitInitialize( const StateMachine& )
{
        spdlog::info( "[Visit] Initialize" );
        return fs::exists( mChip );
}

bool Actuator::visitPreConfigure( const StateMachine& )
{
        spdlog::info( "[Visit] PreConfigure" );
        return true;
}

bool Actuator::visitConnect( const StateMachine& )
{
        spdlog::info( "[Visit] Connect" );

        return true;
}

bool Actuator::visitPostConfigure( const StateMachine& )
{
        spdlog::info( "[Visit] PostConfigure" );

        std::string filename = "";

        int channels = Channels( true );

        // Iterate through all channels
        for ( int i = 0; i < channels; i++ )
        {
                std::string index = std::to_string( i );

                /* Configure the channels */
                pwm_file_descriptors* pfd = new pwm_file_descriptors{ -1, -1, -1, -1 };

                pfd->id = i;

                filename = mChip + "pwm" + std::to_string( i ) + "/" + "period";
                pfd->period = open( filename.c_str(), O_WRONLY );
                if ( pfd->period == -1 ) break;

                filename = mChip + "pwm" + std::to_string( i ) + "/" + "enable";
                pfd->enable = open( filename.c_str(), O_WRONLY );
                if ( pfd->enable == -1 ) break;

                filename = mChip + "pwm" + std::to_string( i ) + "/" + "duty_cycle";
                pfd->duty_cycle = open( filename.c_str(), O_WRONLY );
                if ( pfd->duty_cycle == -1 ) break;

                /* Store pointer */
                fds.push_back( pfd );
        }

        return false;
}

bool Actuator::visitLoop( const StateMachine& )
{
        //        spdlog::info( "[Visit] Loop" );
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
        spdlog::info( "[Visit] Destroy" );

        // close and delete array of pointers
        for ( auto fd : fds )
        {
                if ( fd->enable > 0 )
                        close( fd->enable );

                if ( fd->period > 0 )
                        close( fd->period );

                if ( fd->duty_cycle > 0 )
                        close( fd->duty_cycle );

                delete fd;
        }
        fds.clear();

        Channels( false );
        return true;
}

bool Actuator::visitCleanup( const StateMachine& )
{
        spdlog::info( "[Visit] Cleanup" );
        // Gracefull terminate
        return true;
}
