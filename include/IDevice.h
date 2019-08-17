#pragma once

#include "designpatterns/Composite.h"

class IDevice:
    public Composite< IDevice >
{

};
