#pragma once

// Type Defention
#include "Modules.h"

// Inheritance
#include "Generic.h"

/** 
 * @brief The Mosquitto Interface
 */
class IMosquitto : public Generic,
                   public MqttVisitor
{
       public:
        virtual ~IMosquitto() = default;
};

