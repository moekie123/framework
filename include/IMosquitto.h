#pragma once

// Inheritance
#include "Generic.h"
#include "Visitor.h"

/** 
 * @brief The Mosquitto Interface
 * @details Note that only Parameters are allowed to attach to the broker
 */
class IMosquitto : public Generic,
                   public Visitor
{
};
