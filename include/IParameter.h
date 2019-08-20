#pragma once

#include "Generic.h"

#include "Composite.h"
#include "Subject.h"
#include "Observer.h"

#include <string>
#include <map>

/**
 * @brief The generic interface class for a Poramater
 */
class IParameter:
    public Generic,
    public Composite< IParameter >,
    public Observer< IParameter >,
    public Subject< IParameter >
{
    public:

    /** 
     *  @brief reset the parameter to the default valuei
     *  @details TODO should return a bool whether it was succesfull
     */
    virtual void reset() = 0;

};
