#pragma once

// Inheritance
#include "Generic.h"

// Interfaces
#include "IConfigurator.h"

// Third-Party
#include <spdlog/spdlog.h>

class Channel : public Generic
{
       public:
        Channel( const IConfigurator* _config, std::string _name ) : mConfig( _config ), mEnable( 0 ), mPeriod( 0 ), mDutyCycle( 0 )
        {
                spdlog::info( "Construct Channel [{}]", _name );
                mName = _name;
        }

        bool Open()
        {
                std::string filename;
                spdlog::info( "Open Channel [{}]", mName );

                mConfig->GetProperty( "Channel", mName, "path", mPath );
                /*
                filename = mPath + "/" + "enable";
                mEnable = open( filename.c_str(), O_WRONLY );

                filename = mPath + "/" + "period";
                mPeriod = open( filename.c_str(), O_WRONLY );

                filename = mPath + "/" + "duty_cycle";
                mDutyCycle = open( filename.c_str(), O_WRONLY );
*/
                return false;
        }

        bool Close()
        {
                spdlog::info( "Close Channel [{}]", mName );
                /*
                if ( mEnable > 0 )
                {
                        write( mEnable, "0", 1 );
                        close( mEnable );
                }

                if ( mPeriod > 0 )
                        close( mPeriod );

                if ( mDutyCycle > 0 )
                        close( mDutyCycle );
*/
                return false;
        }

       private:
        const IConfigurator* mConfig;

        std::string mPath;

        int mEnable;
        int mPeriod;
        int mDutyCycle;
};
