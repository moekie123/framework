#pragma once

#include "Generic.h"
#include "Composite.h"
#include "Subject.h"
#include "Observer.h"

/**
 * @brief The generic interface for a Chipset
 */
class IChipset:

//    public Generic,
    public Composite< IChipset >,

    public Observer< IChipset >,
    public Subject< IChipset >
{
        
};
