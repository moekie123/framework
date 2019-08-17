#pragma once

#include "IChipset.h"

class Chipset:
    public IChipset
{
    public:
        
        Chipset();

        /** Generic */
        Generic* build( std::string _name ) override;

        /** Observer */
        void update( IChipset *subject) override;

};
