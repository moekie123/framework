#pragma once

#include "Composite.h"

/**
 *  Interface: ISensor
 */
class ISensor:
    public Composite< ISensor >
{

};
