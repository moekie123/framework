#pragma once

// Type Defention
#include "Modules.h"

// Inherentance
#include "Channel.h"
#include "Generic.h"

// STL-Headers
#include <vector>

/**
 * @brief The Actuator Interface
 */
class IActuator : public Generic,
                  public ActuatorVisitor
{
       public:
        /**
	 * @brief (Composite-) Nodes and Leafs can be add to the instance by this Add-methods
	 * @param _gen The Object that will observe
 	 */
        bool Add( Channel& _channel )
        {
                mChannels.push_back( &_channel );
                return true;
        }

       protected:
        std::vector<Channel*> mChannels;
};
