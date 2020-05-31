#pragma once

// Inheritance
#include "Generic.h"

// Interfaces
#include "IConfigurator.h"

// Design Patterns
#include "Visitor.h"

// Third-Party
#include <spdlog/spdlog.h>
#include <map>
#include <queue>

class Channel : public Generic,
                public Visitor<1>
{
       public:
        Channel( const IConfigurator* _config, std::string _name );

        /** 
	 * Visitor Pattern Methods
	 */
        bool visitInitialize( const ActuatorStateMachine& ) override;
        bool visitPreConfigure( const ActuatorStateMachine& ) override;
        bool visitConnect( const ActuatorStateMachine& ) override;
        bool visitPostConfigure( const ActuatorStateMachine& ) override;
        bool visitLoop( const ActuatorStateMachine& ) override;
        bool visitReconnect( const ActuatorStateMachine& ) override;
        bool visitDisconnect( const ActuatorStateMachine& ) override;
        bool visitDestroy( const ActuatorStateMachine& ) override;
        bool visitCleanup( const ActuatorStateMachine& ) override;

        /** Observer Methods */
        // TODO Package should be a radid json document
        bool Update( const IMosquitto& _mqtt, const std::string& _package ) override;

       private:
        std::string mId;
        std::string mPath;
        std::map<std::string, int> mFds;

        // TODO Should be a Rapid Json Package
        std::queue<std::string> mPayloads;
};
