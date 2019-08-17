#pragma once

#include "Generic.h"
#include "designpatterns/Composite.h"
#include "designpatterns/Subject.h"
#include "designpatterns/Observer.h"

/**
 * Interface: IChipset
 */
class IChipset:
    public Generic,
    public Composite< IChipset >,
    public Observer< IChipset >,
    public Subject< IChipset >
{
        
};
