#pragma once

// Inheritance
#include "Generic.h"

// Design Patterns
#include "Visitor.h"

/** 
 * @brief The Mosquitto Interface
 */
class IMosquitto : public Generic,
                   public Visitor<0>
{
       public:
        virtual ~IMosquitto() = default;
};

