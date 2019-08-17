#include "Chipset.h"

Chipset::Chipset()
{

}

Generic* Chipset::build( std::string _name )
{
    return new Chipset();
}

void Chipset::update( IChipset *subject )
{
    
}
