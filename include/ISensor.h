#pragma once

#include "designpatterns/Composite.h"

/**
 *  Interface: ISensor
 */
class ISensor:
    public Composite< ISensor >
{

};
