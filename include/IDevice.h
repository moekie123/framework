#pragma once

// Inheritance
#include "Generic.h"

/**
 * @brief The generic interface class for an Device
 */
class IDevice : public Generic
{
       public:
        virtual ~IDevice() = default;
};
