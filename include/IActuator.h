#pragma once

// Inherentance
#include "Generic.h"

// Design Patterns
#include "Visitor.h"

/**
 * @brief The Actuator Interface
 */
class IActuator : public Generic,
                  public Visitor<1>
{
       public:
       	virtual ~IActuator() = default;
};
