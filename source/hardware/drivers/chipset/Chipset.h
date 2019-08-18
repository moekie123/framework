#pragma once

#include "IChipset.h"
#include "Configurator.h"

#include "designpatterns/Builder.h"
#include "designpatterns/Singleton.h"


class Chipset:
    public IChipset
{
    public:

 	/**
	 * Builder
	 */
	class ChipsetBuilder:
		public Builder
	{
		public:
		Generic* build( std::string _name ) override
		{
			Configurator& config = Singleton< Configurator >::Instance();
			return new Chipset( config, _name );
		}
	};
	static ChipsetBuilder builder;
   
	Chipset();
   	Chipset( Configurator& _config, std::string _name );

        /** Observer */
        void update( IChipset *subject) override;

};
