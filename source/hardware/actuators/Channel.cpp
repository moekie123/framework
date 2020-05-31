#include "Channel.h"

//Stl-Headers
#include <string>
#include <vector>

const std::vector<std::string> labels = { "enable", "period", "duty_cycle" };

bool Channel::Update( const IMosquitto& _mqtt, const std::string& _package )
{
        spdlog::info( "Channel Received Message [{}]", _package );

        mPayloads.push( _package );

        return true;
}

Channel::Channel( const IConfigurator* _config, std::string _name )
{
        std::string filename = "";
        spdlog::info( "Construct Channel [{}]", _name );

        // TODO Should you SetName
        mName = _name;

        // Get the path of the driver
        _config->GetProperty( "Channel", mName, "path", mPath );

        // Get the id of the channel
        _config->GetProperty( "Channel", mName, "id", mId );

        for ( auto label : labels )
                mFds[label] = -1;
}

bool Channel::visitInitialize( const ActuatorStateMachine& )
{
        std::string filename = "";
        spdlog::info( "Initialize Channel [{}]", mId );

        // Export Channel
        filename = mPath + "/export";
        int fd = open( filename.c_str(), O_WRONLY );
        write( fd, mId.c_str(), strlen( mId.c_str() ) );
        close( fd );

        // Connect all filedescriptors
        for ( auto label : labels )
        {
                filename = mPath + "/pwm" + mId + "/" + label;
                mFds[label] = open( filename.c_str(), O_WRONLY );
        }
        return true;
}

bool Channel::visitPreConfigure( const ActuatorStateMachine& )
{
        spdlog::info( "PreConfigure Channel [{}]", mId );

        // TODO Set Start Position as Temporaray Refrence, Sett this by pushing a JSON Command
        return true;
}

bool Channel::visitConnect( const ActuatorStateMachine& )
{
        spdlog::info( "Connect Channel [{}]", mId );
        return true;
}

bool Channel::visitPostConfigure( const ActuatorStateMachine& )
{
        spdlog::info( "PostConfigure Channel [{}]", mId );
        return true;
}

bool Channel::visitLoop( const ActuatorStateMachine& )
{
        spdlog::trace( "Loop Channel [{}]", mId );

        if ( !mPayloads.empty() )
        {
                // Get the first element from the queue
                auto message = mPayloads.front();
                spdlog::info( "Channel [{}] | Process Payload | [{}]", mId, message );

                mPayloads.pop();
        }

   	return true;
}

bool Channel::visitReconnect( const ActuatorStateMachine& )
{
        spdlog::info( "Reconnect Channel [{}]", mId );
        return true;
}

bool Channel::visitDisconnect( const ActuatorStateMachine& )
{
        spdlog::info( "Disconnect Channel [{}]", mId );
        return true;
}

bool Channel::visitDestroy( const ActuatorStateMachine& )
{
        std::string filename = "";
        spdlog::info( "Destroy Channel [{}]", mId );

        // Disconnect all filedescriptors
        for ( auto label : labels )
        {
                if ( mFds[label] >= 0 ) close( mFds[label] );
        }

        // Unexport Channel
        filename = mPath + "/unexport";
        int fd = open( filename.c_str(), O_WRONLY );
        write( fd, mId.c_str(), strlen( mId.c_str() ) );
        close( fd );

        return true;
}

bool Channel::visitCleanup( const ActuatorStateMachine& )
{
        spdlog::info( "Cleanup Channel [{}]", mId );
        return true;
}

