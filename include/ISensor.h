#pragma once

#include "Composite.h"

/**
 * @brief The generic interface class for a Sensor
 */
class ISensor:
    public Composite< ISensor >
{

};
