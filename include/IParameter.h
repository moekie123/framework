#pragma once

#include "Generic.h"

#include "Composite.h"
#include "Subject.h"
#include "Observer.h"

#include <string>
#include <map>

/**
 *  Interface: IParameter
 */
class IParameter:
    public Generic,
    public Composite< IParameter >,
    public Observer< IParameter >,
    public Subject< IParameter >
{
    public:

    /** 
     *  @brief reset
     *  @details resets the parameter to the default value
     */
    virtual void reset() = 0;

};
