#pragma once

#include "IChipset.h"

#include "Builder.h"
#include "Singleton.h"

#include "Configurator.h"

/**
 * @brief The (base) Chipset class
 */
class Chipset:
    public IChipset
{
    public:

 	/**
	 * @brief The Chipset Builder to create new (base) Chipsets
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

	/** 
	 * @brief The global Chipset Builder 
	 * @details This should be registerd to an (abstract) Factory in Framework
	 */
	static ChipsetBuilder builder;
   
	Chipset();
	/**
	 * @brief The basic constructor
	 * @param _config The Configurator to fill in the default values
	 * @param _name The name of the new Chipset
	 */
   	Chipset( Configurator& _config, std::string _name );

        void update( IChipset *subject) override;
};


