#include "factory/ChipsetFactory.h"

#include "designpatterns/Singleton.h"
#include "designpatterns/AbstractFactory.h"

#include "Chipset.h"

ChipsetFactory::ChipsetFactory()
{
    Factory& factory = Singleton< Factory >::Instance();
    
    factory.push( "ChipsetDefault", new Chipset );
};


